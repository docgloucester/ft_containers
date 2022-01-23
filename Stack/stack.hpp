/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:35:47 by rgilles           #+#    #+#             */
/*   Updated: 2022/01/23 17:56:29 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <vector>
# include <cstddef>

namespace ft
{
	template< class T, class Container = std::vector<T> >
	class stack
	{
	public:
		typedef	T value_type;
		typedef Container container_type;
		typedef	size_t size_type;

		explicit stack(const container_type& ctnr = container_type()): _c(ctnr) {};
		stack(const stack<T, Container>& src): _c(src._c) {};
		~stack() {};
		stack<T, Container>&	operator=(const stack<T, Container>& src) {this->_c = src._c; return (*this);};

		bool					empty() const {return (this->_c.empty());};
		size_type				size() const {return (this->_c.size());};
		value_type&				top() {return (this->_c.back());};
		const value_type& 		top() const {return (this->_c.back());};
		void					push(const value_type& val) {this->_c.push_back(val);};
		void					pop() {this->_c.pop_back();}

		friend bool	operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{return (lhs._c == rhs._c);}
		friend bool	operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{return (lhs._c != rhs._c);}
		friend bool	operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{return (lhs._c < rhs._c);}
		friend bool	operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{return (lhs._c <= rhs._c);}
		friend bool	operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{return (lhs._c > rhs._c);}
		friend bool	operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)	{return (lhs._c >= rhs._c);}
	protected:
		container_type _c;
	};
}
#endif