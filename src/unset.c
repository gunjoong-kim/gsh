/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:09 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:07:47 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_unset(char **arg)
{
	int	exit_status;

	arg++;
	exit_status = e_success;
	while (*arg != NULL)
	{
		if (is_valid_name(*arg))
			delete_dic(g_env_list, *arg);
		else
		{
			print_arg_error("unset", *arg, NOT_A_IDENTIFIER);
			exit_status = e_failure;
		}
		arg++;
	}
	return (exit_status);
}
