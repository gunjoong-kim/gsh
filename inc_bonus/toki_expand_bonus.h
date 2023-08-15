/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toki_expand_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:02:47 by jhwang            #+#    #+#             */
/*   Updated: 2023/06/03 20:16:59 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKI_EXPAND_BONUS_H
# define TOKI_EXPAND_BONUS_H
# include "libft.h"
# include "queue.h"
# include "dic_bonus.h"
# include "minishell_bonus.h"
# include "toki_bonus.h"

typedef struct s_expand_info
{
	char	*str;
	int		len;
	int		name_len;
	char	*before;
	char	*after;
	char	*expand_str;
	int		expand_len;
	int		is_error;
	int		in_quote;
}	t_expand_info;

typedef struct s_int_group
{
	int	row;
	int	col;
	int	len;
	int	idx;
	int	flag;
	int	count;
}	t_int_qroup;

typedef struct s_split
{
	char	*source;
	int		is_wild;
}	t_split;

t_queue	*wildcard_expander(t_queue *queue, t_split *format, int token_type);
t_queue	*tokenize_expand(t_queue *queue);
t_queue	*expand_env(t_queue *queue);
t_queue	*expand_tokenize(t_queue *queue);
t_queue	*expand_wildcard(t_queue *queue);
void	expand_init_info(t_expand_info *info, t_node *node);
t_queue	*expand_free_data(t_expand_info *info, t_queue *queue, t_node *node);
t_queue	*expand_push_eof(t_queue *queue);
int		check_after_heredog(t_queue *queue, t_node *node, int *flag);
int		expand_get_name_len(char *s);
char	*expand_get_new_string(char *s1, char *s2, t_expand_info *info);
int		expand_set_error(t_expand_info *info);
int		expand_copy_env_value(t_expand_info *info);
int		expand_replace_string(t_expand_info *info);
int		expand_get_name(t_expand_info *info);
int		expand_get_retcode(t_expand_info *info);
int		expand_get_raw_str(t_expand_info *info);
int		check_include_quote(t_expand_info *info);
int		expand_seperate_case(t_expand_info *info);
int		expand_from_string(t_expand_info *info);
t_queue	*expand_tokenize_sequence(t_queue *queue, t_node *node);
t_queue	*expand_tokenize_error(t_queue *queue, t_node *node);
t_queue	*expand_wildcard_error(t_queue *queue, t_node *node);
char	*expand_find_vaild_wildcard(char *str);
void	expand_replace_and_push(t_queue *queue, t_node *node, t_split *src);
t_queue	*expand_wildcard_accept(t_queue *queue, t_node *node);
t_split	*expand_wildcard_sequence(char *str);
t_queue	*expand_wildcard_case(t_queue *queue, t_split *mat, t_node *node);
int		expand_wildcard_quote_match(char *str);
int		expand_wildcard_check_count_case(int *count, int *flag);
int		expand_wildcard_get_split_count(char *str);
int		expand_wildcard_get_split_len(char *str);
t_split	*expand_wildcard_make_string_matrix(char *str, int count);
void	init_int_group(t_int_qroup *n);
void	expand_wildcard_fill_data(char *str, t_split *mat, int count);
void	expand_wildcard_fill_no_quote(char *str, t_split *mat, t_int_qroup *n);
t_split	*expand_wildcard_free_matrix(t_split *mat, int count);

#endif
