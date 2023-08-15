/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toki_expand_utils2_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 20:13:08 by jhwang            #+#    #+#             */
/*   Updated: 2023/06/03 22:58:55 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toki_expand_bonus.h"

t_queue	*expand_wildcard_accept(t_queue *queue, t_node *node)
{
	t_split	*mat;

	mat = expand_wildcard_sequence(node->element);
	if (mat == NULL)
	{
		free_node(node);
		return (NULL);
	}
	if (expand_wildcard_case(queue, mat, node) == NULL)
		return (NULL);
	expand_wildcard_free_matrix(mat, -1);
	return (queue);
}

int	check_after_heredog(t_queue *queue, t_node *node, int *flag)
{
	if (*flag && node->token_type == arg)
	{
		*flag = 0;
		queue_push(queue, node);
		return (1);
	}
	else if (node->token_type == redirection \
			&& ft_strncmp(node->element, "<<", 2) == 0)
		*flag = 1;
	return (0);
}
