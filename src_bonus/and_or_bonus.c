/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:17 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:07:55 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_ast_bonus.h"
#include "signal_util_bonus.h"

int	make_process(t_tree_node *ast)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		return (make_exit_status(status));
	}
	else if (pid == 0)
	{
		signal_templete(CHILD);
		exit(exec_token(ast));
	}
	print_error(NULL, NULL, strerror(errno));
	exit(e_failure);
}

int	exec_and_or(t_tree_node *ast)
{
	int	exit_status;

	exit_status = e_failure;
	if (ft_strequal(ast->element, "&&"))
	{
		exit_status = make_process(ast->left);
		if (exit_status == e_success)
			exit_status = (make_process(ast->right));
	}
	else if (ft_strequal(ast->element, "||"))
	{
		exit_status = make_process(ast->left);
		if (exit_status != e_success)
			exit_status = make_process(ast->right);
	}
	return (exit_status);
}
