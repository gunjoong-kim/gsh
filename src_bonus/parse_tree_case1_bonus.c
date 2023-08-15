/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_case1_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:19 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:03:19 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

t_tree_node	*tree_case_parenthesis(t_tree_info *info)
{
	t_tree_node	*tmp;

	if (is_parenthsis(info->node->element) == 1)
		return (tree_if_open_parenthesis(info));
	else if (is_parenthsis(info->node->element) == 2)
	{
		if (info->prev_type == comm || info->prev_type == arg \
		|| info->prev_type == parenthsis)
		{
			tmp = info->root;
			while (tmp->right != NULL)
				tmp = tmp->right;
			tmp->right = info->node;
			return (info->node);
		}
		else
			return (tree_print_error(info));
	}
	info->prev_type = parenthsis;
	return (info->node);
}

t_tree_node	*tree_case_and_or(t_tree_info *info)
{
	if (info->prev_type == parenthsis || info->prev_type == comm \
	|| info->prev_type == arg)
	{
		info->node->left = info->root;
		info->root = info->node;
		info->work_root = info->node;
		info->prev_type = and_or;
		return (info->node);
	}
	else
		return (tree_print_error(info));
}

t_tree_node	*tree_case_pipe(t_tree_info *info)
{
	if (info->prev_type == parenthsis || info->prev_type == comm \
	|| info->prev_type == arg)
	{
		if (info->root->token_type == and_or)
		{
			info->node->left = info->root->right;
			info->root->right = info->node;
		}
		else
		{
			info->node->left = info->root;
			info->root = info->node;
		}
		info->work_root = info->node;
		info->prev_type = pipee;
		return (info->node);
	}
	else
		return (tree_print_error(info));
}

t_tree_node	*tree_case_command(t_tree_info *info)
{
	if (info->prev_type == null)
		return (tree_case_command_null(info));
	else if (info->prev_type == and_or || info->prev_type == pipee)
		return (tree_case_command_and_or_pipe(info));
	else if (info->prev_type == arg)
		return (tree_case_command_arg(info));
	else
		return (tree_print_error(info));
}

t_tree_node	*tree_case_eof(t_tree_info *info)
{
	if (info->prev_type == and_or \
	|| info->prev_type == pipee \
	|| info->prev_type == redirection)
		return (tree_print_error(info));
	return (info->node);
}
