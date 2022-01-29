/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:45:37 by rgilles           #+#    #+#             */
/*   Updated: 2022/01/25 12:49:47 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft
{
	template<typename T>
	struct is_integral {static const bool value = false;};

	template<>
	struct is_integral<bool> {static const bool value = true;};

	template<>
	struct is_integral<const bool> {static const bool value = true;};

	template<>
	struct is_integral<int> {static const bool value = true;};

	template<>
	struct is_integral<const int> {static const bool value = true;};

	template<>
	struct is_integral<unsigned int> {static const bool value = true;};

	template<>
	struct is_integral<const unsigned int> {static const bool value = true;};

	template<>
	struct is_integral<long> {static const bool value = true;};

	template<>
	struct is_integral<const long> {static const bool value = true;};

	template<>
	struct is_integral<unsigned long> {static const bool value = true;};

	template<>
	struct is_integral<const unsigned long> {static const bool value = true;};

	template<>
	struct is_integral<short> {static const bool value = true;};

	template<>
	struct is_integral<const short> {static const bool value = true;};

	template<>
	struct is_integral<unsigned short> {static const bool value = true;};

	template<>
	struct is_integral<const unsigned short> {static const bool value = true;};

	template<>
	struct is_integral<char> {static const bool value = true;};

	template<>
	struct is_integral<const char> {static const bool value = true;};

	template<>
	struct is_integral<unsigned char> {static const bool value = true;};

	template<>
	struct is_integral<const unsigned char> {static const bool value = true;};

	template<>
	struct is_integral<float> {static const bool value = true;};

	template<>
	struct is_integral<const float> {static const bool value = true;};

	template<>
	struct is_integral<double> {static const bool value = true;};

	template<>
	struct is_integral<const double> {static const bool value = true;};

	template<>
	struct is_integral<long double> {static const bool value = true;};

	template<>
	struct is_integral<const long double> {static const bool value = true;};
}

#endif
