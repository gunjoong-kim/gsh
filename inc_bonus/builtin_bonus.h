/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:00:21 by gunjkim           #+#    #+#             */
/*   Updated: 2023/06/01 16:27:41 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_BONUS_H
# define BUILTIN_BONUS_H

# include "minishell_bonus.h"

int		ft_cd(char **arg);
int		ft_pwd(void);
int		ft_env(char **arg);
int		ft_unset(char **arg);
int		ft_export(char **arg);
int		ft_exit(char **arg);
int		ft_echo(char **arg);
int		exec_builtin(t_tree_node *ast);
int		is_builtin(char *cmd);
int		is_valid_name(char *str);
int		check_arg_has_option(char **arg);
char	**key_value_arr(char *str);

#endif
