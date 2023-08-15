/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toki_case.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:01:20 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:01:21 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toki.h"

t_node	*tokenize_parenthesis(char *s, t_token_info *info)
{
	t_node	*node;

	if (is_parenthsis(s) == 1)
	{
		node = tokenize_make_token(s, 1, parenthsis);
		if (node == NULL)
			return (NULL);
		stack_push(info->stack, node);
	}
	else if (is_parenthsis(s) == 2)
	{
		node = stack_top(info->stack);
		if (!node || is_parenthsis(node->element) != 1)
			return (NULL);
		else
			free_node(stack_pop(info->stack));
	}
	info->flag = 0;
	node = tokenize_make_token(s, 1, parenthsis);
	return (node);
}

t_node	*tokenize_and_or(char *s, t_token_info *info)
{
	t_node	*node;

	info->flag = 0;
	node = tokenize_make_token(s, 2, and_or);
	return (node);
}

t_node	*tokenize_pipe(char *s, t_token_info *info)
{
	t_node	*node;

	info->flag = 0;
	node = tokenize_make_token(s, 1, pipee);
	return (node);
}

t_node	*tokenize_redirection(char *s, t_token_info *info)
{
	t_node	*node;

	info->flag |= REDIRECTION;
	node = tokenize_make_token(s, is_redirection(s), redirection);
	return (node);
}

t_node	*tokenize_arg(char *s, t_token_info *info)
{
	t_node	*node;
	t_token	type;
	int		len;

	type = set_token_type(info);
	len = 0;
	while (s[len])
	{
		if (is_quote(s + len))
		{
			check_quote(s + len, info);
			len++;
		}
		else if (info->flag & IS_QUOTE)
			len++;
		else if (!is_ws(s[len]) && !is_parenthsis(s + len) && !is_op(s + len))
				len++;
		else
			break ;
	}
	node = tokenize_make_token(s, len, type);
	return (node);
}
