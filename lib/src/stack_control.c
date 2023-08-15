/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:59:36 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 21:59:36 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_node	*stack_top(t_stack *stack)
{
	return (stack->top);
}

t_node	*stack_pop(t_stack *stack)
{
	t_node	*node;

	if (stack->top == NULL)
		return (NULL);
	node = stack->top;
	stack->top = stack->top->next;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	stack_push(t_stack *stack, t_node *node)
{
	if (stack->top == NULL)
	{
		stack->top = node;
	}
	else
	{
		node->next = stack->top;
		stack->top = node;
	}
}

void	stack_free(t_stack *stack)
{
	t_node	*delete;

	while (stack->top)
	{
		delete = stack_pop(stack);
		free_node(delete);
	}
}
