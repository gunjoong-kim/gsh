/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toki_expand_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:01 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:04:01 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toki_expand_bonus.h"

int	expand_set_error(t_expand_info *info)
{
	info->is_error = 1;
	return (info->is_error);
}

void	expand_init_info(t_expand_info *info, t_node *node)
{
	info->str = node->element;
	info->len = 0;
	info->name_len = 0;
	info->before = NULL;
	info->after = NULL;
	info->expand_str = NULL;
	info->expand_len = 0;
	info->is_error = 0;
	info->in_quote = 0;
}

t_queue	*expand_free_data(t_expand_info *info, t_queue *queue, t_node *node)
{
	if (info->before != NULL)
		free(info->before);
	if (info->expand_str != NULL)
		free(info->expand_str);
	if (info->after != NULL)
		free(info->after);
	free_node(node);
	queue_free(queue);
	free(queue);
	return (NULL);
}

int	expand_get_name_len(char *s)
{
	int	len;

	len = 0;
	if (s && (is_alpha(s[len]) || s[len] == '_'))
		len++;
	else
		return (0);
	while (s && is_name(s[len]))
		len++;
	return (len);
}

char	*expand_get_new_string(char *s1, char *s2, t_expand_info *info)
{
	char	*new;

	new = NULL;
	if (s1 && s2)
	{
		new = ft_strjoin(s1, s2);
		if (new == NULL)
		{
			expand_set_error(info);
			return (NULL);
		}
		free(s1);
		free(s2);
	}
	else if (s1 && !s2)
		return (s1);
	else if (!s1 && s2)
		return (s2);
	return (new);
}
