/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toki_utils2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:18 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:04:18 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "toki_bonus.h"

t_token	set_token_type(t_token_info *info)
{
	if (info->flag & REDIRECTION)
	{
		info->flag &= ~REDIRECTION;
		return (arg);
	}
	else if (!(info->flag & COMMAND))
	{
		info->flag |= COMMAND;
		return (comm);
	}
	else
		return (arg);
}

t_node	*tokenize_make_token(char *s, int len, t_token type)
{
	char	*elem;
	t_node	*node;

	elem = ft_substr(s, 0, len);
	if (elem == NULL)
		return (NULL);
	node = create_node(elem, type);
	if (node == NULL)
	{
		free(elem);
		return (NULL);
	}
	return (node);
}

char	*tokenize_next_token(char *s, t_node *node, t_token_info *info)
{
	s += ft_strlen(node->element);
	queue_push(info->queue, node);
	return (s);
}
