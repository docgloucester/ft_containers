/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:43:07 by rgilles           #+#    #+#             */
/*   Updated: 2022/01/29 17:33:03 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include "vector_iterator.hpp"
# include "../common/reverse_iterator.hpp"
# include "../common/LexicographicalCompare.hpp"
# include "../common/Equal.hpp"
# include "../common/enable_if.hpp"
# include "../common/is_integral.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef vector_iterator<pointer>					iterator;
			typedef vector_iterator<const_pointer>				const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
			typedef std::ptrdiff_t								difference_type;
			typedef size_t										size_type;

			explicit vector(const allocator_type& alloc = allocator_type())														: _alloc(alloc), _arr(NULL), _size(0), _capacity(0)	{}
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())	: _alloc(alloc), _arr(NULL), _size(n), _capacity(n)	{
																																														this->_arr = this->_alloc.allocate(this->_capacity);
																																														for (size_t i = 0; i < this->_size; i++)
																																															this->_alloc.construct(this->_arr + i, val);
																																													}
			template <class InputIterator>
			vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
																	const allocator_type& alloc = allocator_type())				:  _alloc(alloc),_size(0), _capacity(0)				{
																																														for (; first != last; first++)
																																															this->push_back(*first);
																																													}
			vector(const vector& x)																								: _capacity(0)										{*this = x;}
			~vector()																																								{
																																														if (this->_capacity != 0)
																																															this->_alloc.deallocate(this->_arr, this->_capacity);
																																													}
			vector& operator= (const vector& x)																																		{
																																														if (this != &x)
																																														{
																																															this->~vector();
																																															this->_size = x._size;
																																															this->_capacity = x._capacity;
																																															this->_alloc = x._alloc;
																																															if (_capacity != 0)
																																																this->_arr = this->_alloc.allocate(_capacity);
																																															for (size_t i = 0; i < this->_size; i++)
																																															{
																																																_arr[i] = x._arr[i];
																																															}
																																														}
																																														return (*this);
																																													}
			//Getters
			iterator				begin()			{return iterator(this->_arr);}
			const_iterator 			begin() const	{return const_iterator(this->_arr);}
			iterator				end()			{return iterator(this->_arr + this->_size);}
			const_iterator 			end() const		{return const_iterator(this->_arr + this->_size);}
			reverse_iterator		rbegin()		{return reverse_iterator(this->end());}
			const_reverse_iterator	rbegin() const	{return const_reverse_iterator(this->begin());}
			reverse_iterator		rend()			{return reverse_iterator(this->begin());}
			const_reverse_iterator	rend() const	{return const_reverse_iterator(this->_arr);}


			size_type				size() const					{return (this->_size);}
			size_type				capacity() const				{return (this->_capacity);}
			size_type				max_size() const				{return (this->_alloc.max_size());}
			bool					empty() const					{return (this->_size == 0);}
			reference				operator[] (size_type n)		{return (this->_arr[n]);}
			const_reference			operator[] (size_type n) const	{return (this->_arr[n]);}
			reference				front()							{return (this->_arr[0]);}
			const_reference			front() const					{return (this->_arr[0]);}
			reference				back()							{return (this->_arr[this->_size - 1]);}
			const_reference			back() const					{return (this->_arr[this->_size - 1]);}
			reference				at(size_type n)					{
																		if (n >= this->_size)
																			throw std::out_of_range("Index out of vector bounds!");
																		return (this->_arr[n]);
																	}
			const_reference			at (size_type n) const			{
																		if (n >= this->_size)
																			throw std::out_of_range("Index out of vector bounds!");
																		return (this->_arr[n]);
																	}

			//Modifiers
			void		assign(size_type n, const value_type& val)							{
																								this->clear();
																								for (size_type i = 0; i < n; i++)
																									this->push_back(val);
																							}
			template <class InputIterator>
			void		assign(typename ft::enable_if<!is_integral<InputIterator>::value, InputIterator>::type first,
																		InputIterator last)	{
																								size_t	i = 0;
																								this->clear();
																								InputIterator tmp = first;
																								while (tmp != last)
																								{
																									tmp++;
																									i++;
																								}
																								if (this->_capacity < i)
																									this->reserve(i);
																								while (first != last)
																								{
																									this->push_back(*first);
																									first++;
																								}
																							}
			void		clear()																{
																								for (size_t i = 0; i < this->_size; i++)
																									this->_alloc.destroy(this->_arr + i);
																								this->_size = 0;
																							}
			iterator	erase(iterator position)											{
																								if (this->empty() == true || position > this->end())
																									return (NULL);
																								for (iterator it = position; it != this->end() - 1; ++it)
																									*it = *(it + 1);
																								pop_back();
																								return position;
																							}

			iterator	erase(iterator first, iterator last)								{
																								if (this->empty() == true || last > this->end() || first > this->end())
																									return (NULL);
																								iterator tmp = first;
																								while (tmp != last)
																								{
																									erase(first);
																									tmp++;
																								}
																								return (first);
																							}
			iterator	insert(iterator position, const value_type& val)					{
																								if (this->_capacity == this->max_size())
																									return (NULL);
																								if (this->_capacity == 0)
																								{
																									this->push_back(val);
																									return (position);
																								}
																								if (this->_capacity == this->_size)
																								{
																									int pos = position - this->begin();
																									this->redimension(2 * this->_capacity);
																									position = this->begin() + pos;
																								}
																								vector tmp(position, this->end());
																								for (size_t i = 0; i < tmp.size(); i++)
																									this->pop_back();
																								this->push_back(val);
																								for (iterator it = tmp.begin(); it != tmp.end(); it++)
																									this->push_back(*it);
																								return (position);
																							}
			void		insert(iterator position, size_type n, const value_type& val)		{
																								if (this->_capacity < this->_size + n)
																								{
																									std::ptrdiff_t pos = position - this->begin();
																									this->redimension(this->_size + n);
																									position = this->begin() + pos;
																								}
																								for (size_type i = 0; i < n; i++)
																								{
																									this->insert(position, val);
																									position++;
																								}
																							}
			template <class InputIterator>
			void		insert(iterator position, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type first,
																		InputIterator last)	{
																								std::ptrdiff_t count = 0;
																								std::ptrdiff_t pos = position - this->begin();
																								InputIterator tmp = first;
																								while (tmp != last)
																								{
																									count++;
																									tmp++;
																								}
																								if ((this->_size + count) > this->_capacity)
																									this->reserve(this->_size + count);
																								for (std::ptrdiff_t i = this->_size; i > pos; i--)
																								{
																									this->_arr[i - 1 + count] = this->_arr[i - 1];
																								}
																								this->_size += count;
																								while (count--)
																								{
																									last--;
																									this->_arr[pos + count] = *last;
																								}
																							}
			void		pop_back()															{
																								if (!this->empty())
																								{
																									this->_alloc.destroy(this->_arr + (this->_size - 1));
																									this->_size --;
																								}
																							}
			void		push_back(const value_type& val)									{
																								if (!this->_capacity)
																								{
																									this->_arr = this->_alloc.allocate(1);
																									this->_capacity++;
																								}
																								else if (this->_size == this->_capacity)
																									redimension(this->_capacity * 2);
																								this->_alloc.construct(this->_arr + this->_size, val);
																								this->_size++;
																							}		
			void		swap(vector& x)														{
																								allocator_type tmp_alloc = x._alloc;
																								size_type tmp_size = x._size;
																								size_type tmp_capacity = x._capacity;
																								pointer tmp_arr = x._arr;

																								x._alloc = this->_alloc;
																								this->_alloc = tmp_alloc;
																								x._size = this->_size;
																								this->_size = tmp_size;
																								x._capacity = this->_capacity;
																								this->_capacity = tmp_capacity;
																								x._arr = this->_arr;
																								this->_arr = tmp_arr;
																							}
			//Capacity
			void		resize(size_type n, value_type val = value_type())					{
																								if (n > this->_size)
																									for (size_t i = this->_size; i < n; i++)
																										push_back(val);
																								else if (n < this->_size)
																									for (size_t i = this->_size - n; i > 0; i--)
																										pop_back();
																							}
			void		reserve (size_type n)												{
																								if (n > this->_capacity)
																									redimension(n);
																							}

		
			//allocator_type  get_allocator() const {return (this->_alloc);}

		private:
			Alloc	_alloc;
			T*		_arr;
			size_t	_size;
			size_t	_capacity;

			void		redimension(size_type n)
			{
				if (n > this->max_size())
					n = this->max_size();
				pointer newdata = this->_alloc.allocate(n);
				for (size_type i = 0; i < this->_size; i++)
				{
					this->_alloc.construct(newdata + i, this->_arr[i]);
					this->_alloc.destroy(this->_arr + i);
				}
				if (this->_capacity != 0)
					this->_alloc.deallocate(this->_arr, this->_capacity);
				this->_arr = newdata;
				this->_capacity = n;
			}
	};

/*	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1) return false;
			else if (*first1<*first2) return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}
	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1!=last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}*/
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
	}
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(lhs < rhs);
	}
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif