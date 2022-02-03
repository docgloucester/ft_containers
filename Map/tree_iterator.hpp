/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:35:16 by rgilles           #+#    #+#             */
/*   Updated: 2022/02/03 15:17:47 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
#define TREE_ITERATOR_HPP

#include "../common/iterator_traits.hpp"

namespace ft
{
	template <class T, class node_ptr>
	class tree_iterator : public ft::iterator_traits<ft::iterator<std::bidirectional_iterator_tag, T> >
	{
		public:
			typedef typename iterator_traits<T>::reference	reference;
			typedef typename iterator_traits<T>::pointer	pointer;
			typedef std::bidirectional_iterator_tag			iterator_category;

			tree_iterator()											: _currnode(NULL)		{}
			explicit tree_iterator(node_ptr ptr)					: _currnode(ptr)		{}
			template <class T1, class node_ptr1>
			tree_iterator (const tree_iterator<T1, node_ptr1>& it)	: _currnode(it.base())	{}
			tree_iterator&	operator=(const tree_iterator& rhs)								{this->_currnode = rhs._currnode; return (*this);}

			node_ptr		base() const		{return this->_currnode;}
			reference		operator*() const	{return (this->_currnode->_data);}
			pointer			operator->() const	{return (&(this->_currnode->_data));}
			tree_iterator&	operator++()		{this->_currnode = this->_currnode->increment(); return (*this);}
			tree_iterator&	operator--()		{this->_currnode = this->_currnode->decrement(); return (*this);}
			tree_iterator	operator++(int)		{tree_iterator itr(*this); ++(*this); return (itr);}
			tree_iterator	operator--(int)		{tree_iterator itr(*this); --(*this); return (itr);}
		private:
			node_ptr	_currnode;
	};
	template <class It1, class It2, class node_ptr>
	bool  operator==(const tree_iterator<It1, node_ptr>& x, const tree_iterator<It2, node_ptr>& y)	{return (x.base() == y.base());}
	template <class It1, class It2, class node_ptr>
	bool  operator!=(const tree_iterator<It1, node_ptr>& x, const tree_iterator<It2, node_ptr>& y)	{return (!(x == y));}
}

#endif