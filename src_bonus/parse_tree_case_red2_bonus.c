/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_case_red2_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:15 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:03:16 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

t_tree_node	*tree_case_red_else_simple(t_tree_info *info)
{
	t_tree_node	*tmp;

	tmp = create_tree_node(ft_strdup(""), compoundcmd);
	if (tmp == NULL)
		return (NULL);
	tmp->right = info->root;
	info->root = tmp;
	info->prev_type = redirection;
	return (info->node);
}

t_tree_node	*tree_case_red_else_compound(t_tree_info *info)
{
	t_tree_node	*tmp;

	if (info->root->left == NULL)
		info->root->left = info->node;
	else
	{
		tmp = info->root->left;
		while (tmp->right != NULL)
			tmp = tmp->right;
		tmp->right = info->node;
	}
	info->prev_type = redirection;
	return (info->node);
}

t_tree_node	*tree_case_red_else_red(t_tree_info *info)
{
	t_tree_node	*tmp;

	tmp = info->root;
	while (tmp->right != NULL)
		tmp = tmp->right;
	tmp->right = info->node;
	info->prev_type = redirection;
	return (info->node);
}

t_tree_node	*tree_case_red_else(t_tree_info *info)
{
	if (info->root->token_type == simplecmd)
	{
		if (tree_case_red_else_simple(info) == NULL)
			return (NULL);
	}
	if (info->root->token_type == compoundcmd)
		return (tree_case_red_else_compound(info));
	else if (info->root->token_type == redirection)
		return (tree_case_red_else_red(info));
	info->prev_type = redirection;
	return (info->node);
}
