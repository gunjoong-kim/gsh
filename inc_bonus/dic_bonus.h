/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dic_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:00:25 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:00:25 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIC_BONUS_H
# define DIC_BONUS_H

# include <stdlib.h>
# include "libft.h"

typedef struct s_dic_element {
	char					*key;
	char					*value;
	struct s_dic_element	*next;
}	t_dic_element;

typedef struct s_dic {
	t_dic_element	*head;
	int				size;
	int				return_value;
}	t_dic;

t_dic			*init_dictionary(void);
t_dic_element	*add_dic(t_dic *dic, char *key, char *value);
void			delete_dic(t_dic *dic, char *key);
void			clear_dic(t_dic *dic);
void			*xmalloc(size_t size);
void			*xstrdup(char *str);

#endif
