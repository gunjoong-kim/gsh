/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_util_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:04:58 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:04:58 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	*xmalloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (!p)
	{
		perror("xmalloc");
		exit(e_failure);
	}
	return (p);
}

void	*xstrdup(char *str)
{
	char			*new;
	unsigned int	s_len;

	if (str == NULL)
		return (NULL);
	s_len = ft_strlen(str);
	new = xmalloc(sizeof(char) * (s_len + 1));
	if (!new)
		return (0);
	new = ft_memcpy(new, str, s_len);
	new[s_len] = 0;
	return (new);
}

char	*join_string(char *str1, char *str2, char *str3)
{
	char	*mid;
	char	*ret;

	mid = ft_strjoin(str1, str2);
	if (mid == NULL)
		return (NULL);
	ret = ft_strjoin(mid, str3);
	if (ret == NULL)
	{
		free(mid);
		return (NULL);
	}
	free(mid);
	return (ret);
}

int	count_arg(t_tree_node *arg)
{
	int	num;

	num = 0;
	while (arg != NULL)
	{
		if (arg->element == NULL)
		{
			arg = arg->right;
			continue ;
		}
		num++;
		arg = arg->right;
	}
	return (num);
}

char	**make_exec_argv(t_tree_node *cmd, t_tree_node *arg)
{
	int			num;
	int			i;
	char		**ret;

	num = 1 + count_arg(arg);
	i = 1;
	ret = (char **)xmalloc(sizeof(char *) * (num + 1));
	ret[0] = ft_strdup(cmd->element);
	if (ret[0] == NULL)
		error_exit(NULL, "strdup", strerror(errno), e_failure);
	ret[num] = NULL;
	while (arg != NULL)
	{
		if (arg->element == NULL)
		{
			arg = arg->right;
			continue ;
		}
		ret[i] = ft_strdup(arg->element);
		if (ret[i] == NULL)
			error_exit(NULL, "strdup", strerror(errno), e_failure);
		arg = arg->right;
		i++;
	}
	return (ret);
}
