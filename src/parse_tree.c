/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:01:17 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:01:17 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

void	tree_init_info(t_tree_info *info, t_queue *queue)
{
	info->root = NULL;
	info->work_root = NULL;
	info->node = NULL;
	info->queue = queue;
	info->prev_type = null;
}

t_tree_node	*tree_seperate_case(t_tree_info *info)
{
	if (info->node->token_type == parenthsis)
		return (tree_case_parenthesis(info));
	else if (info->node->token_type == and_or)
		return (tree_case_and_or(info));
	else if (info->node->token_type == pipee)
		return (tree_case_pipe(info));
	else if (info->node->token_type == redirection)
		return (tree_case_redirection(info));
	else if (info->node->token_type == comm)
		return (tree_case_command(info));
	else if (info->node->token_type == arg)
		return (tree_case_arg(info));
	else
		return (tree_case_eof(info));
}

t_tree_node	*tree_copy_and_push(t_queue *queue, t_tree_info *info)
{
	t_tree_node	*node;

	node = copy_to_tree_node(queue);
	if (node == NULL)
		return (NULL);
	info->node = node;
	node = tree_seperate_case(info);
	if (node == NULL)
	{
		free_tree(info->root);
		return (NULL);
	}
	return (node);
}

t_tree_node	*tree_sequence(t_queue *queue)
{
	t_tree_node	*node;
	t_tree_info	info;

	tree_init_info(&info, queue);
	while (queue->head->token_type != eof)
	{
		node = tree_copy_and_push(queue, &info);
		if (node == NULL)
			return (NULL);
		if (node->token_type == parenthsis && is_parenthsis(node->element) == 2)
			return (info.root);
	}
	node = tree_copy_and_push(queue, &info);
	if (node == NULL)
		return (NULL);
	free_tree_node(info.node);
	return (info.root);
}

t_tree_node	*tree(t_queue *queue)
{
	t_tree_node	*result;

	result = tree_sequence(queue);
	if (result == NULL)
		return (tree_error(result, queue));
	else if (tree_check_end_subshell(result))
		tree_delete_end_subshell(result);
	return (result);
}
