/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:02 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:07:40 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_ast.h"

int	redir_i(char *filename, int mode)
{
	int	fd;

	fd = open(filename, mode);
	if (fd == -1)
	{
		print_error(NULL, filename, strerror(errno));
		return (e_failure);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (e_success);
}

int	redir_o(char *filename, int mode)
{
	int	fd;

	fd = open(filename, mode, 0644);
	if (fd == -1)
	{
		print_error(NULL, filename, strerror(errno));
		return (e_failure);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (e_success);
}

int	redir(t_tree_node *ast)
{
	if (ft_strequal(ast->element, ">"))
		return (redir_o(ast->right->element, O_CREAT | O_WRONLY | O_TRUNC));
	else if (ft_strequal(ast->element, "<"))
		return (redir_i(ast->right->element, O_RDONLY));
	else if (ft_strequal(ast->element, ">>"))
		return (redir_o(ast->right->element, O_CREAT | O_WRONLY | O_APPEND));
	else if (ft_strequal(ast->element, "<<"))
		return (redir_i(ast->right->element, O_RDONLY));
	return (e_failure);
}

int	exec_red(t_tree_node *ast)
{
	int			status;
	t_tree_node	*target;

	target = ast;
	if (target == NULL)
		return (e_success);
	else if (target->token_type == redirection)
	{
		while (target != NULL)
		{
			if (target->token_type == redirection)
			{
				status = redir(target);
				if (status != e_success)
					return (status);
			}
			target = target->right;
		}
	}
	return (e_success);
}
