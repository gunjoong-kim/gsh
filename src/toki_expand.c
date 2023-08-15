/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toki_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:02:05 by jhwang            #+#    #+#             */
/*   Updated: 2023/06/03 20:12:24 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toki_expand.h"

t_queue	*expand_push_eof(t_queue *queue)
{
	t_node	*endnode;

	endnode = tokenize_make_token("newline", 7, eof);
	if (endnode == NULL)
		return (NULL);
	queue_push(queue, endnode);
	return (queue);
}

t_queue	*expand_env(t_queue *queue)
{
	t_node			*node;
	t_expand_info	info;
	int				flag;

	flag = 0;
	while (queue->head->token_type != eof)
	{
		node = queue_pop(queue);
		if (check_after_heredog(queue, node, &flag))
			continue ;
		else if (node->token_type == redirection \
				&& ft_strncmp(node->element, "<<", 2) == 0)
			flag = 1;
		expand_init_info(&info, node);
		if (expand_from_string(&info))
			return (expand_free_data(&info, queue, node));
		node->element = info.str;
		queue_push(queue, node);
	}
	queue_push(queue, queue_pop(queue));
	return (queue);
}

t_queue	*expand_tokenize(t_queue *queue)
{
	t_queue	*expand_queue;
	t_node	*node;
	int		flag;

	flag = 0;
	while (queue->head->token_type != eof)
	{
		expand_queue = NULL;
		node = queue_pop(queue);
		if (check_after_heredog(queue, node, &flag))
			continue ;
		if ((node->token_type == comm || node->token_type == arg) \
			&& node->element != NULL)
		{
			expand_queue = expand_tokenize_sequence(queue, node);
			if (expand_queue == NULL)
				return (NULL);
		}
		else
			queue_push(queue, node);
		free(expand_queue);
	}
	queue_push(queue, queue_pop(queue));
	return (queue);
}

t_queue	*expand_wildcard(t_queue *queue)
{
	t_node	*node;
	int		flag;

	flag = 0;
	while (queue->head->token_type != eof)
	{
		node = queue_pop(queue);
		if (check_after_heredog(queue, node, &flag))
			continue ;
		if (node->element != NULL)
		{
			if (expand_wildcard_accept(queue, node) == NULL)
				return (NULL);
		}
		else
			queue_push(queue, node);
	}
	queue_push(queue, queue_pop(queue));
	return (queue);
}

t_queue	*tokenize_expand(t_queue *queue)
{
	if (expand_push_eof(queue) == NULL)
		return (NULL);
	if (expand_env(queue) == NULL)
		return (NULL);
	if (expand_tokenize(queue) == NULL)
		return (NULL);
	if (expand_wildcard(queue) == NULL)
		return (NULL);
	return (queue);
}
