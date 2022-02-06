/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:34:35 by rgilles           #+#    #+#             */
/*   Updated: 2022/02/06 17:14:30 by rgilles          ###   ########.fr       */
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
			typedef size_t											size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef Compare											key_compare;
			typedef Alloc											allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::node<value_type>							node_type;
			typedef node_type*										node_ptr;
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

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())	: _root(), _cmp(comp), _alloc(alloc), _size(0), _val_compare(_cmp)
																													{this->_root = this->_alloc.allocate(1); this->_alloc.construct(this->_root, node_type());}
			template <class Ite>
			map(typename ft::enable_if<!ft::is_integral<Ite>::value, Ite>::type first, Ite last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
																													: _root(), _cmp(comp), _alloc(alloc), _size(0), _val_compare(_cmp)
																													{this->_root = this->_alloc.allocate(1); this->_alloc.construct(this->_root, node_type()); this->insert(first, last);}
			map(const map& src)																						: _root(), _cmp(key_compare()), _alloc(allocator_type()), _size(0), _val_compare(_cmp)
																													{this->_root = this->_alloc.allocate(1); this->_alloc.construct(this->_root, node_type()); *this = src;}
			virtual ~map(void)																						{this->clear(); this->_alloc.deallocate(this->_root, 1);}
			map&	operator=(map const &rhs)																		{
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
			mapped_type&		at(const key_type& k)			{																	// retroactively added to c++98 standard
																	iterator it = this->find(k);
																	if (it == this->end())
																		throw std::out_of_range("No such key.");
																	return ((*it).second);
																}
			const mapped_type&	at(const key_type& k) const		{																	// idem
																	const_iterator it = this->find(k);
																	if (it == this->end())
																		throw std::out_of_range("No such key.");
																	return ((*it).second);
																}

			iterator				begin(void)			{return (iterator(leftmost(this->_root)));}
			const_iterator			begin(void) const	{return (const_iterator(leftmost(this->_root)));}
			iterator				end(void)			{return (iterator(rightmost(this->_root)));}
			const_iterator			end(void) const		{return (const_iterator(rightmost(this->_root)));}
			reverse_iterator		rbegin(void)		{return (reverse_iterator(this->end()));}
			const_reverse_iterator	rbegin(void) const	{return (const_reverse_iterator(this->end()));}
			reverse_iterator		rend(void)			{return (reverse_iterator(this->begin()));}
			const_reverse_iterator	rend(void) const	{return (const_reverse_iterator(this->begin()));}


			void						clear(void)											{
																								if (this->_size == 0)
																									return ;
																								node_ptr endnode = this->end().base();
																								endnode->parent->right = NULL;
																								this->_recursive_clear(this->_root);
																								this->_root = endnode;
																								this->_size = 0;
																							}
			ft::pair<iterator, bool>	insert(const value_type& val)						{
																								ft::pair<iterator, bool> res;
																								res.first = this->find(val.first);
																								if (res.first == this->end())
																								{
																									node_ptr	newnode = this->_alloc.allocate(1);
																									this->_alloc.construct(newnode, node_type(val));
																									this->_add_node(newnode);
																									res.first = iterator(newnode);
																									res.second = true;
																								}
																								else
																									res.second = false;																							
																								return (res);
																							}
			iterator					insert(iterator position, const value_type& val)	{
																								static_cast<void>(position);
																								return this->insert(val).first;
																							}
			template <class Ite>
			void						insert(Ite first, Ite last)							{
																								while (first != last)
																									this->insert(*first++);
																							}
			size_type					erase(const key_type& k)							{
																								iterator it = this->find(k);
																								if (it == this->end())
																									return (0);
																								this->_del_node(it.base());
																								return (1);
																							}
			void						erase(iterator position)							{this->_del_node(position.base());}
			void						erase(iterator first, iterator last)				{while (first != last) this->erase(first++);}
			void						swap(map& x)										{
																								node_ptr		tmp_root = this->_root;
																								key_compare		tmp_cmp = this->_cmp;
																								allocator_type	tmp_alloc = this->_alloc;
																								size_type		tmp_size = this->_size;
																								this->_root = x._root;
																								x._root = tmp_root;
																								this->_cmp = x._cmp;
																								x._cmp = tmp_cmp;
																								this->_alloc = x._alloc;
																								x._alloc = tmp_alloc;
																								this->_size = x._size;
																								x._size = tmp_size;
																								
																							}

			size_type		count(const key_type& k) const	{return (find(k) != this->end() ? 1 : 0);}
			iterator		find(const key_type& k)			{
																node_ptr	curr = this->_root;
																while (curr && (this->_cmp(curr->data.first, k) || this->_cmp(k, curr->data.first)))
																{
																	if (this->_cmp(k, curr->data.first))
																		curr = curr->left;
																	else
																		curr = curr->right;
																}
																if (curr)
																	return (iterator(curr));
																else
																	return (this->end());
															}
			const_iterator	find(const key_type& k) const	{
																node_ptr	curr = this->_root;
																while (curr && (this->_cmp(curr->data.first, k) || this->_cmp(k, curr->data.first)))
																{
																	if (this->_cmp(k, curr->data.first))
																		curr = curr->left;
																	else
																		curr = curr->right;
																}
																if (curr)
																	return (const_iterator(curr));
																else
																	return (this->end());
															}

			iterator								lower_bound(const key_type& k)			{
																								iterator	it = this->begin();
																								iterator	ite = this->end();
																								while (it != ite)
																								{
																									if (!this->_cmp(it->first, k))
																										break;
																									++it;
																								}
																								return (it);
																							}
			const_iterator							lower_bound(const key_type& k) const	{
																								const_iterator	it = this->begin();
																								const_iterator	ite = this->end();
																								while (it != ite)
																								{
																									if (!this->_cmp(it->first, k))
																										break;
																									++it;
																								}
																								return (it);
																							}
			iterator								upper_bound(const key_type& k)			{
																								iterator	it = this->begin();
																								iterator	ite = this->end();
																								while (it != ite)
																								{
																									if (this->_cmp(k, it->first))
																										break;
																									++it;
																								}
																								return (it);
																							}
			const_iterator							upper_bound(const key_type& k) const	{
																								const_iterator	it = this->begin();
																								const_iterator	ite = this->end();
																								while (it != ite)
																								{
																								if (this->_cmp(k, it->first))
																										break;
																									++it;
																								}
																								return (it);
																							}
			ft::pair<iterator,iterator>				equal_range(const key_type& k)			{
																								ft::pair<iterator, iterator> res;
																								res.first = this->lower_bound(k);
																								res.second = this->upper_bound(k);
																								return (res);
																							}
			ft::pair<const_iterator,const_iterator>	equal_range(const key_type& k) const	{
																								ft::pair<const_iterator, const_iterator> res;
																								res.first = this->lower_bound(k);
																								res.second = this->upper_bound(k);
																								return (res);
																							}

		private:
			node_ptr				_root;
			key_compare				_cmp;
			allocator_type			_alloc;
			size_type				_size;
			value_compare			_val_compare;

			void				_recursive_clear(node_ptr curr)	{
																	if (curr == NULL)
																		return ;
																	this->_recursive_clear(curr->left);
																	this->_recursive_clear(curr->right);
																	this->_alloc.deallocate(curr, 1);
																}
			void				_add_node(node_ptr to_add)		{
																	node_ptr*	parent = &this->_root;
																	node_ptr*	curr = &this->_root;
																	node_ptr	endnode = rightmost(this->_root);
																	bool		which_direction;
																	++this->_size;
																	while (*curr && *curr != endnode)
																	{
																		parent = curr;
																		which_direction = _val_compare(to_add->data, (*curr)->data);
																		curr = (which_direction ? &(*curr)->left : &(*curr)->right);
																	}
																	if (*curr == NULL)
																	{
																		to_add->parent = (*parent);
																		*curr = to_add;
																	}
																	else
																	{
																		*curr = to_add;
																		to_add->parent = endnode->parent;
																		endnode->parent = rightmost(to_add);
																		rightmost(to_add)->right = endnode;
																	}
																	//this->_balance_on_insert(to_add);
																}
			void				_del_node(node_ptr to_del)		{
																	if (!to_del->left)
																	{
																		if (!to_del->parent)
																			this->_root = to_del->right;
																		else if (to_del == to_del->parent->left)
																			to_del->parent->left = to_del->right;
																		else
																			to_del->parent->right = to_del->right;
																		if (to_del->right)
																			to_del->right->parent = to_del->parent;
																	}
																	else if (!to_del->right)
																	{
																		if (!to_del->parent)
																			this->_root = to_del->left;
																		else if (to_del == to_del->parent->left)
																			to_del->parent->left = to_del->left;
																		else
																			to_del->parent->right = to_del->left;
																		to_del->left->parent = to_del->parent;
																	}
																	else
																	{
																		node_ptr	successor = leftmost(to_del->right);
																		if (!(to_del == successor->parent))
																		{
																			if (successor == successor->parent->left)
																				successor->parent->left = successor->right;
																			else
																				successor->parent->right = successor->right;
																			if (successor->right != NULL)
																				successor->right->parent = successor->parent;
																			successor->right = to_del->right;
																			successor->right->parent = successor;
																			
																		}
																		if (!to_del->parent)
																			this->_root = successor;
																		else if (to_del == to_del->parent->left)
																			to_del->parent->left = successor;
																		else
																			to_del->parent->right = successor;
																		successor->parent = to_del->parent;
																		successor->left = to_del->left;
																		successor->left->parent = successor;

																	}
																	--this->_size;
																	this->_alloc.deallocate(to_del, 1);
																}

			node_ptr	_rotate_left(node_ptr to_rotate)	{
																node_ptr	r = to_rotate->right;
																to_rotate->right = r->left;
																r->left = to_rotate;
																to_rotate->height = std::max((to_rotate->right ? to_rotate->right->height : 0), (to_rotate->left ? to_rotate->left->height : 0)) + 1;
																r->height = std::max((r->right ? r->right->height : 0), (r->left ? r->left->height : 0)) + 1;
																return (r);
															}
			node_ptr	_rotate_right(node_ptr to_rotate)	{
																node_ptr	l = to_rotate->left;
																to_rotate->left = l->right;
																l->right = to_rotate;
																to_rotate->height = std::max((to_rotate->right ? to_rotate->right->height : 0), (to_rotate->left ? to_rotate->left->height : 0)) + 1;
																l->height = std::max((l->right ? l->right->height : 0), (l->left ? l->left->height : 0)) + 1;
																return (l);
															}
			node_ptr	_rotate_right_left(node_ptr to_rot)	{
																to_rot->right = this->_rotate_right(to_rot->right);
																to_rot = this->_rotate_left(to_rot);
																to_rot->height = std::max((to_rot->right ? to_rot->right->height : 0), (to_rot->left ? to_rot->left->height : 0)) + 1;
																return (to_rot);
															}
			node_ptr	_rotate_left_right(node_ptr to_rot)	{
																to_rot->left = this->_rotate_left(to_rot->left);
																to_rot = this->_rotate_right(to_rot);
																to_rot->height = std::max((to_rot->right ? to_rot->right->height : 0), (to_rot->left ? to_rot->left->height : 0)) + 1;
																return (to_rot);
															}
			node_ptr	_rebalance(node_ptr	start)			{
																if (start->get_bal() < -1 && start->left->get_bal() == -1)
																	return (this->_rotate_right(start));
																else
																if (start->get_bal() >  1 && start->right->get_bal() == 1)
																	return (this->_rotate_left(start));
																else
																if (start->get_bal() < -1 && start->left->get_bal() == 1)
																	return (this->_rotate_left_right(start));
																else
																if (start->get_bal() >  1 && start->right->get_bal() == -1)
																	return (this->_rotate_right_left(start));
																else
																	return (start);	
			}
			void		_balance_on_insert(node_ptr start)	{
																if (start->get_bal() < -1 || start->get_bal() > 1)
																{
																	this->_rebalance(start);
																	return ;
																}
																if (start->parent)
																{
																	node_ptr tmp = start;
																	while (tmp != this->_root)
																	{
																		tmp->parent->height++;
																		tmp = tmp->parent;
																	}
																	this->_rebalance(start->parent);
																}														
			}

	};

	template <class Key, class T, class Compare, class Alloc>
	bool	operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {if (lhs.size() != rhs.size()) return false; return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));}
	template <class Key, class T, class Compare, class Alloc>
	bool	operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {return !(lhs == rhs);}
	template <class Key, class T, class Compare, class Alloc>
	bool	operator< (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}
	template <class Key, class T, class Compare, class Alloc>
	bool	operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {return !(rhs < lhs);}
	template <class Key, class T, class Compare, class Alloc>
	bool	operator> (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {return (rhs < lhs);}
	template <class Key, class T, class Compare, class Alloc>
	bool	operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {return !(lhs < rhs);}
	template <class Key, class T, class Compare, class Alloc>
	void	swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y) {x.swap(y);}
}

#endif