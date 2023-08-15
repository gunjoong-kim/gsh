/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toki_expand_wildcard1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:01:54 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:01:55 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toki_expand.h"

char	*expand_find_vaild_wildcard(char *str)
{
	int	flag;
	int	ret;

	flag = 0;
	ret = 0;
	while (str && *str)
	{
		ret = is_quote(str);
		if (flag == 0 && ret != 0)
			flag = ret;
		else if (flag != 0 && ret != 0)
		{
			if (flag == ret)
				flag = 0;
		}
		else if (flag == 0 && ret == 0)
			if (*str == '*')
				return (str);
		str++;
	}
	return (NULL);
}

t_queue	*expand_wildcard_error(t_queue *queue, t_node *node)
{
	free_node(node);
	queue_free(queue);
	free(queue);
	return (NULL);
}

void	expand_replace_and_push(t_queue *queue, t_node *node, t_split *src)
{
	t_int_qroup	n;

	n.col = 0;
	n.row = 0;
	n.idx = 0;
	while (src[n.col].source != NULL)
	{
		node->element[n.idx++] = src[n.col].source[n.row++];
		if (src[n.col].source[n.row] == '\0')
		{
			n.col++;
			n.row = 0;
		}
	}
	node->element[n.idx] = '\0';
	queue_push(queue, node);
}

int	expand_wildcard_quote_match(char *str)
{
	t_int_qroup	n;

	n.len = 1;
	n.flag = is_quote(str);
	while (str[n.len])
	{
		if (is_quote(&str[n.len]) == n.flag)
			return (n.len);
		else
			n.len++;
	}
	return (0);
}

int	expand_wildcard_check_count_case(int *count, int *flag)
{
	if (*count == 0)
		(*count)++;
	else if (*flag)
	{
		*flag = 0;
		(*count)++;
	}
	return (*count);
}
