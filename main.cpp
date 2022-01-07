/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:34:40 by rgilles           #+#    #+#             */
/*   Updated: 2022/01/07 13:05:32 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack.hpp>
#include <deque>
#include <iostream>

int	main(void)
{
	ft::stack<int>	uwu;
	ft::stack<int>	owo;

	std::cout << "Stack size is " << uwu.size() << std::endl;
	uwu.push(1);
	uwu.push(5);
	uwu.push(9);
	std::cout << "Stack size is " << uwu.size() << std::endl;
	std::cout << "Stack top is " << uwu.top() << std::endl;
	uwu.top() = 8;
	std::cout << "Stack top is " << uwu.top() << std::endl;
	uwu.pop();
	std::cout << "Stack size is " << uwu.size() << std::endl;
	std::cout << "Stack top is " << uwu.top() << std::endl;
	// uwu is 1, 5
	
	owo.push(2);
	std::cout << "Is owo superior to uwu ? " << (owo > uwu) << std::endl;
	owo.top() = 1;
	owo.push(4);
	owo.push(10);
	std::cout << "Is owo superior to uwu ? " << (owo > uwu) << std::endl;
}