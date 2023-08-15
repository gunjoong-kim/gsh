/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:57 by gunjkim           #+#    #+#             */
/*   Updated: 2023/06/01 15:48:48 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_ast.h"
#include "signal_util.h"

static void	exec_child(t_tree_node *child, int *fd, pid_t *pid, int side)
{
	*pid = fork();
	if (*pid > 0)
		return ;
	else if (*pid == 0)
	{
		signal_templete(CHILD);
		if (side == left)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		else if (side == right)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		exit(exec_token(child));
	}
	error_exit(NULL, "fork", strerror(errno), e_failure);
}

int	exec_pipe(t_tree_node *ast)
{
	int		fd[2];
	int		status;
	pid_t	left_pid;
	pid_t	right_pid;

	if (pipe(fd) == -1)
		error_exit(NULL, "pipe", strerror(errno), e_failure);
	exec_child(ast->left, fd, &left_pid, left);
	exec_child(ast->right, fd, &right_pid, right);
	close(fd[0]);
	close(fd[1]);
	waitpid(left_pid, &status, 0);
	waitpid(right_pid, &status, 0);
	return (make_exit_status(status));
}
