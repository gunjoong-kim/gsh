/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_case_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:00:41 by jhwang            #+#    #+#             */
/*   Updated: 2023/06/03 22:00:55 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

static void	tree_case_arg_input(t_tree_info *info, t_tree_node *input_path)
{
	t_tree_node	*tmp;

	tmp = input_path;
	while (tmp->right != NULL)
		tmp = tmp->right;
	tmp->right = info->node;
}

void	tree_case_arg_red(t_tree_info *info)
{
	if (info->root->token_type == redirection)
		tree_case_arg_input(info, info->root);
	else if (info->root->token_type == compoundcmd)
		tree_case_arg_input(info, info->root->left);
	else if (info->work_root->right->token_type == redirection)
		tree_case_arg_input(info, info->work_root->right);
	else
		tree_case_arg_input(info, info->work_root->right->left);
}

int	check_arg_to_cmd(t_tree_info *info, t_tree_node *path)
{
	if (path->token_type == and_or || path->token_type == pipee)
	{
		if (path->right->token_type == compoundcmd)
			path = path->right->right->left;
		else if (path->right->token_type == simplecmd)
			path = path->right->left;
	}
	else
	{
		if (path->token_type == compoundcmd)
			path = path->right->left;
		else if (path->token_type == simplecmd)
			path = path->left;
	}
	if (path->token_type == comm && path->element == NULL)
	{
		path->element = info->node->element;
		free(info->node);
		return (1);
	}
	return (0);
}

void	tree_case_arg_cmd_arg(t_tree_info *info)
{
	if (info->root->token_type == and_or || info->root->token_type == pipee)
	{
		if (check_arg_to_cmd(info, info->work_root))
			return ;
		else if (info->work_root->right->token_type == simplecmd)
			tree_case_arg_input(info, info->work_root->right);
		else if (info->work_root->right->token_type == compoundcmd)
			tree_case_arg_input(info, info->work_root->right->right);
	}
	else
	{
		if (check_arg_to_cmd(info, info->root))
			return ;
		else if (info->root->token_type == simplecmd)
			tree_case_arg_input(info, info->root);
		else if (info->root->token_type == compoundcmd)
			tree_case_arg_input(info, info->root->right);
	}
}
