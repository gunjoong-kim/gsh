/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:03:32 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:03:32 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *cmd, char *target, char *msg)
{
	int	stdout_copy;

	stdout_copy = dup(STDOUT_FILENO);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(e_failure);
	}
	printf("%s", "minishell: ");
	if (cmd != NULL)
		printf("%s: ", cmd);
	if (target != NULL)
		printf("%s: ", target);
	printf("%s\n", msg);
	if (dup2(stdout_copy, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(e_failure);
	}
	close(stdout_copy);
}

void	print_syntax_error(char *target)
{	
	int	stdout_copy;

	stdout_copy = dup(STDOUT_FILENO);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(e_failure);
	}
	printf("minishell: syntax error near unexpected token `%s'\n", target);
	if (dup2(stdout_copy, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(e_failure);
	}
	close(stdout_copy);
}

void	error_exit(char *cmd, char *target, char *msg, int code)
{
	print_error(cmd, target, msg);
	exit(code);
}

void	print_arg_error(char *cmd, char *target, char *msg)
{
	int	stdout_copy;

	stdout_copy = dup(STDOUT_FILENO);
	if (dup2(STDERR_FILENO, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(e_failure);
	}
	printf("%s", "minishell: ");
	if (cmd != NULL)
		printf("%s: ", cmd);
	if (target != NULL)
		printf("`%s\': ", target);
	printf("%s\n", msg);
	if (dup2(stdout_copy, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(e_failure);
	}
	close(stdout_copy);
}
