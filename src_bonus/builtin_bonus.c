/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:20 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:04:20 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_bonus.h"

int	is_builtin(char *cmd)
{
	if (ft_strequal(cmd, "echo") || \
		ft_strequal(cmd, "cd") || \
		ft_strequal(cmd, "pwd") || \
		ft_strequal(cmd, "export") || \
		ft_strequal(cmd, "unset") || \
		ft_strequal(cmd, "env") || \
		ft_strequal(cmd, "exit"))
	{
		return (1);
	}
	return (0);
}

int	check_arg_has_option(char **arg)
{
	while (*arg != NULL)
	{
		if (*arg[0] == '-')
			return (1);
		arg++;
	}
	return (0);
}

int	exec_builtin(t_tree_node *ast)
{
	char	**exec_arg;
	int		exit_status;

	exit_status = e_failure;
	exec_arg = make_exec_argv(ast->left, ast->right);
	if (exec_arg == NULL)
		error_exit(NULL, "ft_split", strerror(errno), e_failure);
	if (ft_strequal(ast->left->element, "env"))
		exit_status = ft_env(exec_arg);
	else if (ft_strequal(ast->left->element, "unset"))
		exit_status = ft_unset(exec_arg);
	else if (ft_strequal(ast->left->element, "export"))
		exit_status = ft_export(exec_arg);
	else if (ft_strequal(ast->left->element, "pwd"))
		exit_status = ft_pwd();
	else if (ft_strequal(ast->left->element, "cd"))
		exit_status = ft_cd(exec_arg);
	else if (ft_strequal(ast->left->element, "exit"))
		exit_status = ft_exit(exec_arg);
	else if (ft_strequal(ast->left->element, "echo"))
		exit_status = ft_echo(exec_arg);
	free_str_array(exec_arg);
	return (exit_status);
}
