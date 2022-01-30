/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:35:28 by rgilles           #+#    #+#             */
/*   Updated: 2022/01/30 14:04:09 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_HPP
# define BST_HPP

namespace ft 
{
	template <class T>
	struct node
	{
		node(const T& src_data) : _data(src_data)	{}
	
		T			_data;
		node		*left;
		node		*right;
		node		*parent;
		int			bf;
	};

	template <class T, class Alloc, class Compare>
	class BST
	{
		public:
			typedef T															value_type;
			typedef node<T>*													node_ptr;
			typedef typename Alloc::template rebind<node<value_type> >::other	allocator_type;
			typedef Compare														key_compare;
			typedef size_t														size_type;

		private:
			ptr_node		_root;
			ptr_node		_end;
			allocator_type	_alloc;
			key_compare		_cmp;
			size_type		_size;
	};
}

#endif