/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toki_expand_wildcard3_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:12 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:04:12 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toki_expand_bonus.h"

void	expand_wildcard_fill_no_quote(char *str, t_split *mat, t_int_qroup *n)
{
	n->len++;
	while (--n->count)
		mat[n->col].source[n->row++] = str[n->len++];
}

void	expand_wildcard_fill_star(t_split *mat, t_int_qroup *n, char *str)
{
	mat[n->col].is_wild = 1;
	mat[n->col++].source[0] = str[n->len];
	n->row = 0;
}

void	expand_wildcard_fill_data(char *str, t_split *mat, int count)
{
	t_int_qroup	n;

	init_int_group(&n);
	while (str[n.len] && n.col < count)
	{
		if (is_quote(str + n.len))
		{
			n.count = expand_wildcard_quote_match(str + n.len);
			if (n.count == 0)
				mat[n.col].source[n.row++] = str[n.len];
			else
				expand_wildcard_fill_no_quote(str, mat, &n);
		}
		else if (str[n.len] == '*')
		{
			if (n.row)
				n.col++;
			expand_wildcard_fill_star(mat, &n, str);
		}
		else
			mat[n.col].source[n.row++] = str[n.len];
		n.len++;
	}
	if (mat[n.col].source != NULL)
		mat[n.col].source[n.row] = '\0';
}

t_split	*expand_wildcard_sequence(char *str)
{
	t_split	*mat;
	int		count;

	count = expand_wildcard_get_split_count(str);
	mat = expand_wildcard_make_string_matrix(str, count);
	if (mat == NULL)
		return (NULL);
	expand_wildcard_fill_data(str, mat, count);
	return (mat);
}

t_queue	*expand_wildcard_case(t_queue *queue, t_split *mat, t_node *node)
{
	if ((node->token_type == comm || node->token_type == arg) \
		&& expand_find_vaild_wildcard(node->element) != NULL)
	{
		if (wildcard_expander(queue, mat, node->token_type) == NULL)
			return (expand_wildcard_error(queue, node));
		free_node(node);
	}
	else
		expand_replace_and_push(queue, node, mat);
	return (queue);
}
