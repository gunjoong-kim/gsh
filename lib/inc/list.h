/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:14:03 by jhwang            #+#    #+#             */
/*   Updated: 2023/06/01 15:53:58 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <stdlib.h>

typedef enum e_token {
	null = 0,
	ws,
	comm,
	arg,
	redirection,
	and_or,
	pipee,
	parenthsis,
	quote,
	compoundcmd,
	simplecmd,
	eof
}	t_token;

typedef struct s_node
{
	t_token			token_type;
	char			*element;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

typedef struct s_tree_node
{
	t_token				token_type;
	char				*element;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

t_node		*create_node(char *element, t_token type);
void		free_node(t_node *list);
t_tree_node	*create_tree_node(char *element, t_token type);
void		free_tree_node(t_tree_node *list);

#endif
