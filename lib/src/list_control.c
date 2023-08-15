/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:59:22 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 21:59:23 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_node	*create_node(char *element, t_token type)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (new == NULL)
		return (NULL);
	new->token_type = type;
	new->element = element;
	new->token_type = type;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

t_tree_node	*create_tree_node(char *element, t_token type)
{
	t_tree_node	*new;

	new = malloc(sizeof(t_tree_node));
	if (new == NULL)
		return (NULL);
	new->token_type = type;
	new->element = element;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	free_node(t_node *node)
{
	if (node)
	{
		if (node->element != NULL)
			free(node->element);
		free(node);
	}
}

void	free_tree_node(t_tree_node *node)
{
	if (node)
	{
		if (node->element != NULL)
			free(node->element);
		free(node);
	}
}
