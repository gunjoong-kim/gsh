/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toki.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:02:14 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:02:15 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toki.h"

t_node	*tokenize_seperate_case(char *s, t_token_info *info)
{
	t_node	*node;

	if (is_parenthsis(s))
		node = tokenize_parenthesis(s, info);
	else if (is_and_or(s))
		node = tokenize_and_or(s, info);
	else if (is_pipe(s))
		node = tokenize_pipe(s, info);
	else if (is_redirection(s))
		node = tokenize_redirection(s, info);
	else
		node = tokenize_arg(s, info);
	return (node);
}

t_queue	*tokenize_sequence(char *s, t_token_info *info)
{
	t_node	*node;

	node = (t_node *)1;
	while (*s)
	{
		s = skip_white_space(s);
		if (*s == '\0')
			break ;
		node = NULL;
		node = tokenize_seperate_case(s, info);
		if (node == NULL)
			break ;
		s = tokenize_next_token(s, node, info);
	}
	if (is_match_error(node, info))
	{
		print_error(NULL, NULL, "matching error detected");
		g_env_list->return_value = 258;
		return (NULL);
	}
	return (info->queue);
}

t_queue	*tokenize(char *s)
{
	t_token_info	info;
	t_stack			stack;

	if (!s)
		return (NULL);
	init_info(&info, &stack);
	if (tokenize_sequence(s, &info) == NULL)
		free_info(&info);
	return (info.queue);
}

t_tree_node	*sequence(char *s)
{
	t_queue		*q;
	t_tree_node	*t;

	q = tokenize(s);
	if (q == NULL)
		return (NULL);
	if (q->head == NULL)
	{
		free(q);
		return (NULL);
	}
	if (tokenize_expand(q) == NULL)
		return (NULL);
	if (q == NULL)
		return (NULL);
	t = tree(q);
	queue_free(q);
	free(q);
	return (t);
}
