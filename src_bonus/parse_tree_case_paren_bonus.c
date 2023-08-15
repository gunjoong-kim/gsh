/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_case_paren_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:08 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:03:08 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

t_tree_node	*tree_if_open_parenthesis(t_tree_info *info)
{
	if (info->prev_type == null)
	{
		free_tree_node(info->node);
		info->root = tree(info->queue);
		if (info->root == NULL)
			return (NULL);
	}
	else if (info->prev_type == and_or || info->prev_type == pipee)
	{
		free_tree_node(info->node);
		info->work_root->right = tree(info->queue);
		if (info->work_root->right == NULL)
			return (NULL);
	}
	else
		return (tree_print_error(info));
	info->prev_type = parenthsis;
	return (info->node);
}
