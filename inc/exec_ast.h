/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:59:56 by gunjkim           #+#    #+#             */
/*   Updated: 2023/06/05 15:02:15 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_AST_H
# define EXEC_AST_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

# include "minishell.h"
# include "queue.h"

typedef enum e_side
{
	left = 0,
	right = 1
}	t_side;

int		exec_ast(t_tree_node *ast);
int		exec_token(t_tree_node *ast);
int		exec_and_or(t_tree_node *ast);
int		exec_pipe(t_tree_node *ast);
int		exec_red(t_tree_node *ast);
int		exec_simple_cmd(t_tree_node *ast);
int		exec_cmd(t_tree_node *ast);
int		exec_heredoc(t_tree_node *ast, t_queue *heredoc_q);
void	recursive_heredoc(t_tree_node *ast, int fd);
int		make_exit_status(int status);

#endif
