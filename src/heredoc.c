/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:45 by gunjkim           #+#    #+#             */
/*   Updated: 2023/06/05 01:06:22 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_ast.h"

void	init_filename(char *filename)
{
	filename[0] = '/';
	filename[1] = 't';
	filename[2] = 'm';
	filename[3] = 'p';
	filename[4] = '/';
}

char	*make_tmp_filename(void)
{
	int			fd;
	int			index;
	char		*filename;
	const char	*alphabet = "abcdefghijklmnopqrstuvwxyz\
	ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	index = 5;
	filename = (char *)xmalloc(sizeof(char) * TMP_FILE_LEN + 1);
	init_filename(filename);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		error_exit(NULL, "open", strerror(errno), e_failure);
	while (index < TMP_FILE_LEN)
	{
		read(fd, &filename[index], 1);
		filename[index] = alphabet[filename[index] % 62];
		index++;
	}
	filename[TMP_FILE_LEN] = '\0';
	close(fd);
	return (filename);
}

void	readline_to_tmpfile(int tmp_fd, char *delimeter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strequal(line, delimeter) || line == NULL)
			break ;
		write(tmp_fd, line, ft_strlen(line));
		write(tmp_fd, "\n", 1);
		free(line);
	}
	free(line);
}

void	heredoc(t_tree_node *ast, int pipe)
{
	char	*filename;
	int		tmp_fd;

	filename = make_tmp_filename();
	while (access(filename, F_OK) == 0)
	{
		free(filename);
		filename = make_tmp_filename();
	}
	tmp_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd == -1)
		error_exit(NULL, "open", strerror(errno), e_failure);
	write(pipe, filename, TMP_FILE_LEN + 1);
	readline_to_tmpfile(tmp_fd, ast->right->element);
	close(tmp_fd);
}

void	recursive_heredoc(t_tree_node *ast, int pipe)
{
	if (ast == NULL)
		return ;
	if (ft_strequal(ast->element, "<<"))
		heredoc(ast, pipe);
	recursive_heredoc(ast->left, pipe);
	recursive_heredoc(ast->right, pipe);
}
