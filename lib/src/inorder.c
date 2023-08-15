/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inorder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:58:44 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 21:58:46 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

t_tree_node	*check_leaf(t_tree_node *node)
{
	if (node == NULL)
		return (NULL);
	if (node->left == NULL && node->right == NULL)
		return (node);
	return (NULL);
}

void	inorder(t_tree_node *root)
{
	if (root == NULL)
		return ;
	inorder(root->left);
	inorder(root->right);
}

void	free_tree(t_tree_node *root)
{
	if (root == NULL)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	free_tree_node(root);
}
