/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toki_expand_tokenize_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:58 by jhwang            #+#    #+#             */
/*   Updated: 2023/06/03 20:15:12 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toki_expand_bonus.h"

t_queue	*expand_tokenize_error(t_queue *queue, t_node *node)
{
	free_node(node);
	queue_free(queue);
	free(queue);
	queue = NULL;
	return (NULL);
}

t_queue	*expand_tokenize_sequence(t_queue *queue, t_node *node)
{
	t_queue	*expand_queue;

	expand_queue = tokenize(node->element);
	if (expand_queue == NULL)
		return (expand_tokenize_error(queue, node));
	if (expand_queue->head && node->token_type == arg)
		expand_queue->head->token_type = arg;
	free_node(node);
	while (expand_queue && queue_top(expand_queue) != NULL)
		queue_push(queue, queue_pop(expand_queue));
	return (expand_queue);
}
