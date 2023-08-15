/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toki_expand_env3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:01:31 by jhwang            #+#    #+#             */
/*   Updated: 2023/06/03 17:27:40 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toki_expand.h"

int	expand_get_retcode(t_expand_info *info)
{
	info->expand_str = ft_itoa(g_env_list->return_value);
	if (info->expand_str == NULL)
		return (expand_set_error(info));
	info->expand_len = ft_strlen(info->expand_str);
	info->name_len = 1;
	return (info->is_error);
}

int	expand_get_raw_str(t_expand_info *info)
{
	int	quote;
	int	len;
	int	idx;

	quote = is_quote(&info->str[info->len + 1]);
	len = 1;
	idx = info->len + 2;
	while (info->str[idx])
	{
		if (is_quote(&info->str[idx]) == quote)
		{
			len++;
			break ;
		}
		len++;
		idx++;
	}
	info->expand_len = len;
	info->name_len = len;
	info->in_quote += 5;
	info->expand_str = ft_substr(info->str, info->len + 1, info->expand_len);
	if (info->expand_str == NULL)
		return (expand_set_error(info));
	return (info->is_error);
}

int	expand_get_name(t_expand_info *info)
{
	info->name_len = expand_get_name_len(info->str + info->len + 1);
	if (info->name_len == 0)
	{
		info->expand_str = ft_strdup("$");
		info->expand_len = 1;
		if (info->expand_str == NULL)
			return (expand_set_error(info));
	}
	else
	{
		if (expand_copy_env_value(info))
			return (info->is_error);
	}
	return (info->is_error);
}

int	expand_seperate_case(t_expand_info *info)
{
	if (info->str[info->len + 1] == '?')
	{
		if (expand_get_retcode(info))
			return (info->is_error);
	}
	else if (!info->in_quote && is_quote(&info->str[info->len + 1]))
	{
		if (expand_get_raw_str(info))
			return (info->is_error);
	}
	else if (expand_get_name(info))
		return (info->is_error);
	if (!info->in_quote && check_include_quote(info))
		return (info->is_error);
	if (info->in_quote >= 5)
		info->in_quote -= 5;
	return (expand_replace_string(info));
}

int	expand_from_string(t_expand_info *info)
{
	info->in_quote = 0;
	while (info->str && info->str[info->len])
	{
		if (is_quote(&info->str[info->len]))
		{
			if (info->in_quote == 0)
				info->in_quote = is_quote(&info->str[info->len]);
			else if (info->in_quote == is_quote(&info->str[info->len]))
				info->in_quote = 0;
			info->len++;
		}
		else if (info->in_quote != 1 && info->str[info->len] == '$')
		{
			if (expand_seperate_case(info))
				return (info->is_error);
		}
		else
			info->len++;
	}
	return (info->is_error);
}
