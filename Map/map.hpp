/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:34:35 by rgilles           #+#    #+#             */
/*   Updated: 2022/02/03 23:02:14 by rgilles          ###   ########.fr       */
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

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> >	 >
	class map
	{
		public:

			typedef Key											key_type;
			typedef T											mapped_type;
			typedef ft::pair<const key_type, mapped_type>		value_type;
			typedef Compare										key_compare;
			class												value_compare;

			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::node<value_type>						node_type;
			typedef node_type*									node_ptr;

			typedef std::ptrdiff_t									difference_type;
			typedef size_t										size_type;

			typedef ft::tree_iterator<value_type, node_type>			iterator;
			typedef ft::tree_iterator<const value_type, node_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		// ************************** Member functions ****************************** //

			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())	: _data(), _key_cmp(comp), _alloc(alloc), _size(0)
																													{this->_data = new node_type;}
			template <class Ite>
			map(typename ft::enable_if<!ft::is_integral<Ite>::value, Ite>::type first, Ite last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
																													: _data(), _key_cmp(comp), _alloc(alloc), _size(0)
																													{this->_data = new node_type; this->insert(first, last);}
			map(const map &src)																						: _data(), _key_cmp(key_compare()), _alloc(allocator_type()), _size(0)
																													{this->_data = new node_type; *this = src;}
			virtual ~map(void)																						{this->clear(); delete this->_data;}
			map	&operator=(map const &rhs)																			{
																														if (this != &rhs)
																														{
																															this->clear();
																															this->insert(rhs.begin(), rhs.end());
																														}
																														return (*this);
																													}
		// ****************************** Iterators ********************************* //

			iterator				begin(void)			{return (iterator(leftmost(this->_data)));}
			const_iterator			begin(void) const	{return (const_iterator(leftmost(this->_data)));}
			iterator				end(void)			{return (iterator(rightmost(this->_data)));}
			const_iterator			end(void) const		{return (const_iterator(rightmost(this->_data)));}

			reverse_iterator		rbegin(void)		{return (reverse_iterator(this->end()));}
			const_reverse_iterator	rbegin(void) const	{return (const_reverse_iterator(this->end()));}
			reverse_iterator		rend(void)			{return (reverse_iterator(this->begin()));}
			const_reverse_iterator	rend(void) const	{return (const_reverse_iterator(this->begin()));}

		// ******************************* Capacity ********************************* //

			size_type	size(void) const		{return (this->_size);}
			size_type	max_size(void) const	{return (this->_alloc.max_size());}
			bool		empty(void) const		{return (this->_size == 0 ? true : false);}

		// ******************************* Ele Access ******************************* //

			mapped_type	&operator[](const key_type &k)	{return (this->insert(value_type(k, mapped_type()))).first->second;}

		// ******************************** Modifiers ******************************* //

			ft::pair<iterator, bool>	insert(const value_type &val)						{
																								ft::pair<iterator, bool> res;
																								res.second = !this->count(val.first);
																								if (res.second == true)
																									this->_btree_add(new node_type(val));
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
			void		erase(iterator position)											{this->erase(position++, position);}
			size_type	erase(const key_type &k)											{
																								iterator element = this->find(k);
																								if (element == this->end())
																									return (0);
																								this->_btree_rm(element.base());
																								return (1);
																							}
			void		erase(iterator first, iterator last)								{
																								while (first != last)
																									this->_btree_rm((first++).base());	
																							}

			void		swap(map &x)														{
																								map	tmp;
																								tmp._cpy_content(x);
																								x._cpy_content(*this);
																								this->_cpy_content(tmp);
																							}
			void		clear(void)															{
																								if (this->_size == 0)
																									return ;
																								node_ptr ghost = this->end().base();
																								ghost->parent->right = NULL;
																								this->_btree_clear(this->_data);
																								this->_data = ghost;
																								this->_size = 0;
																							}

		// ******************************* Observers ******************************** //

			key_compare		key_comp(void) const	{return (key_compare());}
			value_compare	value_comp(void) const	{return (value_compare(key_compare()));}

		// ******************************* Operations ******************************* //

			iterator		find(const key_type &k)										{
																							iterator it = this->begin(), ite = this->end();
																							while (it != ite)
																							{
																								if (this->_key_eq(it->first, k))
																									break ;
																								++it;
																							}
																							return (it);
																						}
			const_iterator	find(const key_type &k) const								{
																							const_iterator it = this->begin(), ite = this->end();
																							while (it != ite)
																							{
																								if (this->_key_eq(it->first, k))
																									break ;
																								++it;
																							}
																							return (it);
																						}
			size_type		count(const key_type &k) const								{return (find(k) != this->end() ? 1 : 0);}

			iterator		lower_bound(const key_type &k)								{
																							iterator it = this->begin(), ite = this->end();
																							while (it != ite)
																							{
																								if (!this->_key_cmp(it->first, k))
																									break;
																								++it;
																							}
																							return (it);
																						}
			const_iterator	lower_bound(const key_type &k) const						{
																							const_iterator it = this->begin(), ite = this->end();
																							while (it != ite)
																							{
																								if (!this->_key_cmp(it->first, k))
																									break;
																								++it;
																							}
																							return (it);
																						}
			iterator		upper_bound(const key_type &k)								{
																							iterator it = this->begin(), ite = this->end();
																							while (it != ite)
																							{
																								if (this->_key_cmp(k, it->first))
																									break;
																								++it;
																							}
																							return (it);
																						}
			const_iterator	upper_bound(const key_type &k) const						{
																							const_iterator it = this->begin(), ite = this->end();
																							while (it != ite)
																							{
																								if (this->_key_cmp(k, it->first))
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
		// ******************************* Non-public ******************************* //

		private:
			node_ptr				_data;
			key_compare				_key_cmp;
			allocator_type			_alloc;
			size_type				_size;
			const static size_type	_max_size;

			//template <class Ite>
			//void				_create_data_it(Ite first, Ite last);
			//void				_create_data(size_type size, const value_type &val = value_type());
			void				_cpy_content(map &src);

			void				_btree_clear(node_ptr node);
			void				_btree_add(node_ptr node);
			void				_btree_rm(node_ptr node);

			bool				_key_eq(const key_type &k1, const key_type &k2) const;

	}; // ***************************************************** class ft::map end //


// ################################ Private ####################################

/*template<class Key, class T, class Compare, class Alloc> template <class Ite>
void	map<Key, T, Compare, Alloc>::_create_data_it(Ite first, Ite last) {
	this->insert(first, last);
}*/
/*
template<class Key, class T, class Compare, class Alloc>
void	map<Key, T, Compare, Alloc>::_create_data(size_type size, const value_type &val) {
	(void)size; (void)val;
}*/

template<class Key, class T, class Compare, class Alloc>
void	map<Key, T, Compare, Alloc>::_cpy_content(map &src) {
	this->clear();
	node_ptr tmp = this->_data;

	this->_data = src._data;
	this->_key_cmp = src._key_cmp;
	this->_alloc = src._alloc;
	this->_size = src._size;
	src._data = tmp; src._size = 0;
	tmp = NULL;
}

template<class Key, class T, class Compare, class Alloc>
void	map<Key, T, Compare, Alloc>::_btree_clear(node_ptr node) {
	if (node == NULL)
		return ;
	this->_btree_clear(node->left);
	this->_btree_clear(node->right);
	delete node;
}

template<class Key, class T, class Compare, class Alloc>
void	map<Key, T, Compare, Alloc>::_btree_add(node_ptr newNode) {
	node_ptr	*parent = &this->_data;
	node_ptr	*node = &this->_data;
	node_ptr	ghost = rightmost(this->_data);
	bool		side_left = -1;

	++this->_size;
	while (*node && *node != ghost)
	{
		parent = node;
		side_left = this->_key_cmp(newNode->data.first, (*node)->data.first);
		node = (side_left ? &(*node)->left : &(*node)->right);
	}
	if (*node == NULL)
	{
		newNode->parent = (*parent);
		*node = newNode;
	}
	else // if (*node == ghost)
	{
		*node = newNode;
		newNode->parent = ghost->parent;
		ghost->parent = rightmost(newNode); // Using rightmost(newNode)
		rightmost(newNode)->right = ghost; // in case newNode isnt alone
	}
}

template<class Key, class T, class Compare, class Alloc>
void	map<Key, T, Compare, Alloc>::_btree_rm(node_ptr rmNode) {
	node_ptr	replaceNode = NULL;
	node_ptr	*rmPlace = &this->_data;

	--this->_size;
	if (rmNode->parent)
		rmPlace = (rmNode->parent->left == rmNode ? &rmNode->parent->left : &rmNode->parent->right);
	if (rmNode->left == NULL && rmNode->right == NULL)
		;
	else if (rmNode->left == NULL) // left == NULL && right != NULL
		replaceNode = rmNode->right;
	else // left != NULL && right ?= NULL
	{
		replaceNode = rightmost(rmNode->left);
		if (replaceNode != rmNode->left)
			if ((replaceNode->parent->right = replaceNode->left))
				replaceNode->left->parent = replaceNode->parent;
	}
	if (replaceNode)
	{
		replaceNode->parent = rmNode->parent;
		if (rmNode->left && rmNode->left != replaceNode)
		{
			replaceNode->left = rmNode->left;
			replaceNode->left->parent = replaceNode;
		}
		if (rmNode->right && rmNode->right != replaceNode)
		{
			replaceNode->right = rmNode->right;
			replaceNode->right->parent = replaceNode;
		}
	}
	*rmPlace = replaceNode;
	delete rmNode;
}

template<class Key, class T, class Compare, class Alloc>
bool
map<Key, T, Compare, Alloc>::_key_eq(const key_type &k1, const key_type &k2) const {
	return (!this->_key_cmp(k1, k2) && !this->_key_cmp(k2, k1));
}

// ####################### Non-member function overloads #######################

template <class Key, class T, class Compare, class Alloc>
bool	operator==(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	if (lhs.size() != rhs.size())
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class Key, class T, class Compare, class Alloc>
bool	operator!=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool	operator< (const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool	operator<=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool	operator> (const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	return (rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool	operator>=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	return !(lhs < rhs);
}

template <class Key, class T, class Compare, class Alloc>
void	swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) {
	x.swap(y);
}

// ################################## Other ####################################

template <class Key, class T, class Compare, class Alloc>
class	map<Key, T, Compare, Alloc>::value_compare {
	public:
	Compare comp;
	value_compare(Compare c) : comp(c) { };

	typedef bool		result_type;
	typedef value_type	first_argument_type;
	typedef value_type	second_argument_type;
	bool	operator()(const value_type &x, const value_type &y) const {
		return comp(x.first, y.first);
	}
};

} // ******************************************************* ft namespace end //

#endif