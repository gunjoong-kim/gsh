/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_util_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:05:09 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:05:09 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include "minishell_bonus.h"
#include "signal_util_bonus.h"

void	switch_echoctl(int flag)
{
	struct termios	term;

	if (isatty(STDIN_FILENO) == 0)
		return ;
	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		exit(e_failure);
	}
	if (flag == 0)
		term.c_lflag |= ECHOCTL;
	else if (flag == 1)
		term.c_lflag &= (~ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcsetattr");
		exit(e_failure);
	}
}

void	readline_cntl_c_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	g_env_list->return_value = 1;
}

void	print_quit_msg(int signo)
{
	if (signo != SIGQUIT)
		return ;
	ft_putstr_fd(STDOUT_FILENO, "Quit: 3");
}

void	signal_x(int signo, void (*handler)(int))
{
	if (signal(signo, handler) == SIG_ERR)
		exit(e_failure);
}

void	signal_templete(int type)
{
	if (type == READLINE)
		signal_x(SIGINT, readline_cntl_c_handler);
	else if (type == CHILD)
	{
		signal_x(SIGINT, SIG_DFL);
		signal_x(SIGQUIT, SIG_DFL);
		return ;
	}
	else if (type == HERE_DOC)
		signal_x(SIGINT, SIG_DFL);
	else if (GENERAL)
	{
		signal_x(SIGINT, SIG_IGN);
		signal_x(SIGQUIT, print_quit_msg);
		return ;
	}
	signal_x(SIGQUIT, SIG_IGN);
}
