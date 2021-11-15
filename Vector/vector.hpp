/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:43:07 by rgilles           #+#    #+#             */
/*   Updated: 2021/11/11 22:56:20 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <allocator>
# include <cstddef>
# #include "VectorIterator.hpp"

namespace ft
{
	template <class T, class Alloc>
	class vector
	{
	public:

		typedef	T value_type;
		typedef	Alloc allocator_type;
		typedef	allocator_type::reference reference;
		typedef	allocator_type::const_reference const_reference;
		typedef	allocator_type::pointer pointer;
		typedef	allocator_type::const_pointer const_pointer;
		typedef __gnu_cxx::__normal_iterator<pointer, vector> iterator;
		typedef __gnu_cxx::__normal_iterator<const_pointer, vector> const_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef	ptrdiff_t difference_type;
		typedef	size_t size_type;
		

		explicit vector(const allocator_type& alloc = allocator_type());
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
		vector(const vector& x);
		~vector() {};
		vector& operator=(const vector& x);

		//Iterators
		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		reverse_const_iterator	rbegin() const;
		reverse_iterator		rend();
		reverse_const_iterator	rend() const;

		//Capacity
		size_type	size() const;
		size_type	max_size() const;
		void		resize(size_type n, value_type val = value_type());
		size_type	capacity() const;
		bool		empty() const;
		void		reserve(size_type n);

		//Access
		reference		operator[](size_type n);
		const_reference	operator[](size_type n) const;
		reference		at(size_type n);
		const_reference	at(size_type n) const;
		reference		front();
		const_reference	front() const;
		reference		back();
		const_reference	back() const;

		//Modifiers
		template <class InputIterator>
		void		assign(InputIterator first, InputIterator last);
		void		assign(size_type n, const value_type& val);
		void		push_back (const value_type& val);
		void		pop_back();
		iterator	insert(iterator position, const value_type& val);
		void		insert(iterator position, size_type n, const value_type& val);
		template <class InputIterator>
		void		insert(iterator position, InputIterator first, InputIterator last);
		iterator	erase(iterator position);
		iterator	erase(iterator first, iterator last);
		void		swap(vector& x);
		void		clear();

		//Getter
		allocator_type	get_allocator() const;
	private:
		allocator_type	_a;

	};

	template <class T, class Alloc>
	bool	operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool	operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool	operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool	operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	void	swap(vector<T,Alloc>& x, vector<T,Alloc>& y);
}
#endif