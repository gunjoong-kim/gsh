/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:34 by gunjkim           #+#    #+#             */
/*   Updated: 2023/06/05 15:46:59 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_ast.h"
#include "signal_util.h"

void	clear_ast(t_tree_node *ast)
{
	t_tree_node	*left;
	t_tree_node	*right;

	if (ast == NULL)
		return ;
	left = ast->left;
	right = ast->right;
	free(ast->element);
	free(ast);
	clear_ast(left);
	clear_ast(right);
}

void	clear_all(t_tree_node *ast, t_queue *heredoc)
{
	t_node	*target;
	t_node	*target_prev;

	if (heredoc->head != NULL)
	{
		target = heredoc->head;
		while (target->next != heredoc->head)
		{
			if (unlink(target->element) == -1)
				print_error(NULL, "unlink", strerror(errno));
			target_prev = target;
			target = target->next;
			free(target_prev->element);
			free(target_prev);
		}
		if (unlink(target->element) == -1)
			print_error(NULL, "unlink", strerror(errno));
		free(target->element);
		free(target);
	}
	clear_ast(ast);
}

int	make_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		ft_putstr_fd(STDOUT_FILENO, "\n");
		return (WTERMSIG(status) + 128);
	}
	return (e_failure);
}

int	exec_token(t_tree_node *ast)
{
	if (ast == NULL)
		return (e_success);
	else if (ast->token_type == and_or)
		return (exec_and_or(ast));
	else if (ast->token_type == pipee)
		return (exec_pipe(ast));
	else if (ast->token_type == compoundcmd)
		return (exec_cmd(ast));
	else if (ast->token_type == redirection)
		return (exec_red(ast));
	else if (ast->token_type == simplecmd)
		return (exec_simple_cmd(ast));
	print_error(NULL, NULL, "invalid token type");
	return (e_failure);
}

int	exec_ast(t_tree_node *ast)
{
	t_queue	heredoc_q;
	int		stdin_backup;
	int		stdout_backup;
	int		minishell_exit_status;
	int		heredoc_exit_status;

	heredoc_q.head = NULL;
	signal_templete(GENERAL);
	heredoc_exit_status = exec_heredoc(ast, &heredoc_q);
	if (heredoc_exit_status != e_success)
	{
		clear_all(ast, &heredoc_q);
		return (heredoc_exit_status);
	}
	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	switch_echoctl(ON);
	minishell_exit_status = exec_token(ast);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdout_backup);
	clear_all(ast, &heredoc_q);
	return (minishell_exit_status);
}
