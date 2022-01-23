/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:55:16 by rgilles           #+#    #+#             */
/*   Updated: 2022/01/23 17:46:27 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

namespace ft
{
	template <class T>
	class VectorIterator// : public ft::iterator_traits<ft::random_access_iterator_tag, T>
	{
		public:
			typedef T						value_type;
			typedef T*						pointer;
			typedef T&						reference;
			typedef std::ptrdiff_t			difference_type;
			typedef ft::VectorIterator<T>	iterator;

			VectorIterator()										{}
			~VectorIterator()										{}
			VectorIterator(const iterator& it)		: _p(it._p)		{}
			VectorIterator(const pointer vector)	: _p(vector)	{}
			iterator&	operator=(const iterator& it)
			{
				if (this != &it)
					this->_p = it._p;
				return (*this);
			}

			reference		operator*() const				{return (*this->_p);}
			reference		operator->() const				{return (this->_p);}
			reference		operator[](int i) const			{return (this->_p[i]);}
			iterator		operator++()					{++this->_p; return (*this);}
			iterator		operator--()					{--this->_p; return (*this);}
			iterator		operator++(int)					{iterator tmp(*this); ++this->_p; return(tmp);}
			iterator		operator--(int)					{iterator tmp(*this); --this->_p; return(tmp);}
			iterator		operator+(size_t i)				{return (iterator(this->_p + i));}
			iterator		operator-(size_t i)				{return (iterator(this->_p - i));}
			difference_type	operator-(const iterator& rhs)	{return(this->_p - rhs._p);}

			friend bool	operator==(const iterator& lhs, const iterator& rhs)	{return (lhs._p == rhs._p);}
			friend bool	operator!=(const iterator& lhs, const iterator& rhs)	{return (lhs._p != rhs._p);}
			friend bool	operator<(const iterator& lhs, const iterator& rhs)		{return (lhs._p < rhs._p);}
			friend bool	operator<=(const iterator& lhs, const iterator& rhs)	{return (lhs._p <= rhs._p);}
			friend bool	operator>(const iterator& lhs, const iterator& rhs)		{return (lhs._p > rhs._p);}
			friend bool	operator>=(const iterator& lhs, const iterator& rhs)	{return (lhs._p >= rhs._p);}

		protected:
			pointer	_p;
	};

/*******************************************************************************************/

	template <class T>
	class VectorConstIterator// : public ft::iterator_traits<ft::random_access_iterator_tag, T>
	{
		public:
			typedef const T								value_type;
			typedef const T*							pointer;
			typedef T&									reference;
			typedef std::ptrdiff_t						difference_type;
			typedef ft::VectorConstIterator<T>			const_iterator;

			VectorConstIterator()													{}
			~VectorConstIterator()													{}
			VectorConstIterator(const const_iterator& it)			: _p(it._p)		{}
			VectorConstIterator(const ft::VectorIterator<T>& it)	: _p(it._p)		{}
			VectorConstIterator(pointer vector)						: _p(vector)	{}
			const_iterator&	operator=(const_iterator& it)
			{
				if (this != &it)
					this->_p = it._p;
				return (*this);
			}

			reference		operator*() const						{return (*this->_p);}
			reference		operator->() const						{return (this->_p);}
			reference		operator[](int i) const					{return (*(this->_p + i));}
			const_iterator	operator+(size_t i)						{return(const_iterator(this->_p + i));}
			const_iterator	operator-(size_t i)						{return(const_iterator(this->_p - i));}
			difference_type	operator-(const const_iterator& rhs)	{return (this->_p - rhs._p);}

			friend bool	operator==(const const_iterator& lhs, const const_iterator& rhs)	{return (lhs._p == rhs._p);}
			friend bool	operator!=(const const_iterator& lhs, const const_iterator& rhs)	{return (lhs._p != rhs._p);}
			friend bool	operator<(const const_iterator& lhs, const const_iterator& rhs)		{return (lhs._p < rhs._p);}
			friend bool	operator<=(const const_iterator& lhs, const const_iterator& rhs)	{return (lhs._p <= rhs._p);}
			friend bool	operator>(const const_iterator& lhs, const const_iterator& rhs)		{return (lhs._p > rhs._p);}
			friend bool	operator>=(const const_iterator& lhs, const const_iterator& rhs)	{return (lhs._p >= rhs._p);}


		protected:
			pointer	_p;
	};
}

#endif