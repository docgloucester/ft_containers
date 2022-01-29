/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:55:16 by rgilles           #+#    #+#             */
/*   Updated: 2022/01/29 17:33:00 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR
# define VECTOR_ITERATOR

#include "../common/iterator_traits.hpp"

namespace ft
{
	template <typename Iterator>
	class vector_iterator : public ft::iterator_traits<Iterator>
	{
		public:
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::vector_iterator<Iterator>						self;

			vector_iterator()														{}
			~vector_iterator()														{}
			template <class Iter>
			vector_iterator(const vector_iterator<Iter>& it)	: _p(it.base())	{}
			vector_iterator(const pointer pt)					: _p(pt)			{}
			self&	operator=(const self& it)
			{
				if (this != &it)
					this->_p = it._p;
				return (*this);
			}

			pointer		base() const						{return (this->_p);}
			pointer		operator->() const					{return (this->_p);}
			reference	operator*() const					{return (*this->_p);}
			reference	operator[](int i) const				{return (this->_p[i]);}
			self&		operator++()						{++this->_p; return (*this);}
			self&		operator+=(difference_type i)		{this->_p += i; return (*this);}
			self&		operator--()						{--this->_p; return (*this);}
			self&		operator-=(difference_type i)		{this->_p -= i; return (*this);}
			self		operator++(int)						{self tmp(*this); ++this->_p; return(tmp);}
			self		operator--(int)						{self tmp(*this); --this->_p; return(tmp);}
			self		operator+(difference_type i) const	{return (self(this->_p + i));}
			self		operator-(difference_type i) const	{return (self(this->_p - i));}

		private:
			pointer	_p;
	};

	template <class It>
	vector_iterator<It>								operator+(typename vector_iterator<It>::difference_type n, const vector_iterator<It>& it)	{return (it.base() + n);}
	template <class It1, class It2>
	typename vector_iterator<It1>::difference_type	operator-(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)					{return(lhs.base() - rhs.base());}
	template <class It1, class It2>
	bool	operator==(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)	{return (lhs.base() == rhs.base());}
	template <class It1, class It2>
	bool	operator!=(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)	{return (lhs.base() != rhs.base());}
	template <class It1, class It2>
	bool	operator< (const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)	{return (lhs.base() < rhs.base());}
	template <class It1, class It2>
	bool	operator<=(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)	{return (lhs.base() <= rhs.base());}
	template <class It1, class It2>
	bool	operator> (const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)	{return (lhs.base() > rhs.base());}
	template <class It1, class It2>
	bool	operator>=(const vector_iterator<It1>& lhs, const vector_iterator<It2>& rhs)	{return (lhs.base() >= rhs.base());}
}
#endif