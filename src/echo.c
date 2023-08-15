/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:21 by gunjkim           #+#    #+#             */
/*   Updated: 2023/06/04 19:50:52 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_n_option(char *arg)
{
	if (*arg != '-')
		return (0);
	arg++;
	while (*arg != '\0')
	{
		if (*arg != 'n')
			return (0);
		arg++;
	}
	return (1);
}

int	ft_echo(char **arg)
{
	int		is_n;
	char	**target;

	if (arg[1] != NULL)
		is_n = is_n_option(arg[1]);
	else
		is_n = 0;
	target = arg + 1;
	while (*target != NULL && is_n_option(*target))
		target++;
	while (*target != NULL)
	{
		ft_putstr_fd(STDOUT_FILENO, *target);
		if (*(target + 1) != NULL)
			ft_putstr_fd(STDOUT_FILENO, " ");
		target++;
	}
	if (!is_n)
		ft_putstr_fd(STDOUT_FILENO, "\n");
	return (e_success);
}
