/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:26 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:03:26 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

t_tree_node	*tree_print_error(t_tree_info *info)
{
	print_syntax_error(info->node->element);
	g_env_list->return_value = 258;
	free_tree_node(info->node);
	return (NULL);
}

t_tree_node	*tree_error(t_tree_node *result, t_queue *queue)
{
	free_tree(result);
	queue_free(queue);
	return (NULL);
}

t_tree_node	*copy_to_tree_node(t_queue *queue)
{
	t_node		*qnode;
	t_tree_node	*node;

	qnode = queue_pop(queue);
	node = create_tree_node(qnode->element, qnode->token_type);
	if (node == NULL)
	{
		free_node(qnode);
		return (NULL);
	}
	free(qnode);
	return (node);
}

t_tree_node	*tree_check_end_subshell(t_tree_node *root)
{
	while (root->right != NULL)
		root = root->right;
	if (root->token_type == parenthsis && is_parenthsis(root->element) == 2)
		return (root);
	return (NULL);
}

void	tree_delete_end_subshell(t_tree_node *root)
{
	while (root->right->token_type != parenthsis)
		root = root->right;
	free_tree_node(root->right);
	root->right = NULL;
}
