/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:22 by gunjkim           #+#    #+#             */
/*   Updated: 2023/06/05 16:44:00 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"

int	check_valid_arg(char **arg)
{
	if (check_arg_has_option(arg))
	{
		print_error("cd", NULL, HAS_NO_OPTION);
		return (0);
	}
	if (arg[1] == NULL)
	{
		print_error("cd", NULL, HAS_ONLY_ONE_PATH);
		return (0);
	}
	return (1);
}

char	*cd_init(void)
{
	char	*old_pwd;

	if (ft_getenv("PWD") == NULL)
		return (NULL);
	old_pwd = ft_strdup(ft_getenv("PWD"));
	if (!old_pwd)
		error_exit("cd", NULL, strerror(errno), e_failure);
	return (old_pwd);
}

int	set_pwd_oldpwd(char *pwd, char *oldpwd)
{
	if (ft_getenv("PWD") != NULL && ft_setenv("PWD", pwd) == -1)
	{
		free(pwd);
		free(oldpwd);
		return (e_failure);
	}
	if (ft_getenv("OLDPWD") != NULL && ft_setenv("OLDPWD", oldpwd) == -1)
	{
		free(pwd);
		free(oldpwd);
		return (e_failure);
	}
	free(pwd);
	free(oldpwd);
	return (e_success);
}

int	ft_cd(char **arg)
{
	char	*cwd;
	char	*old_pwd;

	if (!check_valid_arg(arg))
		return (e_failure);
	old_pwd = cd_init();
	if (chdir(arg[1]) == -1)
	{
		free(old_pwd);
		print_error("cd", arg[1], strerror(errno));
		return (e_failure);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		free(old_pwd);
		print_error("cd", NULL, strerror(errno));
		return (e_failure);
	}
	return (set_pwd_oldpwd(cwd, old_pwd));
}
