/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_case2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:22 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:03:23 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

t_tree_node	*tree_case_redirection(t_tree_info *info)
{
	if (info->prev_type == null)
		info->root = info->node;
	else if (info->prev_type == and_or || info->prev_type == pipee)
		info->work_root->right = info->node;
	else if (info->prev_type == comm || info->prev_type == arg)
	{
		if (info->root->token_type == and_or || info->root->token_type == pipee)
			return (tree_case_red_and_or_pipe(info));
		else
			return (tree_case_red_else(info));
	}
	else
		return (tree_print_error(info));
	info->prev_type = redirection;
	return (info->node);
}

t_tree_node	*tree_case_arg(t_tree_info *info)
{
	if (info->prev_type == redirection)
		tree_case_arg_red(info);
	else if (info->prev_type == comm || info->prev_type == arg)
		tree_case_arg_cmd_arg(info);
	else
		return (tree_print_error(info));
	info->prev_type = arg;
	return (info->node);
}
