/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 17:35:28 by rgilles           #+#    #+#             */
/*   Updated: 2022/02/03 15:54:57 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST_HPP
# define BST_HPP

namespace ft 
{
	template <class T>
	struct node
	{
		node(const T& src_data = T(), node* prt = NULL, node* lft = NULL, node* rght = NULL, std::ptrdiff_t hgt = 0) : _data(src_data), parent(prt), left(lft), right(rght), height(hgt)	{}
	
		T		_data;
		node*			parent;
		node*			left;
		node*			right;
		std::ptrdiff_t	height;

		node*	increment()	{
								node*	ret = this;
								if (ret->right)
								{
									ret = ret->right;
									while (ret->left)
										ret = ret->left;
								}
								else
								{
									while (ret->parent && ret == ret->parent->right)
										ret = ret->parent;
									ret = ret->parent;
								}
								return (ret);
							}
		node*	decrement()	{
								node*	ret = this;
								if (ret->left)
								{
									ret = ret->left;
									while (ret->right)
										ret = ret->right;
								}
								else
								{
									while (ret->parent && ret == ret->parent->left)
										ret = ret->parent;
									ret = ret->parent;
								}
								return (ret);
							}
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

		
			BST(const allocator_type& alloc = allocator_type(), const key_compare& comp = key_compare())	: _alloc(alloc), _cmp(comp), _size(0)			{
																																								this->_root = this->_alloc.allocate(1);
																																								this->_alloc.construct(this->_root, node<T>());
																																								this->_end = this->_root;
																																							}
			~BST()																																			{this->clear(); this->_alloc.deallocate(this->_root, 1);}
			BST(const BST& cpy)																				: _alloc(cpy._alloc), _cmp(cpy._cmp), _size(0)	{
																																								this->_root = this->_alloc.allocate(1);
																																								this->_alloc.construct(this->_root, node<T>());
																																								this->_end = this->_root;
																																								node_ptr i = cpy.get_min();
																																								while (i != cpy.get_end())
																																								{
																																									this->insert_node(i->_data);
																																									i = i->increment();
																																								}
																																							}
			BST&	operator=(const BST& cpy)																												{
																																								if (this != &cpy)
																																								{
																																									this->clear();
																																									node_ptr i = cpy.get_min();
																																									while (i != cpy.get_end())
																																									{
																																										this->insert_node(i->_data);
																																										i = i->increment();
																																									}
																																								}
																																								return (*this);
																																							}

			//Getters
			allocator_type	get_alloc() const			{return allocator_type();}
			size_type		size() const				{return this->_size;}
			size_type		max_size() const			{return (this->_alloc.max_size());}
			void			print() const				{print2DUtil(this->_root, 0);}
			node_ptr		get_min() const				{
															if (!this->_root)
																return NULL;
															node_ptr tmp = this->_root;
															while (tmp->left)
																tmp = tmp->left;
															return (tmp);
														}
			node_ptr		get_end() const				{return this->_end;}

			//Modifiers
			void		clear()								{
																erase_tree(this->_root);
																this->_root = this->_end;
																this->_end->parent = NULL;
																this->_end->left = NULL;
																this->_end->right = NULL;
																this->_end->height = 0;
																_size = 0;
															}
			void		insert_node(value_type data)		{
																node_ptr	curr = this->_root;
																node_ptr	newNode;

																while (true)
																{
																	if (curr == this->_end)
																	{
																		node_ptr	parent = this->_end->parent;
																		node_ptr&	dest = parent ? parent->right : this->_root;

																		newNode = this->_alloc.allocate(1);
																		this->_alloc.construct(newNode, node<T>(data, parent, NULL, _end, 0));
																		dest = newNode;
																		this->_end->parent = newNode;
																		break;
																	}

																	bool	res = _cmp(data.first, curr->_data.first);

																	if (!res && !_cmp(curr->_data.first, data.first))
																		break;

																	if (res)
																	{
																		if (curr->left)
																			curr = curr->left;
																		else
																		{
																			newNode = this->_alloc.allocate(1);
																			this->_alloc.construct(newNode, node<T>(data, curr, NULL, NULL, 0));
																			curr->left = newNode;
																			break;
																		}
																	}
																	else
																	{
																		if (curr->right)
																			curr = curr->right;
																		else
																		{
																			newNode = this->_alloc.allocate(1);
																			this->_alloc.construct(newNode, node<T>(data, curr, NULL, NULL, 0));
																			curr->right = newNode;
																			break;
																		}
																	}
																}
																// _insert_rebalance(newNode);
																this->_size++;
															}
/*			node_ptr	search_node(value_type val)			{
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
															}*/
			node_ptr	search_node(value_type val) const	{
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

			void		delete_node(value_type val)			{
																node_ptr	node = this->search_node(val);
																node_ptr*	x;
																if (!node->parent)
																	x = &this->_root;
																else
																	x = (node == node->parent->left ? &node->parent->left : &node->parent->right);

																if (!node->left && !node->right)
																	*x = NULL;
																else if ((node->left || node->right) && !(node->left && node->right))
																	*x = node->left ? node->left : node->right;
																else
																{
																	node_ptr	succ = node->right;
																	while (succ->left)
																		succ = succ->left;
																	succ->parent->left = NULL;
																	succ->left = node->left;
																	succ->right = node->right;
																	*x = succ;
																}
																this->_alloc.deallocate(node, 1);
																this->_size--;
															}
			//Misc
			node_ptr		lower_bound(value_type val) const	{
																	node_ptr node = get_min();
																	while (node != _end)
																	{
																		if (!_cmp(node->_data.first, val.first))
																			return node;
																		node = node->increment();
																	}
																	return _end;
																}
			node_ptr		upper_bound(value_type val) const	{
																	node_ptr node = get_min();
																	while (node != _end)
																	{
																		if (_cmp(val.first, node->_data.first))
																			return node;
																		node = node->increment();
																	}
																	return _end;
																}
			void		swap(BST& x)							{
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

		private:
			allocator_type	_alloc;
			key_compare		_cmp;
			size_type		_size;
			node_ptr		_root;
			node_ptr		_end;

			void		print2DUtil(node_ptr root, int spc) const	{
															    if (root == NULL)
															        return;
															    spc += 10;
															    print2DUtil(root->right, spc);
															    std::cout << std::endl;
															    for (int i = 10; i < spc; i++)
															        std::cout << " ";
															    std::cout << "[" << root->_data.first <<", " << root->_data.second << "]" << std::endl;
															    print2DUtil(root->left, spc);
															}
			void		erase_tree(node_ptr node)			{
																if (node != NULL)
																{
																	if (node->left)
																		erase_tree(node->left);
																	if (node->right)
																		erase_tree(node->right);
																	if (node != this->_end)
																		_alloc.deallocate(node, 1);
																}
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
																				if (!root->left)
																				{
																					node_ptr tmp = root->right;
																					if (tmp != NULL)
																						tmp->parent = root->parent;
																					_alloc.deallocate(root, 1);
																					_size--;
																					return tmp;
																				}
																				else if (!root->right)
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
			//Balancing
			node_ptr	right_rotation(node_ptr node)							{
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
																					node->height = node->height - 1 - std::max(0, tmp->height);
																					tmp->height = tmp->height - 1 - std::min(0, node->height);
																					return tmp;
																				}
			node_ptr	left_rotation(node_ptr node)							{
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
																					node->height = node->height + 1 - std::min(0, tmp->height);
																					tmp->height = tmp->height + 1 + std::max(0, node->height);
																					return tmp;
																				}
			node_ptr	rebalance(node_ptr node)								{
																					node_ptr tmp = NULL;
																					if (node->height < 0)
																					{
																						if (node->right->height > 0)
																						{
																							right_rotation(node->right);
																							tmp = left_rotation(node);
																						}
																						else
																							tmp = left_rotation(node);
																					}
																					else if (node->height > 0)
																					{
																						if (node->left->height < 0)
																						{
																							left_rotation(node->left);
																							tmp = right_rotation(node);
																						}
																						else
																							tmp = right_rotation(node);
																					}
																					return tmp;
																				}
			void		insert_balance_factor(node_ptr node)					{
																					if (node->height < -1 || node->height > 1)
																					{
																						rebalance(node);
																						return ;
																					}
																					if (node->parent != _end)
																					{
																						if (node == node->parent->left)
																							node->parent->height += 1;
																						if (node == node->parent->right)
																							node->parent->height -= 1;
																						if (node->parent->height != 0)
																							insert_balance_factor(node->parent);
																					}
																				}
			node_ptr	delete_balance_factor(node_ptr node, value_type val)	{
																					if (node != this->_end)
																					{
																						if (node->_data.first > val.first)
																							node->height -= 1;
																						else if (node->_data.first < val.first)
																							node->height += 1;
																						if (node->height < -1 || node->height > 1)
																						{
																							return rebalance(node);
																						}
																						if (node->height == 0)
																							delete_balance_factor(node->parent, val);
																					}
																					return NULL;
																				}
	};
}

#endif