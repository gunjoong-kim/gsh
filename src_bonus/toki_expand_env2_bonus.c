/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toki_expand_env2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:51 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 22:03:52 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toki_expand_bonus.h"

static void	input_quote(t_expand_info *info, char *str, int len, int len2)
{
	if (is_quote(&info->expand_str[len]) == 2)
	{
		str[len2++] = '\'';
		str[len2++] = info->expand_str[len++];
		str[len2++] = '\'';
	}
	else
	{
		str[len2++] = '\"';
		str[len2++] = info->expand_str[len++];
		str[len2++] = '\"';
	}
}

static int	add_quote(t_expand_info *info, int count)
{
	char	*str;
	int		len;
	int		len2;

	str = malloc(sizeof(char) * (info->expand_len + (2 * count) + 1));
	if (str == NULL)
		return (expand_set_error(info));
	str[info->expand_len + (2 * count)] = '\0';
	len = 0;
	len2 = 0;
	while (len < info->expand_len)
	{
		if (is_quote(&info->expand_str[len]))
		{
			input_quote(info, str, len, len2);
			len += 1;
			len2 += 3;
		}
		else
			str[len2++] = info->expand_str[len++];
	}
	str[len2] = info->expand_str[len];
	free(info->expand_str);
	info->expand_str = str;
	return (info->is_error);
}

int	check_include_quote(t_expand_info *info)
{
	int	len;
	int	count;

	len = 0;
	count = 0;
	while (info->in_quote == 0 && len < info->expand_len)
	{
		if (is_quote(&info->expand_str[len]))
			count++;
		len++;
	}
	if (count && !info->in_quote)
		return (add_quote(info, count));
	return (info->is_error);
}
