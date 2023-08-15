/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toki_expand_env1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:01:25 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:01:25 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toki_expand.h"

int	expand_copy_env_value(t_expand_info *info)
{
	char	*value;

	value = ft_substr(info->str, info->len + 1, info->name_len);
	if (value == NULL)
		return (expand_set_error(info));
	info->expand_str = ft_getenv(value);
	free(value);
	if (info->expand_str != NULL)
	{
		info->expand_str = ft_strdup(info->expand_str);
		if (info->expand_str == NULL)
			return (expand_set_error(info));
		info->expand_len = ft_strlen(info->expand_str);
	}
	return (info->is_error);
}

char	*expand_merge_string(t_expand_info *info)
{
	char	*new;

	new = NULL;
	new = expand_get_new_string(info->before, info->expand_str, info);
	if (new == NULL && info->is_error)
		return (NULL);
	if (info->before)
		info->before = NULL;
	if (info->expand_str)
		info->expand_str = NULL;
	new = expand_get_new_string(new, info->after, info);
	if (new == NULL && info->is_error)
		return (NULL);
	if (info->after)
		info->after = NULL;
	return (new);
}

int	expand_replace_string(t_expand_info *info)
{
	int		after_start;
	char	*new;

	if (info->len != 0)
	{
		info->before = ft_substr(info->str, 0, info->len);
		if (info->before == NULL)
			return (expand_set_error(info));
	}
	after_start = info->len + info->name_len + 1;
	if (info->str[after_start] != '\0')
	{
		info->after = ft_substr(info->str, after_start, \
						ft_strlen(info->str + after_start));
		if (info->after == NULL)
			return (expand_set_error(info));
	}
	new = expand_merge_string(info);
	if (new == NULL && info->is_error)
		return (info->is_error);
	free(info->str);
	info->str = new;
	info->len += info->expand_len;
	info->expand_len = 0;
	return (info->is_error);
}
