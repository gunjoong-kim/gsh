/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:36 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:04:37 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "builtin_bonus.h"

int	is_valid_name(char *key)
{
	if (!is_alpha(*key) && *key != '_')
	{
		errno = EINVAL;
		return (0);
	}
	key++;
	while (*key)
	{
		if (!is_alpha(*key) && !is_digit(*key) && *key != '_')
		{
			errno = EINVAL;
			return (0);
		}
		key++;
	}
	return (1);
}

char	**envlist_to_envp(t_dic *g_env_list)
{
	char			**envp;
	t_dic_element	*target;
	int				i;

	envp = (char **)xmalloc(sizeof(char *) * (g_env_list->size + 1));
	target = g_env_list->head;
	i = 0;
	while (target != NULL)
	{
		envp[i] = join_string(target->key, "=", target->value);
		if (envp[i] == NULL)
			error_exit(NULL, "join_string", strerror(errno), e_failure);
		target = target->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
