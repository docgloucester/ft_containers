/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 16:55:16 by rgilles           #+#    #+#             */
/*   Updated: 2021/11/13 17:11:32 by rgilles          ###   ########.fr       */
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
		VectorIterator() {}
		VectorIterator(const pointer vector) : _p(vector) {}
		VectorIterator(const iterator &it) : _p(it._p) {}
		iterator &operator=(const iterator &it)
		{
			if (*this != it)
				this->_p = it._p;
			return (*this);
		}
		~VectorIterator() {}

		reference	operator*() const {return (*_p);}
		reference	operator->() const {return (_p);}
		reference	operator[](int i) const {return (*(_p + i));}
		iterator	operator++() {++_p; return (*this);}
		iterator	operator--() {--_p; return (*this);}
		iterator	operator++(int) {iterator tmp(*this); ++_p; return(tmp);}
		iterator	operator--(int) {iterator tmp(*this); --_p; return(tmp);}
		iterator	operator+(size_t i) {return (iterator(_p + i));}
		iterator	operator-(size_t i) {return (iterator(_p - i));}

		difference_type operator-(const iterator& rhs) { return (this->_p - rhs._p); }

		// Non member Comparison operator overload
		friend bool	operator!=(const iterator &fst_it, const iterator &sec_it)
		{return (fst_it._p != sec_it._p);}
		friend bool	operator==(const iterator &fst_it, const iterator &sec_it)
		{return (fst_it._p == sec_it._p);}
		friend bool	operator>=(const iterator &fst_it, const iterator &sec_it)
		{return (fst_it._p >= sec_it._p);}
		friend bool	operator>(const iterator &fst_it, const iterator &sec_it)
		{return (fst_it._p > sec_it._p);}
		friend bool	operator<=(const iterator &fst_it, const iterator &sec_it)
		{return (fst_it._p <= sec_it._p);}
		friend bool	operator<(const iterator &fst_it, const iterator &sec_it)
		{return (fst_it._p < sec_it._p);}

	protected:
		T	*_p;
	};

	template <class T>
	class VectorConstIterator : public ft::iterator_traits<ft::random_access_iterator_tag, T>
	{
		public:
			typedef const T								value_type;
    		typedef const T*							pointer;
			typedef T&              					reference;
			typedef std::ptrdiff_t						difference_type;
			typedef ft::VectorConstIterator<T>			const_iterator;


		public:
		    T	*_pvector;

			// Coplien
		    VectorConstIterator() 							{}
		    VectorConstIterator(T *vector) : _pvector(vector)	{}
		    VectorConstIterator(const const_iterator &it) : _pvector(it._pvector) {} 
			VectorConstIterator(const ft::VectorIterator<T>	 &it) : _pvector(it._pvector) {}
			const_iterator &operator=(const_iterator &it) 	{
																if (*this != it)
                													this->_pvector = it._pvector;
            													return (*this); 
															}
			~VectorConstIterator()							{}

			// Operator overload
		    reference operator*() const				{ return (*_pvector); }
		    reference operator->() const			{ return (_pvector); }
			reference operator[](int i) const		{ return (*(_pvector + i)); }
		    const_iterator operator++()				{ ++_pvector; return (*this); }
		    const_iterator operator--()				{ --_pvector; return (*this); }
			const_iterator operator++(int)			{ const_iterator tmp(*this); ++_pvector; return(tmp); }
	    	const_iterator operator--(int)			{ const_iterator tmp(*this); --_pvector; return(tmp); }
			const_iterator operator+(size_t i)		{ const_iterator tmp(_pvector + i); return(tmp); }
	    	const_iterator operator-(size_t i)		{ const_iterator tmp(_pvector - i); return(tmp); }

			difference_type operator-(const const_iterator& rhs) { return (this->_pvector - rhs._pvector); }

			// Non member Comparison operator overload
		    friend bool	operator!=(const const_iterator &fst_it, const const_iterator &sec_it) 	{ return (fst_it._pvector != sec_it._pvector); }
		    friend bool	operator==(const const_iterator &fst_it, const const_iterator &sec_it) 	{ return (fst_it._pvector == sec_it._pvector); }
		    friend bool	operator>=(const const_iterator &fst_it, const const_iterator &sec_it) 	{ return (fst_it._pvector >= sec_it._pvector); }
		    friend bool	operator>(const const_iterator &fst_it, const const_iterator &sec_it) 	{ return (fst_it._pvector > sec_it._pvector); }
		    friend bool	operator<=(const const_iterator &fst_it, const const_iterator &sec_it) 	{ return (fst_it._pvector <= sec_it._pvector); }
		    friend bool	operator<(const const_iterator &fst_it, const const_iterator &sec_it) 	{ return (fst_it._pvector < sec_it._pvector); }
	};
}

#endif