/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:43:07 by rgilles           #+#    #+#             */
/*   Updated: 2022/01/25 12:45:52 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <cstddef>
# include <VectorIterator.hpp>
# include <LexicographicalCompare.hpp>
# include <Equal.hpp>
# include <enable_if.hpp>
# include <is_integral.hpp>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:

			typedef	T value_type;
			typedef	Alloc allocator_type;
			typedef	typename allocator_type::reference reference;
			typedef	typename allocator_type::const_reference const_reference;
			typedef	typename allocator_type::pointer pointer;
			typedef	typename allocator_type::const_pointer const_pointer;
			typedef ft::VectorIterator<T> iterator;
			typedef typename std::reverse_iterator<iterator> reverse_iterator;
			typedef typename ft::VectorConstIterator<T> const_iterator;
			typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef	ptrdiff_t difference_type;
			typedef	size_t size_type;

			class OutOfRangeException: public std::exception
			{
				virtual const char* what() const throw()
				{
					return ("Data out of range");
				}
			};
			

			explicit vector(const allocator_type& alloc = allocator_type()) 													: _a(alloc), _data(NULL), _size(0), _capa(0)	{}
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())	: _a(alloc), _size(0), _capa(0)					{
																																													this->reserve(n);
																																													for (size_type i = 0; i < n; i++)
																																														this->_a.construct(this->_data + i, val);
																																													this->_size = n;
																																													this->_capa = n;
																																												}
			template <class InputIterator>
			vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last,
				const allocator_type& alloc = allocator_type())																	: _a(alloc), _data(NULL), _size(0), _capa(0)	{
																																													if (first > last)
																																														return ;
																																													for (; first != last; first++)
																																														this->push_back(*first);
																																												}
			vector(const vector& cpy)																																			{
																																													*this = cpy;
																																												}
			virtual ~vector() 																																					{
																																													this->clear();
																																													if (this->_capa > 0)
																																														_a.deallocate(this->_data, this->_capa);
																																												}
			vector& operator=(const vector& rhs)																																{
																																													if (this != &rhs)
																																													{
																																														this->~vector();
																																														this->_a = rhs._a;
																																														this->_size = rhs._size;
																																														this->_capa = rhs._capa;
																																														this->_data = this->_a.allocate(_capa);
																																														for (size_t i = 0; i < this->_size; i++)
																																															this->_a.construct(this->_data + i, rhs._data[i]);
																																													}
																																													return (*this);
																																												}

			//Iterators
			iterator				begin()			{return (iterator(this->_data));}
			const_iterator			begin() const	{return (const_iterator(this->_data));}
			iterator				end()			{return (iterator(this->_data + this->_size));}
			const_iterator			end() const		{return (const_iterator(this->_data + this->_size));}
			reverse_iterator		rbegin()		{return (reverse_iterator(this->_data + this->_size - 1));}
			const_reverse_iterator	rbegin() const	{return (const_reverse_iterator(this->_data + this->_size - 1));}
			reverse_iterator		rend()			{return (reverse_iterator(this->_data - 1));}
			const_reverse_iterator	rend() const	{return (const_reverse_iterator(this->_data - 1));}

			//Getters
			size_type		size() const					{return (this->_size);}
			size_type		max_size() const				{return (this->_a.max_size());}
			size_type		capacity() const				{return (this->_capa);}
			bool			empty() const					{return (this->_size == 0);}
			reference		operator[](size_type n)			{return (this->_data[n]);}
			const_reference	operator[](size_type n) const	{return (this->_data[n]);}
			reference		front()							{return (this->_data[0]);}
			const_reference	front() const					{return (this->_data[0]);}
			reference		back()							{return (this->_data[this->_size - 1]);}
			const_reference	back() const					{return (this->_data[this->_size - 1]);}
			reference		at(size_type n)					{
																if (n >= this->_size)
																	throw(ft::vector<T, Alloc>::OutOfRangeException());
																return (this->_data[n]);
															}
			const_reference	at(size_type n) const			{
																if (n >= this->_size)
																	throw(ft::vector<T, Alloc>::OutOfRangeException());
																return (this->_data[n]);
															}

			//Modifiers
			template <class InputIterator>
			void		assign(InputIterator first, InputIterator last)						{
																								size_t	i = 0;
																								this->clear();
																								iterator tmp = first;
																								while (tmp != last)
																								{
																									tmp++;
																									i++;
																								}
																								if (this->_capacity < i)
																									this->reserve(i);
																								while (first < last)
																								{
																									this->push_back(*first);
																									first++;
																								}
																							}
			void		assign(size_type n, const value_type& val)							{
																								this->clear();
																								for (size_type i = 0; i < n; i++)
																									this->push_back(val);
																							}
			void		clear()																{
																								if (this->_size)
																								{
																									for (size_type i = 0; i < this->_size; i++)
																										this->_a.destroy(this->_data + i);
																									this->_size = 0;
																								}
																							}
			iterator	erase(iterator position)											{
																								if (this->empty() == true || position > this->end())
																									return (NULL);
																								if (position == this->end())
																								{
																									this->pop_back();
																									return (position--);
																								}
																								vector<T, Alloc> tmp(position + 1, this->end());
																								for (size_type i = 0; i <= tmp.size(); i++)
																									this->pop_back();
																								for (iterator it = tmp.begin(); it != tmp.end(); it++)
																									this->push_back(*it);
																								return (position);
																							}
			iterator	erase(iterator first, iterator last)								{
																								if (this->empty() == true || last > this->end() || first > this->end())
																									return (NULL);
																								iterator tmp = first;
																								for (tmp; tmp != last; tmp++)
																									erase(tmp);
																								return (first);
																							}
			iterator	insert(iterator position, const value_type& val)					{
																								if (this->_capa == this->max_size())
																									return (NULL);
																								if (this->_capa == this->_size)
																								{
																									int pos = position - this->begin();
																									this->make_room(2 * this->_capa);
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
																								for (size_t i = 0; i < n; i++)
																									insert(position, val);
																							}
			template <class InputIterator>
			void		insert(iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first,
																		InputIterator last)	{
																								if (this->_capa == this->max_size())
																									return ;
																								int pos = position - this->begin();
																								if ((size_t)pos < this->_capa)
																								{
																									this->make_room(this->_capa * 2);
																									position = this->begin() + pos;
																								}
																								while (first < last)
																								{
																									insert(position, *first);
																									position++;
																									first++;
																								}
																							}
			void		pop_back()															{
																								if (this->empty() == false)
																								{
																									this->_a.destroy(this->_data + this->_size - 1);
																									this->_size--;
																								}
																							}
			void		push_back(const value_type& val)									{
																								if (!this->_capa)
																								{
																									this->_data = this->_a.allocate(1);
																									this->_capa++;
																								}
																								else if (this->_size == this->_capa)
																									make_room(this->_capa * 2);
																								this->_a.construct(this->_data + this->_size, val);
																								this->_size++;
																							}
			void		swap(vector& x)														{
																								allocator_type tmp_a = x._a;
																								size_type tmp_size = x._size;
																								size_type tmp_capa = x._capa;
																								pointer tmp_data = x._data;

																								x._a = this->_a;
																								this->_a = tmp_a;
																								x._size = this->_size;
																								this->_size = tmp_size;
																								x._capa = this->_capa;
																								this->_capa = tmp_capa;
																								x._data = this->_data;
																								this->_data = tmp_data;
																							}

			//Capacity
			void		resize(size_type n, value_type val = value_type())					{
																								while (n > this->_size)
																								{
																									this->push_back(val);
																									this->_size++;
																								}
																								while (n < this->_size)
																								{
																									this->pop_back();
																									this->_size--;
																								}
																							}
			void		reserve(size_type n)												{
																								if (n > this->_capa)
																									make_room(n);
																							}

		private:
			allocator_type	_a;
			pointer			_data;
			size_type		_size;
			size_type		_capa;

			void		make_room(size_type n)
			{
				if (this->_capa > this->max_size())
					n = this->max_size();
				pointer newdata = this->_a.allocate(n);
				for (size_type i = 0; i < this->_size; i++)
				{
					this->_a.construct(newdata + i, this->_data[i]);
					this->_a.destroy(this->_data + i);
				}
				if (this->_capa != 0)
					this->_a.deallocate(this->_data, this->_capa);
				this->_data = newdata;
				this->_capa = n;
			}
	};

//----------------------------------------------------------------------------------------------------

	template<class T, class Alloc>
	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class T, class Alloc>
	bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class T, class Alloc>
	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)	{return (lhs < rhs || lhs == rhs);}

	template<class T, class Alloc>
	bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)	{return (!(lhs <= rhs));}

	template<class T, class Alloc>
	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)	{return (!(lhs < rhs));}

	template<class T, class Alloc>
	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)	{return (!(lhs == rhs));}

	template <class T, class Alloc>
	void	swap(vector<T,Alloc>& x, vector<T,Alloc>& y)								{x.swap(y);}
}
#endif