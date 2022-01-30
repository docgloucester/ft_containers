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

	template <class T, class Compare, class Alloc>
	class BST
	{
		public:
			typedef T															value_type;
			typedef node<T>*													node_ptr;
			typedef typename Alloc::template rebind<node<value_type> >::other	allocator_type;
			typedef Compare														key_compare;
			typedef size_t														size_type;

		
			BST(const allocator_type& alloc = allocator_type(), const key_compare& comp = key_compare())	: _alloc(alloc), _cmp(comp), _size(0), _root(NULL), _end(NULL)	{}
			~BST()																																							{
																																												this->_root = all_clean_tree(this->_root);
																																												this->_alloc.deallocate(this->_end, 1);
																																											}

			node_ptr	increment(node_ptr curr)	{
				if (curr->right != NULL)
				{
					curr = curr->right;
					while (curr->left != NULL)
						curr = curr->left;
					return curr;
				}
				else
				{
					node_ptr ptr_parent = curr->parent;
					while (ptr_parent != NULL && curr == ptr_parent->right)
					{
						curr = ptr_parent;
						ptr_parent = ptr_parent->parent;
					}
					return ptr_parent;
				}
			}
			allocator_type	get_alloc() const	{return allocator_type();}
			size_type	size() const			{return _size;}
			size_type	max_size() const		{return (_alloc.max_size());}
			void	swap(BST& x)				{
													size_type		s_size = x._size;
													allocator_type	s_alloc = x._alloc;
													node_ptr		s_end = x._end;
													node_ptr		s_root = x._root;
													x._size = this->_size;
													this->_size = s_size;
													x._alloc = this->_alloc;
													this->_alloc = s_alloc;
													x._end = this->_end;
													this->_end = s_end;
													x._root = this->_root;
													this->_root = s_root;

												}

			node_ptr	all_clean_tree(node_ptr node)	{
															if (node != NULL)
															{
																all_clean_tree(node->left);
																all_clean_tree(node->right);
																_alloc.deallocate(node, 1);
															}
															return NULL;
														}
			void clear()	{
								_root = all_clean_tree(_root);
								if (_root == NULL)
								{
									_alloc.deallocate(_end, 1);
									_end = NULL;
								}
								_size = 0;
							}
			node_ptr	lower_bound(value_type val)	{
														node_ptr node = get_min();
														while (node != _end)
														{
															if (!_cmp(node->_data.first, val.first))
																return node;
															node = increment(node);
														}
														return _end;
													}
			node_ptr	upper_bound(value_type val)	{
														node_ptr node = get_min();
														while (node != _end)
														{
															if (_cmp(val.first, node->_data.first))
																return node;
															node = increment(node);
														}
														return _end;
													}
			void	insert_node(value_type data)	{
														node_ptr new_node = _alloc.allocate(1);
														_alloc.construct(new_node, data);
														new_node->left = NULL;
														new_node->right = NULL;
														new_node->parent = NULL;
														new_node->bf = 0;

														if (_root == NULL)
														{
															_end = _alloc.allocate(1);
															_root = new_node;
															_root->parent = _end;
															_end->left = _root;
															_size++;
															return ;
														}
														node_ptr tmp = _root;
														node_ptr parent = NULL;
														while (tmp != NULL)
														{
															parent = tmp;
															if (_cmp(new_node->_data.first, tmp->_data.first))
																tmp = tmp->left;
															else if (new_node->_data.first == tmp->_data.first)
															{
																tmp->_data.second = new_node->_data.second;
																_alloc.deallocate(new_node, 1);
																return ;
															}
															else
																tmp = tmp->right;
														}
														if (_cmp(new_node->_data.first, parent->_data.first))
														{
															parent->left = new_node;
															_size++;
														}
														else
														{
															parent->right = new_node;
															_size++;
														}
														new_node->parent = parent;
														//NOTE - Calcule bf every node
														insert_balance_factor(new_node);
													}
			node_ptr	get_max() const	{
											node_ptr tmp = _root;
											if (tmp == NULL)
												return NULL;
											return get_max_helper(tmp);
										}

			node_ptr	get_min() const	{
											node_ptr tmp = _root;
											if (tmp == NULL)
												return NULL;
											return get_min_helper(tmp);
										}

			node_ptr  search_node(value_type val)	{
														node_ptr tmp = _root;
														if (tmp == NULL)
															return (NULL);
														while (tmp->_data.first != val.first)
														{
															if (tmp != NULL)
															{
																if (_cmp(val.first, tmp->_data.first))
																	tmp = tmp->left;
																else
																	tmp = tmp->right;
															}
															if (tmp == NULL)
																return NULL;
														}
														return tmp;
													}
			
			node_ptr  search_node(value_type val) const	{
															node_ptr tmp = _root;
															
															if (tmp == NULL)
																return (NULL);
															while (tmp->_data.first != val.first)
															{
																if (tmp != NULL)
																{
																	if (_cmp(val.first, tmp->_data.first))
																		tmp = tmp->left;
																	else
																		tmp = tmp->right;
																}
																if (tmp == NULL)
																	return NULL;
															}
															return tmp;
														}

			void	delete_node(value_type val)	{
													bool isonechild = false;
													node_ptr node = this->search_node(val);
													node_ptr node_p= this->search_node(val)->parent;
													if (node->left == NULL || node->right == NULL)
														isonechild = true;
													_root = delete_helper(_root, val);
													if (_root == NULL)
													{
														_alloc.deallocate(_end, 1);
														_end = NULL;
													}
													if (isonechild == true)
														delete_balance_factor(node_p, val);
												}
												void	print_bst()	{
													print_bst_preorder(this->_root);
												}

			node_ptr get_end() const	{return _end;}

		private:
			allocator_type	_alloc;
			key_compare		_cmp;
			size_type		_size;
			node_ptr		_root;
			node_ptr		_end;
			

			node_ptr get_max_helper(node_ptr tmp)	{
														while (tmp->right != NULL)
															tmp = tmp->right;
														return tmp;
													}

			node_ptr get_min_helper(node_ptr tmp) const	{
															while (tmp->left != NULL)
																tmp = tmp->left;
															return tmp;
														}
			node_ptr	delete_helper(node_ptr root, value_type val)	{
																			node_ptr tmp;
																			if (root == NULL)
																				return root;
																			else if (_cmp(val.first, root->_data.first))
																				root->left = delete_helper(root->left, val);
																			else if (_cmp(root->_data.first, val.first))
																				root->right = delete_helper(root->right, val);
																			else
																			{
																				if (root->left == NULL)
																				{
																					node_ptr tmp = root->right;
																					if (tmp != NULL)
																						tmp->parent = root->parent;
																					_alloc.deallocate(root, 1);
																					_size--;
																					return tmp;
																				}
																				else if (root->right == NULL)
																				{
																					node_ptr tmp = root->left;
																					if (tmp != NULL)
																						tmp->parent = root->parent;
																					_alloc.deallocate(root, 1);
																					_size--;
																					return tmp;
																				}
																				else
																				{
																					node_ptr max_val = this->get_max_helper(root->left);
																					value_type vt = max_val->_data;
																					node_ptr node = max_val->parent;
																					root->left = delete_helper(root->left, max_val->_data);
																					tmp = delete_balance_factor(node, vt);
																					_alloc.construct(root, vt);
																					if (tmp != NULL)
																						root = tmp;
																				}
																			}
																			return root;
																		}

			void	print_bst_preorder(node_ptr root)	{
															if (root != NULL)
															{
																std::cout <<root->_data.first << "\t"<< root->bf << std::endl;
																print_bst_preorder(root->left);
																print_bst_preorder(root->right);
															}
														}
			int	 max(int a, int b)	{return (a > b ? a : b);}
			int	 min(int a, int b)	{return (a < b ? a : b);}
			node_ptr	right_rotation(node_ptr node)	{
															node_ptr tmp = node->left;
															node->left = tmp->right;
															if (tmp->right != NULL)
																tmp->right->parent = node;
															tmp->parent = node->parent;
															if (node->parent == _end)
															{
																this->_root = tmp;
																tmp->parent = _end;
															}
															else if (node == node->parent->right)
																node->parent->right = tmp;
															else
																node->parent->left = tmp;
															
															tmp->right = node;
															node->parent = tmp;
															node->bf = node->bf - 1 - max(0, tmp->bf);
															tmp->bf = tmp->bf - 1 - min(0, node->bf);
															return tmp;
														}
			node_ptr	left_rotation(node_ptr node)	{
															node_ptr	tmp = node->right;
															node->right = tmp->left;
															if (tmp->left != NULL)
																tmp->left->parent = node;
															tmp->parent = node->parent;
															if (node->parent == _end)
															{
																this->_root = tmp;
																this->_root->parent = _end;
																_end->left = this->_root;
															}
															else if (node == node->parent->left)
																node->parent->left = tmp;
															else
																node->parent->right = tmp;
															
															tmp->left = node;
															node->parent = tmp;
															node->bf = node->bf + 1 - min(0, tmp->bf);
															tmp->bf = tmp->bf + 1 + max(0, node->bf);
															return tmp;
														}
			node_ptr	rebalance(node_ptr node)	{
														node_ptr tmp = NULL;
														if (node->bf < 0)
														{
															if (node->right->bf > 0)
															{
																right_rotation(node->right);
																tmp = left_rotation(node);
															}
															else
																tmp = left_rotation(node);
														}
														else if (node->bf > 0)
														{
															if (node->left->bf < 0)
															{
																left_rotation(node->left);
																tmp = right_rotation(node);
															}
															else
																tmp = right_rotation(node);
														}
														return tmp;
													}
			void	insert_balance_factor(node_ptr node)	{
																if (node->bf < -1 || node->bf > 1)
																{
																	rebalance(node);
																	return ;
																}
																if (node->parent != _end)
																{
																	if (node == node->parent->left)
																		node->parent->bf += 1;
																	if (node == node->parent->right)
																		node->parent->bf -= 1;
																	if (node->parent->bf != 0)
																		insert_balance_factor(node->parent);
																}
															}
			node_ptr	delete_balance_factor(node_ptr node, value_type val)	{
																					if (node != _end)
																					{
																						if (node->_data.first > val.first)
																							node->bf -= 1;
																						else if (node->_data.first < val.first)
																							node->bf += 1;
																						if (node->bf < -1 || node->bf > 1)
																						{
																							return rebalance(node);
																						}
																						if (node->bf == 0)
																							delete_balance_factor(node->parent, val);
																					}
																					return NULL;
																				}
	};
}

#endif