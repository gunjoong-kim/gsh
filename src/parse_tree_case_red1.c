/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_case_red1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:00:52 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:00:53 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

t_tree_node	*tree_case_red_and_or_pipe_red(t_tree_info *info)
{
	t_tree_node	*tmp;

	tmp = info->work_root->right;
	while (tmp->right != NULL)
		tmp = tmp->right;
	tmp->right = info->node;
	info->prev_type = redirection;
	return (info->node);
}

t_tree_node	*tree_case_red_and_or_pipe_simple(t_tree_info *info)
{
	t_tree_node	*tmp;

	tmp = create_tree_node(ft_strdup(""), compoundcmd);
	if (tmp == NULL)
		return (NULL);
	tmp->right = info->work_root->right;
	info->work_root->right = tmp;
	info->prev_type = redirection;
	return (info->node);
}

t_tree_node	*tree_case_red_and_or_pipe_compound(t_tree_info *info)
{
	t_tree_node	*tmp;

	if (info->work_root->right->left == NULL)
		info->work_root->right->left = info->node;
	else
	{
		tmp = info->work_root->right->left;
		while (tmp->right != NULL)
			tmp = tmp->right;
		tmp->right = info->node;
	}
	info->prev_type = redirection;
	return (info->node);
}

t_tree_node	*tree_case_red_and_or_pipe(t_tree_info *info)
{
	if (info->work_root->right == NULL)
	{
		info->work_root->right = info->node;
		return (info->node);
	}
	else if (info->work_root->right->token_type == redirection)
		return (tree_case_red_and_or_pipe_red(info));
	else if (info->work_root->right->token_type == simplecmd)
	{
		if (tree_case_red_and_or_pipe_simple(info) == NULL)
			return (NULL);
	}
	if (info->work_root->right->token_type == compoundcmd)
		return (tree_case_red_and_or_pipe_compound(info));
	info->prev_type = redirection;
	return (info->node);
}
