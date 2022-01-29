/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 16:15:25 by rgilles           #+#    #+#             */
/*   Updated: 2022/01/29 17:33:01 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft 
{

	template <class Iterator>
	class reverse_iterator : public ft::iterator<	typename ft::iterator_traits<Iterator>::iterator_category,
													typename ft::iterator_traits<Iterator>::value_type,
													typename ft::iterator_traits<Iterator>::difference_type,
													typename ft::iterator_traits<Iterator>::pointer,
													typename ft::iterator_traits<Iterator>::reference>
	{
		public:
			typedef	Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;
			typedef typename iterator_traits<Iterator>::difference_type 	difference_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef	reverse_iterator<Iterator>								self;

			reverse_iterator()										: _current(NULL)		{}
			explicit reverse_iterator(iterator_type it)				: _current(it)			{}
			template <class Iter>
			reverse_iterator(const reverse_iterator<Iter>& cpy)		: _current(cpy.base())	{}
			template< class Iter >
			reverse_iterator&	operator=(const reverse_iterator<Iter>& rhs)				{this->_current = rhs.base(); return (*this);}
			

			iterator_type	base() const							{return this->_current;}
			reference		operator*() const						{return (*(--this->base()));}
			pointer			operator->() const						{return (&operator*());}
			reference		operator[] (difference_type n) const	{return (*(this->_current - n - 1));}
			self			operator+ (difference_type n) const		{return self(this->_current - n);}
			self&			operator++()							{--this->_current; return (*this);}
			self			operator++(int)							{self tmp = *this; --this->_current; return tmp;}
			self&			operator+= (difference_type n)			{this->_current -= n; return (*this);}
			self			operator- (difference_type n) const		{return self(this->_current + n);}
			self&			operator--()							{++this->_current; return (*this);}
			self 			operator--(int)							{self tmp = *this; ++this->_current; return (tmp);}
			self&			operator-= (difference_type n)			{this->_current += n; return (*this);}
		private:
			iterator_type _current;
	};

	template <class It>
	reverse_iterator<It>							operator+(typename reverse_iterator<It>::difference_type n, const reverse_iterator<It>& rev_it)	{return (reverse_iterator<It>(rev_it.base() - n));}
	template <class It1, class It2>
	typename reverse_iterator<It1>::difference_type	operator-(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)					{return (rhs.base() - lhs.base());}
	template <class It1, class It2>
	bool	operator==(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)	{return (rhs.base() == lhs.base());}
	template <class It1, class It2>
	bool	operator!=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)	{return (rhs.base() != lhs.base());}
	template <class It1, class It2>
	bool	operator< (const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)	{return (rhs.base() < lhs.base());}
	template <class It1, class It2>
	bool	operator<=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)	{return (rhs.base() <= lhs.base());}
	template <class It1, class It2>
	bool	operator> (const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)	{return (rhs.base() > lhs.base());}
	template <class It1, class It2>
	bool	operator>=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)	{return (rhs.base() >= lhs.base());}
}
#endif