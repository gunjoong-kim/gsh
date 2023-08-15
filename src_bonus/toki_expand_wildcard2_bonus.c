/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toki_expand_wildcard2_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:09 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:04:09 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toki_expand_bonus.h"

int	expand_wildcard_get_split_count(char *str)
{
	t_int_qroup	n;

	n.flag = 0;
	n.count = 0;
	n.len = 0;
	while (str && str[n.len])
	{
		if (is_quote(str + n.len))
		{
			expand_wildcard_check_count_case(&n.count, &n.flag);
			n.len += expand_wildcard_quote_match(str + n.len);
		}
		else if (str[n.len] == '*')
		{
			n.flag = 1;
			n.count++;
		}
		else
			expand_wildcard_check_count_case(&n.count, &n.flag);
		n.len++;
	}
	return (n.count);
}

int	expand_wildcard_get_split_len(char *str)
{
	t_int_qroup	n;

	n.flag = 0;
	n.count = 0;
	n.len = 0;
	while (str && str[n.len])
	{
		if (is_quote(str + n.len))
			n.len += expand_wildcard_quote_match(str + n.len);
		else if (str[n.len] == '*')
		{
			if (n.len == 0)
				return (1);
			else
				return (n.len);
		}
		n.len++;
	}
	return (n.len);
}

t_split	*expand_wildcard_free_matrix(t_split *mat, int count)
{
	int	idx;

	idx = 0;
	if (count == -1)
	{
		while (mat[idx].source)
			free(mat[idx++].source);
		free(mat);
	}
	else
	{
		while (idx < count)
			free(mat[idx++].source);
		free(mat);
	}
	return (NULL);
}

t_split	*expand_wildcard_make_string_matrix(char *str, int count)
{
	t_split		*matrix;
	t_int_qroup	n;

	matrix = NULL;
	matrix = malloc(sizeof(t_split) * (count + 1));
	if (matrix == NULL)
		return (NULL);
	n.col = 0;
	n.len = 0;
	while (n.col < count)
	{
		n.row = expand_wildcard_get_split_len(str + n.len);
		n.len += n.row;
		matrix[n.col].source = malloc(sizeof(char) * (n.row + 1));
		if (matrix[n.col].source == NULL)
			return (expand_wildcard_free_matrix(matrix, n.col));
		matrix[n.col].source[n.row] = '\0';
		matrix[n.col].is_wild = 0;
		n.col++;
	}
	matrix[n.col].source = NULL;
	return (matrix);
}

void	init_int_group(t_int_qroup *n)
{
	n->col = 0;
	n->row = 0;
	n->len = 0;
	n->idx = 0;
	n->flag = 0;
	n->count = 0;
}
