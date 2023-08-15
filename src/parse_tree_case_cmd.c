/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_case_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:00:45 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:00:46 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

t_tree_node	*tree_case_command_null(t_tree_info *info)
{
	t_tree_node	*tmp;

	tmp = create_tree_node(ft_strdup(""), simplecmd);
	if (tmp == NULL)
		return (NULL);
	info->root = tmp;
	tmp->left = info->node;
	info->prev_type = comm;
	return (info->node);
}

t_tree_node	*tree_case_command_and_or_pipe(t_tree_info *info)
{
	t_tree_node	*tmp;

	tmp = create_tree_node(ft_strdup(""), simplecmd);
	if (tmp == NULL)
		return (NULL);
	info->work_root->right = tmp;
	tmp->left = info->node;
	info->prev_type = comm;
	return (info->node);
}

t_tree_node	*tree_case_command_arg_red(t_tree_info *info)
{
	t_tree_node	*tmp;

	tmp = create_tree_node(ft_strdup(""), compoundcmd);
	if (tmp == NULL)
		return (NULL);
	tmp->left = info->root;
	info->root = tmp;
	tmp->right = create_tree_node(ft_strdup(""), simplecmd);
	if (tmp->right == NULL)
		return (NULL);
	tmp->right->left = info->node;
	info->prev_type = comm;
	return (info->node);
}

t_tree_node	*tree_case_command_arg_else(t_tree_info *info)
{
	t_tree_node	*tmp;

	tmp = create_tree_node(ft_strdup(""), compoundcmd);
	if (tmp == NULL)
		return (NULL);
	tmp->left = info->work_root->right;
	info->work_root->right = tmp;
	tmp->right = create_tree_node(ft_strdup(""), simplecmd);
	if (tmp->right == NULL)
		return (NULL);
	tmp->right->left = info->node;
	info->prev_type = comm;
	return (info->node);
}

t_tree_node	*tree_case_command_arg(t_tree_info *info)
{
	if (info->root->token_type == redirection)
		return (tree_case_command_arg_red(info));
	else
		return (tree_case_command_arg_else(info));
}
