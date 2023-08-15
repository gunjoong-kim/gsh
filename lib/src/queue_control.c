/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:59:30 by jhwang            #+#    #+#             */
/*   Updated: 2023/06/05 15:47:14 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

t_node	*queue_top(t_queue *queue)
{
	return (queue->head);
}

t_node	*queue_pop(t_queue *queue)
{
	t_node	*node;

	if (queue->head == NULL)
		return (NULL);
	node = queue->head;
	if (queue->head == queue->head->next)
		queue->head = NULL;
	else
	{
		queue->head = queue->head->next;
		queue->head->prev = node->prev;
		node->prev->next = queue->head;
	}
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	queue_push(t_queue *queue, t_node *node)
{
	if (queue->head == NULL)
	{
		queue->head = node;
		node->prev = queue->head;
		node->next = queue->head;
	}
	else
	{
		node->prev = queue->head->prev;
		node->next = queue->head;
		node->prev->next = node;
		queue->head->prev = node;
	}
}

void	queue_free(t_queue *queue)
{
	t_node	*delete;

	while (queue->head)
	{
		delete = queue_pop(queue);
		free_node(delete);
	}
}

t_queue	*insert_queue(t_queue *queue, char *name, int counter, int token_type)
{
	t_node	*target;

	target = (t_node *)malloc(sizeof(t_node));
	if (target == NULL)
		return (NULL);
	if (counter == 0 && token_type == comm)
		target->token_type = comm;
	else
		target->token_type = arg;
	target->element = ft_strdup(name);
	if (target->element == NULL)
		return (NULL);
	target->prev = NULL;
	target->next = NULL;
	queue_push(queue, target);
	return (queue);
}
