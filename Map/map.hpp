/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:34:35 by rgilles           #+#    #+#             */
/*   Updated: 2022/01/30 13:36:35 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "bst.hpp"
#include "pair.hpp"
#include "map_iterator.hpp"
#include "../common/reverse_iterator.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T>>>
	class map
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef pair<const key_type, mapped_type>			value_type;
			typedef size_t										size_type;
			typedef ptrdiff_t									difference_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;

			typedef BST<value_type, key_compare, Alloc>			tree;
			typedef typename tree::ptr_node						ptr_node;

			typedef tree_iterator<pointer, ptr_node>			iterator;
			typedef tree_iterator<const_pointer, ptr_node>		const_iterator;
			typedef reverse_iterator<iterator>					reverse_iterator;
			typedef reverse_iterator<const_iterator>			const_reverse_iterator;
			class value_compare : std::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					value_compare(Compare c)	: comp(c)	{}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;

					bool	operator()(const value_type& x, const value_type& y)	{return comp(x.first, y.first);}
				protected:
					Compare comp;
			};

			explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())	: _alloc(alloc), _tree(), _cmp(comp)	{}
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
																													: _alloc(alloc), _tree(), _cmp(comp)	{
																																								while (first != last)
																																								{
																																									this->_tree.insert_node(*first);
																																									first++;
																																								}
																																							}
			map (const map& x)																						: _alloc(x._alloc), _cmp(x._cmp)		{insert(x.begin(), x.end());}
			~map()																																			{}
			map& operator= (const map& x)																													{
																																								if (this != &x)
																																								{
																																									this->clear();
																																									if (x.size() != 0)
																																										insert(x.begin(), x.end());
																																								}
																																								return (*this);
																																							}

			iterator				begin()									{return iterator(this->_tree.get_min());}
			const_iterator			begin() const							{return const_iterator(this->_tree.get_min());}
			iterator				end()									{return iterator(this->_tree.get_end());}
			const_iterator			end() const								{return const_iterator(this->_tree.get_end());}
			reverse_iterator		rbegin()								{return reverse_iterator(this->end());}
			const_reverse_iterator	rbegin() const							{return const_reverse_iterator(this->end());}
			reverse_iterator		rend()									{return reverse_iterator(this->begin());}
			const_reverse_iterator	rend() const							{return const_reverse_iterator(this->begin());}
			

			bool		empty() const							{return(this->_tree.size() == 0);}
			size_type	size() const							{return this->_tree.size();}
			size_type	max_size() const						{return (this->_tree.max_size());}
			mapped_type& operator[] (const key_type& k)			{
																	ptr_node node = this->_tree.search_node(ft::make_pair(k, mapped_type()));
																	if (node == NULL)
																		this->_tree.insert_node(ft::make_pair(k, mapped_type()));
																	node = this->_tree.search_node(ft::make_pair(k, mapped_type()));
																	return (node->_data.second);
																}
			mapped_type&		at(const key_type& key)			{
																	ptr_node node = this->_tree.search_node(ft::make_pair(k, mapped_type()));
																	if (node == NULL)
																		throw std::out_of_range("Map doesn't contain key!");
																	return (node->_data.second);
																}	
			const mapped_type&	at(const key_type& key) const	{
																	ptr_node node = this->_tree.search_node(ft::make_pair(k, mapped_type()));
																	if (node == NULL)
																		throw std::out_of_range("Map doesn't contain key!");
																	return (node->_data.second);
																}
			key_compare		key_comp() const					{return key_compare();}
			value_compare	value_comp() const					{return value_compare(_cmp);}
			allocator_type 	get_allocator() const				{return (this->_tree.get_alloc());}
			
			void				clear()												{this->_tree.clear();}
			pair<iterator,bool>	insert(const value_type& val)						{
																						ptr_node node = this->_tree.search_node(val);
																						if (node != NULL)
																							return ft::pair<iterator, bool>(iterator(node), false);
																						this->_tree.insert_node(val);
																						node = this->_tree.search_node(val);
																						return (ft::pair<iterator, bool>(iterator(node), true));
																					}
			iterator			insert(iterator position, const value_type& val)	{
																						static_cast<void>(position);
																						ptr_node node = this->_tree.search_node(val);
																						if (node != NULL)
																							return iterator(node);
																						this->_tree.insert_node(val);
																						node = this->_tree.search_node(val);
																						return (iterator(node));
																					}
			template <class InputIterator>
			void				insert (InputIterator first, InputIterator last)	{
																						while (first != last)
																						{
																							ptr_node node = this->_tree.search_node(*first);
																							if (!node)
																								this->_tree.insert_node(*first);
																							first++;
																						}
																					}
			void				erase(iterator position)							{
																						if (position != iterator(NULL))
																							this->_tree.delete_node(*position);
																					}
			size_type			erase(const key_type& k)							{
																						ptr_node node = this->_tree.search_node(ft::make_pair(k, mapped_type()));
																						if (node != NULL)
																						{
																							this->_tree.delete_node(ft::make_pair(k, mapped_type()));
																							return (1);
																						}
																						else
																							return (0);
																					}
			void				erase(iterator first, iterator last)				{
																						iterator tmp;
																						while (first != last)
																						{
																							if (first == this->end())
																								return ;
																							tmp = first;
																							first++;
																							this->erase(tmp);
																						}
																					}
			void				swap(map& x)										{
																						allocator_type	tmp_alloc = x._alloc;
																						key_compare		tmp_cmp = x._cmp;

																						x._alloc = this->_alloc;
																						this->_alloc = tmp_alloc;
																						this->_tree.swap(x._tree);
																						x._cmp = this->_cmp;
																						this->_cmp = tmp_cmp;
																					}


			size_type							count(const key_type& k) const			{return (this->_tree.search_node(ft::make_pair(k, mapped_type())) == NULL ? 0 : 1);}
			iterator							find(const key_type& k)					{
																							ptr_node node = this->_tree.search_node(ft::make_pair(k, mapped_type()));
																							if (node == NULL)
																								return (this->end());
																							return iterator(node);
																						}
			const_iterator						find(const key_type& k) const			{
																							ptr_node node = this->_tree.search_node(ft::make_pair(k, mapped_type()));
																							if (node == NULL)
																								return (this->end());
																							return const_iterator(node);
																						}
			iterator							lower_bound(const key_type& k)			{return iterator(this->_tree.lower_bound(ft::make_pair(k, mapped_type())));}
			const_iterator						lower_bound(const key_type& k) const	{return const_iterator(this->_tree.lower_bound(ft::make_pair(k, mapped_type())));}
			iterator							upper_bound(const key_type& k)			{return iterator(this->_tree.upper_bound(ft::make_pair(k, mapped_type())));}
			const_iterator						upper_bound(const key_type& k) const	{return const_iterator(this->_tree.upper_bound(ft::make_pair(k, mapped_type())));}
			pair<iterator,iterator>				equal_range(const key_type& k)			{return (ft::make_pair(lower_bound(k), upper_bound(k)));}
			pair<const_iterator,const_iterator>	equal_range(const key_type& k) const	{return (ft::make_pair(lower_bound(k), upper_bound(k)));}

		private:
			allocator_type	_alloc;
			tree			_tree;
			key_compare		_cmp;
	};
}
#endif