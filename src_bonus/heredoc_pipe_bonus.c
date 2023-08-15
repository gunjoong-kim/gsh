/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:52 by gunjkim           #+#    #+#             */
/*   Updated: 2023/06/05 16:15:18 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_ast_bonus.h"
#include "signal_util_bonus.h"

void	delimeter_to_tmpfile(t_tree_node *ast, int fd, t_queue *queue)
{
	char	*filename;

	if (ast == NULL)
		return ;
	if (ft_strequal(ast->element, "<<"))
	{
		filename = (char *)xmalloc(sizeof(char) * (TMP_FILE_LEN + 1));
		if (read(fd, filename, TMP_FILE_LEN + 1) > 0)
		{
			if (insert_queue(queue, filename, 0, 0) == NULL)
				error_exit(NULL, NULL, strerror(errno), e_failure);
			free(ast->right->element);
			ast->right->element = filename;
		}
		else
			free(filename);
	}
	delimeter_to_tmpfile(ast->left, fd, queue);
	delimeter_to_tmpfile(ast->right, fd, queue);
}

int	exec_heredoc(t_tree_node *ast, t_queue *queue)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (pipe(fd) == -1)
		error_exit(NULL, "pipe", strerror(errno), e_failure);
	pid = fork();
	if (pid == 0)
	{
		signal_templete(HERE_DOC);
		close(fd[0]);
		recursive_heredoc(ast, fd[1]);
		exit(e_success);
	}
	else if (pid > 0)
	{
		signal_x(SIGQUIT, SIG_IGN);
		close(fd[1]);
		delimeter_to_tmpfile(ast, fd[0], queue);
		close(fd[0]);
		waitpid(pid, &status, 0);
		signal_x(SIGQUIT, print_quit_msg);
		return (make_exit_status(status));
	}
	exit(e_failure);
}
