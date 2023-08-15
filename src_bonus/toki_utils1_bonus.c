/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toki_utils1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:15 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:04:15 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toki_bonus.h"

void	init_info(t_token_info *info, t_stack *s)
{
	t_queue	*q;

	info->flag = 0;
	s->top = NULL;
	q = xmalloc(sizeof(t_queue));
	q->head = NULL;
	info->queue = q;
	info->stack = s;
}

void	free_info(t_token_info *info)
{
	stack_free(info->stack);
	queue_free(info->queue);
	free(info->queue);
	info->queue = NULL;
}

int	is_match_error(t_node *node, t_token_info *info)
{
	if (node == NULL)
		return (1);
	if (stack_top(info->stack) != NULL)
		return (1);
	if (info->flag & IS_QUOTE)
		return (1);
	return (0);
}

char	*skip_white_space(char *s)
{
	while (*s && is_ws(*s))
		s++;
	return (s);
}

void	check_quote(char *s, t_token_info *info)
{
	if (info->flag & IS_QUOTE)
	{
		if (is_quote(s) == 1 && info->flag & SINGLE_QUOTE)
			info->flag &= ~(IS_QUOTE | SINGLE_QUOTE);
		else if (is_quote(s) == 2 && info->flag & DOUBLE_QUOTE)
			info->flag &= ~(IS_QUOTE | DOUBLE_QUOTE);
	}
	else
	{
		if (is_quote(s) == 1)
			info->flag |= (IS_QUOTE | SINGLE_QUOTE);
		else
			info->flag |= (IS_QUOTE | DOUBLE_QUOTE);
	}
}
