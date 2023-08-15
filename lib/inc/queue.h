/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:14:07 by jhwang            #+#    #+#             */
/*   Updated: 2023/06/01 15:53:52 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H
# include "list.h"
# include "libft.h"

typedef struct s_queue
{
	t_node	*head;
}	t_queue;

t_node	*queue_top(t_queue *queue);
t_node	*queue_pop(t_queue *queue);
void	queue_push(t_queue *queue, t_node *node);
void	queue_free(t_queue *queue);
t_queue	*insert_queue(t_queue *queue, char *name, int counter, int token_type);

#endif