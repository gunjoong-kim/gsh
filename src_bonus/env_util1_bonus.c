/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util1_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:34 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:04:34 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "builtin_bonus.h"

char	**key_value_arr(char *str)
{
	char	**ret;
	int		loc;
	int		len;

	loc = 0;
	len = 0;
	ret = (char **)xmalloc(sizeof(char *) * 3);
	while (str[len] != '\0')
		len++;
	while (str[loc] != '=' && str[loc] != '\0')
		loc++;
	ret[0] = ft_substr(str, 0, loc);
	if (ft_strchr(str, '=') == NULL)
		ret[1] = NULL;
	else
	{
		ret[1] = ft_substr(str, loc + 1, len);
		if (ret[0] == NULL || ret[1] == NULL)
			error_exit(NULL, "ft_substr", strerror(errno), e_failure);
	}
	if (ret[0] == NULL)
		error_exit(NULL, "ft_substr", strerror(errno), e_failure);
	ret[2] = NULL;
	return (ret);
}

t_dic	*init_g_env_list(char *envp[])
{
	t_dic			*g_env_list;
	t_dic_element	*ret;
	char			**key_value;

	g_env_list = init_dictionary();
	if (g_env_list == NULL)
		error_exit(NULL, "init_dictionary", strerror(errno), e_failure);
	while (*envp != NULL)
	{
		key_value = key_value_arr(*envp);
		ret = add_dic(g_env_list, key_value[0], key_value[1]);
		free_str_array(key_value);
		if (ret == NULL)
			error_exit(NULL, "add_dic", strerror(errno), e_failure);
		envp++;
	}
	return (g_env_list);
}

char	*ft_getenv(char *key)
{
	t_dic_element	*target;

	target = g_env_list->head;
	while (target != NULL)
	{
		if (ft_strequal(target->key, key))
			return (target->value);
		target = target->next;
	}
	return (NULL);
}

int	ft_setenv(char *key, char *value)
{
	if (is_valid_name(key) == 0)
	{
		errno = EINVAL;
		return (-1);
	}
	if (add_dic(g_env_list, key, value) == NULL)
	{
		errno = ENOMEM;
		return (-1);
	}
	return (0);
}
