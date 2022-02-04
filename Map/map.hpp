/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:34:35 by rgilles           #+#    #+#             */
/*   Updated: 2022/02/04 12:46:49 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

# include "../common/reverse_iterator.hpp"
# include "../common/enable_if.hpp"
# include "../common/is_integral.hpp"
# include "../common/lexicographical_compare.hpp"
# include "../common/equal.hpp"
# include "pair.hpp"
# include "tree_iterator.hpp"

namespace ft
{

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::node<ft::pair<const Key,T> > >	 >
	class map
	{
		public:

			typedef Key												key_type;
			typedef T												mapped_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::node<value_type>							node_type;
			typedef node_type*										node_ptr;
			typedef std::ptrdiff_t									difference_type;
			typedef size_t											size_type;
			typedef ft::tree_iterator<value_type, node_type>		iterator;
			typedef ft::tree_iterator<const value_type, node_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			struct value_compare : public std::binary_function<value_type, value_type, bool>
			{
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;

					value_compare (Compare c) : comp(c) {}
					bool operator() (const value_type& x, const value_type& y) const	{return comp(x.first, y.first);}

					Compare	comp;
			};

			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())	: _data(), _cmp(comp), _alloc(alloc), _size(0)
																													{this->_data = this->_alloc.allocate(1); this->_alloc.construct(this->_data, node_type());}
			template <class Ite>
			map(typename ft::enable_if<!ft::is_integral<Ite>::value, Ite>::type first, Ite last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
																													: _data(), _cmp(comp), _alloc(alloc), _size(0)
																													{this->_data = this->_alloc.allocate(1); this->_alloc.construct(this->_data, node_type()); this->insert(first, last);}
			map(const map &src)																						: _data(), _cmp(key_compare()), _alloc(allocator_type()), _size(0)
																													{this->_data = this->_alloc.allocate(1); this->_alloc.construct(this->_data, node_type()); *this = src;}
			virtual ~map(void)																						{this->clear(); this->_alloc.deallocate(this->_data, 1);}
			map	&operator=(map const &rhs)																			{
																														if (this != &rhs)
																														{
																															this->clear();
																															this->insert(rhs.begin(), rhs.end());
																														}
																														return (*this);
																													}
			size_type			size(void) const				{return (this->_size);}
			size_type			max_size(void) const			{return (this->_alloc.max_size());}
			allocator_type		get_allocator(void) const		{return (this->_alloc);}
			key_compare			key_comp(void) const			{return (key_compare());}
			value_compare		value_comp(void) const			{return (value_compare(key_compare()));}
			bool				empty(void) const				{return (this->_size == 0 ? true : false);}
			mapped_type&		operator[](const key_type& k)	{return (this->insert(value_type(k, mapped_type()))).first->second;}
			mapped_type&		at(const key_type& k)			{
																	iterator it = this->find(k);
																	if (it == this->end())
																		throw std::out_of_range("No such key.");
																	return ((*it).second);
																}
			const mapped_type&	at(const key_type& k) const		{
																	const_iterator it = this->find(k);
																	if (it == this->end())
																		throw std::out_of_range("No such key.");
																	return ((*it).second);
																}

			iterator				begin(void)			{return (iterator(leftmost(this->_data)));}
			const_iterator			begin(void) const	{return (const_iterator(leftmost(this->_data)));}
			iterator				end(void)			{return (iterator(rightmost(this->_data)));}
			const_iterator			end(void) const		{return (const_iterator(rightmost(this->_data)));}
			reverse_iterator		rbegin(void)		{return (reverse_iterator(this->end()));}
			const_reverse_iterator	rbegin(void) const	{return (const_reverse_iterator(this->end()));}
			reverse_iterator		rend(void)			{return (reverse_iterator(this->begin()));}
			const_reverse_iterator	rend(void) const	{return (const_reverse_iterator(this->begin()));}


			void						clear(void)											{
																								if (this->_size == 0)
																									return ;
																								node_ptr ghost = this->end().base();
																								ghost->parent->right = NULL;
																								this->_recursive_clear(this->_data);
																								this->_data = ghost;
																								this->_size = 0;
																							}
			ft::pair<iterator, bool>	insert(const value_type &val)						{
																								ft::pair<iterator, bool> res;
																								res.second = !this->count(val.first);
																								if (res.second == true)
																								{
																									node_ptr	newnode = this->_alloc.allocate(1);
																									this->_alloc.construct(newnode, node_type(val));
																									this->_add_node(newnode);
																								}
																								res.first = this->find(val.first);
																								return (res);
																							}
			iterator					insert(iterator position, const value_type &val)	{
																								static_cast<void>(position);
																								return this->insert(val).first;
																							}
			template <class Ite> void	insert(Ite first, Ite last)							{
																								while (first != last)
																									this->insert(*first++);
																							}
			void						erase(iterator position)							{this->erase(position++, position);}
			size_type					erase(const key_type &k)							{
																								iterator element = this->find(k);
																								if (element == this->end())
																									return (0);
																								this->_del_node(element.base());
																								return (1);
																							}
			void						erase(iterator first, iterator last)				{
																								while (first != last)
																									this->_del_node((first++).base());	
																							}

			void						swap(map &x)										{
																								node_ptr		tmp_data = this->_data;
																								key_compare		tmp_cmp = this->_cmp;
																								allocator_type	tmp_alloc = this->_alloc;
																								size_type		tmp_size = this->_size;
																								this->_data = x._data;
																								x._data = tmp_data;
																								this->_cmp = x._cmp;
																								x._cmp = tmp_cmp;
																								this->_alloc = x._alloc;
																								x._alloc = tmp_alloc;
																								this->_size = x._size;
																								x._size = tmp_size;
																								
																							}

			size_type		count(const key_type &k) const	{return (find(k) != this->end() ? 1 : 0);}
			iterator		find(const key_type &k)			{
																iterator it = this->begin(), ite = this->end();
																while (it != ite)
																{
																	if (!this->_cmp(it->first, k) && !this->_cmp(k, it->first))
																		break ;
																	++it;
																}
																return (it);
															}
			const_iterator	find(const key_type &k) const	{
																const_iterator it = this->begin(), ite = this->end();
																while (it != ite)
																{
																	if (!this->_cmp(it->first, k) && !this->_cmp(k, it->first))
																		break ;
																	++it;
																}
																return (it);
															}

			iterator								lower_bound(const key_type &k)			{
																								iterator it = this->begin(), ite = this->end();
																								while (it != ite)
																								{
																									if (!this->_cmp(it->first, k))
																										break;
																									++it;
																								}
																								return (it);
																							}
			const_iterator							lower_bound(const key_type &k) const	{
																								const_iterator it = this->begin(), ite = this->end();
																								while (it != ite)
																								{
																									if (!this->_cmp(it->first, k))
																										break;
																									++it;
																								}
																								return (it);
																							}
			iterator								upper_bound(const key_type &k)			{
																								iterator it = this->begin(), ite = this->end();
																								while (it != ite)
																								{
																									if (this->_cmp(k, it->first))
																										break;
																									++it;
																								}
																								return (it);
																							}
			const_iterator							upper_bound(const key_type &k) const	{
																								const_iterator it = this->begin(), ite = this->end();
																								while (it != ite)
																								{
																								if (this->_cmp(k, it->first))
																										break;
																									++it;
																								}
																								return (it);
																							}
			ft::pair<iterator,iterator>				equal_range(const key_type &k)			{
																								ft::pair<iterator, iterator> res;
																								res.first = this->lower_bound(k);
																								res.second = this->upper_bound(k);
																								return (res);
																							}
			ft::pair<const_iterator,const_iterator>	equal_range(const key_type &k) const	{
																								ft::pair<const_iterator, const_iterator> res;
																								res.first = this->lower_bound(k);
																								res.second = this->upper_bound(k);
																								return (res);
																							}

		private:
			node_ptr				_data;
			key_compare				_cmp;
			allocator_type			_alloc;
			size_type				_size;
			const static size_type	_max_size;

			void				_recursive_clear(node_ptr node)	{
																	if (node == NULL)
																		return ;
																	this->_recursive_clear(node->left);
																	this->_recursive_clear(node->right);
																	this->_alloc.deallocate(node, 1);
																}
			void				_add_node(node_ptr newnode)		{
																	node_ptr	*parent = &this->_data;
																	node_ptr	*node = &this->_data;
																	node_ptr	ghost = rightmost(this->_data);
																	bool		side_left = -1;

																	++this->_size;
																	while (*node && *node != ghost)
																	{
																		parent = node;
																		side_left = this->_cmp(newnode->data.first, (*node)->data.first);
																		node = (side_left ? &(*node)->left : &(*node)->right);
																	}
																	if (*node == NULL)
																	{
																		newnode->parent = (*parent);
																		*node = newnode;
																	}
																	else // if (*node == ghost)
																	{
																		*node = newnode;
																		newnode->parent = ghost->parent;
																		ghost->parent = rightmost(newnode); // Using rightmost(newnode)
																		rightmost(newnode)->right = ghost; // in case newnode isnt alone
																	}
																}
			void				_del_node(node_ptr rmnode)		{
																	node_ptr	replaceNode = NULL;
																	node_ptr	*rmPlace = &this->_data;

																	--this->_size;
																	if (rmnode->parent)
																		rmPlace = (rmnode->parent->left == rmnode ? &rmnode->parent->left : &rmnode->parent->right);
																	if (rmnode->left == NULL && rmnode->right == NULL)
																		;
																	else if (rmnode->left == NULL) // left == NULL && right != NULL
																		replaceNode = rmnode->right;
																	else // left != NULL && right ?= NULL
																	{
																		replaceNode = rightmost(rmnode->left);
																		if (replaceNode != rmnode->left)
																			if ((replaceNode->parent->right = replaceNode->left))
																				replaceNode->left->parent = replaceNode->parent;
																	}
																	if (replaceNode)
																	{
																		replaceNode->parent = rmnode->parent;
																		if (rmnode->left && rmnode->left != replaceNode)
																		{
																			replaceNode->left = rmnode->left;
																			replaceNode->left->parent = replaceNode;
																		}
																		if (rmnode->right && rmnode->right != replaceNode)
																		{
																			replaceNode->right = rmnode->right;
																			replaceNode->right->parent = replaceNode;
																		}
																	}
																	*rmPlace = replaceNode;
																	this->_alloc.deallocate(rmnode, 1);;
																}

	};

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {if (lhs.size() != rhs.size()) return false; return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));}
	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {return !(lhs == rhs);}
	template <class Key, class T, class Compare, class Alloc>
	bool	operator< (const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}
	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {return !(rhs < lhs);}
	template <class Key, class T, class Compare, class Alloc>
	bool	operator> (const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {return (rhs < lhs);}
	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs) {return !(lhs < rhs);}
	template <class Key, class T, class Compare, class Alloc>
	void	swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) {x.swap(y);}
}

#endif