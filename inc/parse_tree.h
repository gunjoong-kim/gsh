/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:02:26 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:02:26 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_TREE_H
# define PARSE_TREE_H
# include "minishell.h"
# include "libft.h"
# include "queue.h"
# include "tree.h"

typedef struct s_tree_info
{
	t_tree_node	*root;
	t_tree_node	*work_root;
	t_tree_node	*node;
	t_queue		*queue;
	t_token		prev_type;
}	t_tree_info;

t_tree_node	*tree(t_queue *queue);
t_tree_node	*tree_sequence(t_queue *queue);
t_tree_node	*tree_copy_and_push(t_queue *queue, t_tree_info *info);
t_tree_node	*tree_seperate_case(t_tree_info *info);
t_tree_node	*tree_case_parenthesis(t_tree_info *info);
t_tree_node	*tree_case_and_or(t_tree_info *info);
t_tree_node	*tree_case_pipe(t_tree_info *info);
t_tree_node	*tree_case_redirection(t_tree_info *info);
t_tree_node	*tree_case_command(t_tree_info *info);
t_tree_node	*tree_case_arg(t_tree_info *info);
t_tree_node	*tree_case_eof(t_tree_info *info);
t_tree_node	*tree_if_open_parenthesis(t_tree_info *info);
t_tree_node	*tree_case_command_null(t_tree_info *info);
t_tree_node	*tree_case_command_and_or_pipe(t_tree_info *info);
t_tree_node	*tree_case_command_arg(t_tree_info *info);
t_tree_node	*tree_case_command_arg_red(t_tree_info *info);
t_tree_node	*tree_case_command_arg_else(t_tree_info *info);
t_tree_node	*tree_case_red_and_or_pipe(t_tree_info *info);
t_tree_node	*tree_case_red_and_or_pipe_red(t_tree_info *info);
t_tree_node	*tree_case_red_and_or_pipe_simple(t_tree_info *info);
t_tree_node	*tree_case_red_and_or_pipe_compound(t_tree_info *info);
t_tree_node	*tree_case_red_else(t_tree_info *info);
t_tree_node	*tree_case_red_else_simple(t_tree_info *info);
t_tree_node	*tree_case_red_else_compound(t_tree_info *info);
t_tree_node	*tree_case_red_else_red(t_tree_info *info);
void		tree_case_arg_red(t_tree_info *info);
void		tree_case_arg_cmd_arg(t_tree_info *info);
void		tree_init_info(t_tree_info *info, t_queue *queue);
t_tree_node	*copy_to_tree_node(t_queue *queue);
t_tree_node	*tree_print_error(t_tree_info *info);
void		tree_delete_end_subshell(t_tree_node *root);
t_tree_node	*tree_check_end_subshell(t_tree_node *root);
t_tree_node	*tree_error(t_tree_node *result, t_queue *queue);

#endif