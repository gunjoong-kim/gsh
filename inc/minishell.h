/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:00:02 by gunjkim           #+#    #+#             */
/*   Updated: 2023/06/01 16:08:01 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "tree.h"
# include "libft.h"
# include "dic.h"

# define TMP_FILE_LEN 15
# define SHELL_NAME "-minishell $ "
# define ERR_SHELL_NAME "minishell"

# define HAS_NO_OPTION "has no option"
# define HAS_ONLY_ONE_PATH "has only one relative or absolute path"
# define HAS_NO_OPTION_OR_ARG "has no option or arg"
# define TOO_MANY_ARG "too many arguments"
# define NUMERIC_ARG_REQUIRED "numeric argument required"
# define NOT_A_IDENTIFIER "not a valid identifier"
# define C_N_F_MSG "command not found"
# define C_IS_DIR_MSG "is a directory"

typedef enum e_exit_status
{
	e_ast_is_null = -1,
	e_success = 0,
	e_failure = 1,
	e_c_n_exec = 126,
	e_c_n_found = 127,
	e_signal_c_exit = 130,
	e_signal_q_exit = 131,
}	t_exit_status;

extern t_dic	*g_env_list;

void	print_syntax_error(char *target);
void	print_error(char *cmd, char *target, char *msg);
void	error_exit(char *cmd, char *target, char *msg, int code);
void	print_arg_error(char *cmd, char *target, char *msg);

char	*join_string(char *str1, char *str2, char *str3);
char	**make_exec_argv(t_tree_node *cmd, t_tree_node *arg);

t_dic	*init_g_env_list(char *envp[]);
char	*ft_getenv(char *key);
int		ft_setenv(char *key, char *value);
int		is_valid_name(char *key);
char	**envlist_to_envp(t_dic *g_env_list);

#endif
