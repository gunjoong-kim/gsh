/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:14:12 by jhwang            #+#    #+#             */
/*   Updated: 2023/06/01 15:53:47 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H
# include "list.h"

typedef struct s_stack
{
	t_node	*top;
}	t_stack;

t_node	*stack_top(t_stack *stack);
t_node	*stack_pop(t_stack *stack);
void	stack_push(t_stack *stack, t_node *node);
void	stack_free(t_stack *stack);
#endif