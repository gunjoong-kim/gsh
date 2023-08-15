/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:40 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:03:40 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	swap_dic_element(t_dic_element *d1, t_dic_element *d2)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = d2->key;
	tmp_value = d2->value;
	d2->key = d1->key;
	d2->value = d1->value;
	d1->key = tmp_key;
	d1->value = tmp_value;
}

void	sort_env_list(t_dic *env_list_copy)
{
	t_dic_element	*tmp;
	t_dic_element	*target;
	t_dic_element	*min;

	min = env_list_copy->head;
	target = env_list_copy->head;
	while (target != NULL)
	{
		tmp = target;
		while (tmp != NULL)
		{
			if (ft_strncmp(min->key, tmp->key, ft_strlen(min->key)) > 0)
				min = tmp;
			tmp = tmp->next;
		}
		swap_dic_element(target, min);
		min = target->next;
		target = target->next;
	}
}

void	print_g_env_list(t_dic env_list_copy)
{
	t_dic_element	*target;

	sort_env_list(&env_list_copy);
	target = env_list_copy.head;
	while (target != NULL)
	{
		if (target->value == NULL)
			printf("declare -x %s\n", target->key);
		else
			printf("declare -x %s=\"%s\"\n", target->key, target->value);
		target = target->next;
	}
}

int	insert_env_list(char **arg)
{
	char	**key_value;
	int		exit_status;

	exit_status = e_success;
	while (*arg != NULL)
	{
		key_value = key_value_arr(*arg);
		if (ft_setenv(key_value[0], key_value[1]) == -1)
		{
			if (errno == ENOMEM)
				error_exit(NULL, "ft_setenv", strerror(errno), e_failure);
			print_arg_error("export", *arg, NOT_A_IDENTIFIER);
			exit_status = e_failure;
		}
		free_str_array(key_value);
		arg++;
	}
	return (exit_status);
}

int	ft_export(char **argv)
{
	int		exit_status;
	char	**option_or_arg;

	option_or_arg = argv + 1;
	exit_status = e_success;
	if (*option_or_arg == NULL)
		print_g_env_list(*g_env_list);
	else
		exit_status = insert_env_list(option_or_arg);
	return (exit_status);
}
