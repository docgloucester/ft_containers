/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:02:53 by rgilles           #+#    #+#             */
/*   Updated: 2022/02/04 18:52:55 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICALCOMPARE_HPP
# define LEXICOGRAPHICALCOMPARE_HPP

namespace ft
{
	template< class InputIt1, class InputIt2 >
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first1 < *first2)
				return (true);
			else if (*first1 > *first2)
				return (false);
			first1++;
			first2++;
		}
		return (first1 == last1) && (first2 != last2);
	}
}

#endif