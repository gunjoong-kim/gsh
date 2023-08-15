/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:25 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:08:08 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_ast_bonus.h"
#include "builtin_bonus.h"
#include "signal_util_bonus.h"
#include <sys/stat.h>

char	*is_cur(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (cmd);
	error_exit(NULL, cmd, strerror(errno), e_c_n_found);
	return (NULL);
}

char	*cmd_with_path(char *cmd, char **path)
{
	char	*ret;
	char	*cmd_dup;

	cmd_dup = ft_strdup(cmd);
	if (cmd_dup == NULL)
		error_exit(NULL, "ft_strdup", strerror(errno), e_failure);
	if (ft_strchr(cmd_dup, '/') != NULL || path == NULL)
		return (is_cur(cmd_dup));
	while (*path != NULL && ft_strlen(cmd_dup) > 0)
	{
		ret = join_string(*path, "/", cmd_dup);
		if (ret == NULL)
			error_exit(NULL, "join_string", strerror(errno), e_failure);
		if (access(ret, X_OK) == 0)
		{
			free(cmd_dup);
			return (ret);
		}
		free(ret);
		path++;
	}
	return (NULL);
}

void	exec_binary(t_tree_node *ast)
{
	char		**path;
	char		**exec_arg;
	char		*cmd;
	struct stat	statbuf;

	errno = 0;
	path = ft_split(ft_getenv("PATH"), ':');
	if (path == NULL && errno == ENOMEM)
		error_exit(NULL, "ft_split", strerror(errno), e_failure);
	cmd = cmd_with_path(ast->left->element, path);
	if (cmd == NULL)
		error_exit(ast->left->element, NULL, C_N_F_MSG, e_c_n_found);
	exec_arg = make_exec_argv(ast->left, ast->right);
	execve(cmd, exec_arg, envlist_to_envp(g_env_list));
	if (stat(cmd, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
		error_exit(cmd, NULL, C_IS_DIR_MSG, e_c_n_exec);
	error_exit(cmd, NULL, strerror(errno), e_c_n_exec);
}

int	exec_simple_cmd(t_tree_node *ast)
{
	pid_t	pid;
	int		status;

	if (ast->left->element == NULL)
		return (e_success);
	else if (is_builtin(ast->left->element))
		return (exec_builtin(ast));
	else
	{
		pid = fork();
		if (pid > 0)
		{
			waitpid(pid, &status, 0);
			return (make_exit_status(status));
		}
		else if (pid == 0)
		{
			signal_templete(CHILD);
			exec_binary(ast);
		}
		else
			error_exit(NULL, "fork", strerror(errno), e_failure);
	}
	return (e_failure);
}

int	exec_cmd(t_tree_node *ast)
{
	int	exit_status;

	exit_status = e_failure;
	exit_status = exec_token(ast->left);
	if (exit_status != e_success)
		return (exit_status);
	return (exec_token(ast->right));
}
