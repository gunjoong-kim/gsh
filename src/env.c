/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:29 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:03:29 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_env(char **arg)
{
	t_dic_element	*target;

	if (arg[1] != NULL)
	{
		print_error("env", NULL, HAS_NO_OPTION_OR_ARG);
		return (e_failure);
	}
	target = g_env_list->head;
	while (target != NULL)
	{
		if (target->value != NULL)
			printf("%s=%s\n", target->key, target->value);
		target = target->next;
	}
	return (e_success);
}
