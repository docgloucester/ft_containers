/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:35:16 by rgilles           #+#    #+#             */
/*   Updated: 2022/01/31 00:03:47 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_MAP_HPP
#define ITERATOR_MAP_HPP

#include "../common/iterator_traits.hpp"

namespace ft
{
	template <class T, class node_ptr>
	class tree_iterator : public ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T>>
	{
		public:
			typedef typename iterator_traits<T>::reference	reference;
			typedef typename iterator_traits<T>::pointer	pointer;
			typedef std::bidirectional_iterator_tag			iterator_category;

			tree_iterator()											: _currnode(NULL)		{}
			explicit tree_iterator(node_ptr ptr)					: _currnode(ptr)		{}
			template <class T1, class node_ptr1>
			tree_iterator (const tree_iterator<T1, node_ptr1>& it)	: _currnode(it.base())	{}

			node_ptr		base() const		{return this->_currnode;}
			reference		operator*() const	{return (this->_currnode->_data);}
			pointer			operator->() const	{return (&(this->_currnode->_data));}
			tree_iterator&	operator++()		{
													if (this->_currnode->right)
													{
														this->_currnode = this->_currnode->right;
														while (this->_currnode->left)
															this->_currnode = this->_currnode->left;
													}
													else
													{
														while (this->_currnode->parent && this->_currnode == this->_currnode->parent->right)
															this->_currnode = this->_currnode->parent;
													}
													return (*this);
												}
			tree_iterator&	operator--()		{
													if (this->_currnode->left)
													{
														this->_currnode = this->_currnode->left;
														while (this->_currnode->right)
															this->_currnode = this->_currnode->right;
													}
													else
													{
														while (this->_currnode->parent && this->_currnode == this->_currnode->parent->left)
															this->_currnode = this->_currnode->parent;
													}
													return (*this);
												}
			tree_iterator	operator++(int)		{tree_iterator itr(*this); ++(*this); return (itr);}
			tree_iterator	operator--(int)		{tree_iterator itr(*this); --(*this); return (itr);}
		private:
			node_ptr	_currnode;
	};
	template <class T, class node_ptr>
	bool  operator==(const tree_iterator<T, node_ptr>& x, const tree_iterator<T, node_ptr>& y)	{return (x.base() == y.base());}
	template <class T, class node_ptr>
	bool  operator!=(const tree_iterator<T, node_ptr>& x, const tree_iterator<T, node_ptr>& y)	{return (!(x == y));}
}

#endif