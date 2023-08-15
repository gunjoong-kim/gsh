/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:45 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:04:46 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"

int	is_numeric(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!is_digit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	ft_exit(char **arg)
{
	if (arg[1] == NULL)
	{
		ft_putstr_fd(STDERR_FILENO, "exit\n");
		exit(e_success);
	}
	if (!is_numeric(arg[1]))
	{
		ft_putstr_fd(STDERR_FILENO, "exit\n");
		error_exit("exit", arg[1], NUMERIC_ARG_REQUIRED, 255);
	}
	if (arg[2] != NULL)
	{
		print_error("exit", NULL, TOO_MANY_ARG);
		return (e_failure);
	}
	ft_putstr_fd(STDERR_FILENO, "exit\n");
	exit(ft_atoi(arg[1]));
}
