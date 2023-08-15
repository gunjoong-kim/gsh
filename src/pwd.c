/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:59 by gunjkim           #+#    #+#             */
/*   Updated: 2023/06/05 00:20:02 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = ft_strdup(ft_getenv("PWD"));
		if (!cwd || ft_getenv("PWD") == NULL)
		{
			free(cwd);
			print_error("pwd", NULL, strerror(errno));
			return (e_failure);
		}
	}
	ft_putstr_fd(STDOUT_FILENO, cwd);
	ft_putstr_fd(STDOUT_FILENO, "\n");
	free(cwd);
	return (e_success);
}
