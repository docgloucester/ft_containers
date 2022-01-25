/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexicographicalCompare.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:02:53 by rgilles           #+#    #+#             */
/*   Updated: 2022/01/25 12:49:27 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	template< class InputIt1, class InputIt2 >
	bool	lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 )
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

	template< class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp )
	{
		while (first1 != last1 && first2 != last2)
		{
			if (comp(*first1, *first2))
				return (true);
			else if (comp(*first2, *first1))
				return (false);
			first1++;
			first2++;
		}
		return (first1 == last1) && (first2 != last2);
	}
}