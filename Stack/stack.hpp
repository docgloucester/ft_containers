/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:35:47 by rgilles           #+#    #+#             */
/*   Updated: 2022/02/06 16:53:07 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <cstddef>
# include "../Vector/vector.hpp"

namespace ft
{
	template< class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef	T value_type;
		typedef Container container_type;
		typedef	size_t size_type;

		explicit stack(const container_type& ctnr = container_type()): c(ctnr)	{};
		stack(const stack<T, Container>& src): c(src.c)							{};
		~stack()																{};
		stack<T, Container>&	operator=(const stack<T, Container>& src)		{this->c = src.c; return (*this);};

		bool					empty() const				{return (this->c.empty());};
		size_type				size() const				{return (this->c.size());};
		value_type&				top()						{return (this->c.back());};
		const value_type& 		top() const					{return (this->c.back());};
		void					push(const value_type& val)	{this->c.push_back(val);};
		void					pop()						{this->c.pop_back();}

		friend bool	operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{return (lhs.c == rhs.c);}
		friend bool	operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{return (lhs.c != rhs.c);}
		friend bool	operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{return (lhs.c < rhs.c);}
		friend bool	operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{return (lhs.c <= rhs.c);}
		friend bool	operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{return (lhs.c > rhs.c);}
		friend bool	operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{return (lhs.c >= rhs.c);}
	protected:
		container_type c;
	};
}
#endif