/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:55 by gunjkim           #+#    #+#             */
/*   Updated: 2023/06/05 00:29:53 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include "exec_ast_bonus.h"
#include "signal_util_bonus.h"
#include "toki_bonus.h"
#include "toki_expand_bonus.h"

t_dic	*g_env_list;

void	init_minishell(char **envp, t_tree *ast)
{
	char	*cur_shlvl;

	g_env_list = init_g_env_list(envp);
	ast->root = NULL;
	cur_shlvl = ft_getenv("SHLVL");
	if (cur_shlvl == NULL)
		return ;
	else
	{
		cur_shlvl = ft_itoa(ft_atoi(cur_shlvl) + 1);
		if (cur_shlvl == NULL)
			error_exit(NULL, "ft_itoa", strerror(errno), e_failure);
	}
	if (ft_setenv("SHLVL", cur_shlvl) != 0)
		error_exit(NULL, "ft_setenv", strerror(errno), e_failure);
	free(cur_shlvl);
}

void	start_loop(t_tree *ast)
{
	char	*line;

	while (1)
	{
		switch_echoctl(OFF);
		signal_templete(READLINE);
		line = readline(SHELL_NAME);
		if (!line)
			break ;
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		add_history(line);
		ast->root = sequence(line);
		free(line);
		if (ast->root == NULL)
			continue ;
		g_env_list->return_value = exec_ast(ast->root);
	}
}

int	main(int argc, char *envp[])
{
	t_tree	ast;

	if (argc != 1)
		return (1);
	init_minishell(envp + 2, &ast);
	start_loop(&ast);
	rl_clear_history();
	clear_dic(g_env_list);
	return (0);
}
