/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toki_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:02:45 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:02:45 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKI_BONUS_H
# define TOKI_BONUS_H

# include "libft.h"
# include "queue.h"
# include "stack.h"
# include "minishell_bonus.h"
# include "toki_expand_bonus.h"
# include "parse_tree_bonus.h"

# define COMMAND		1
# define ARGS			2
# define REDIRECTION	4
# define IS_QUOTE		8
# define SINGLE_QUOTE	16
# define DOUBLE_QUOTE	32
# define PIPE			64
# define AND_OR			128
# define PARENTHSIS		256
# define IS_WS			512

typedef struct s_token_info
{
	int		flag;
	t_stack	*stack;
	t_queue	*queue;
}	t_token_info;

t_tree_node	*sequence(char *s);
void		init_info(t_token_info *info, t_stack *s);
void		free_info(t_token_info *info);
int			is_match_error(t_node *node, t_token_info *info);
char		*skip_white_space(char *s);
t_node		*tokenize_make_token(char *s, int len, t_token type);
t_node		*tokenize_parenthesis(char *s, t_token_info *info);
t_node		*tokenize_and_or(char *s, t_token_info *info);
t_node		*tokenize_pipe(char *s, t_token_info *info);
t_node		*tokenize_redirection(char *s, t_token_info *info);
t_token		set_token_type(t_token_info *info);
void		check_quote(char *s, t_token_info *info);
t_node		*tokenize_arg(char *s, t_token_info *info);
t_node		*tokenize_seperate_case(char *s, t_token_info *info);
char		*tokenize_next_token(char *s, t_node *node, t_token_info *info);
t_queue		*tokenize_sequence(char *s, t_token_info *info);
t_queue		*tokenize(char *s);

#endif
