/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expander_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:05:15 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:09:18 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <queue.h>
#include "minishell_bonus.h"
#include "toki_expand_bonus.h"

int	check_format(t_split *target, t_split *backlog, char *p_n)
{
	while (*p_n != '\0' || target->source != NULL)
	{
		if (ft_strequal(target->source, "*") && target->is_wild == 1)
		{
			while (ft_strequal(target->source, "*") && target->is_wild == 1)
				target++;
			backlog = target - 1;
			if (target->source == NULL)
				return (1);
			p_n = ft_strnstr(p_n, target->source, ft_strlen(p_n));
			if (p_n == NULL)
				return (0);
		}
		else if (ft_strncmp(target->source, p_n, ft_strlen(target->source)) \
		!= 0)
			return (0);
		p_n += ft_strlen(target->source);
		target++;
		if (*p_n != '\0' && target->source == NULL)
			target = backlog;
	}
	return (1);
}

DIR	*init_expander(void)
{
	DIR		*dir_ptr;
	char	*dir_name;

	dir_name = getcwd(NULL, 0);
	if (dir_name == NULL)
		error_exit(NULL, "getcwd", strerror(errno), e_failure);
	dir_ptr = opendir(dir_name);
	if (dir_ptr == NULL)
		error_exit(NULL, "opendir", strerror(errno), e_failure);
	free(dir_name);
	return (dir_ptr);
}

char	*format_to_str(t_split *format)
{
	t_split	*target;
	char	*ret;
	char	*tmp;
	char	*app;

	ret = ft_strdup("");
	if (ret == NULL)
		error_exit(NULL, "ft_strdup", strerror(errno), e_failure);
	target = format;
	while (target->source != NULL)
	{
		app = target->source;
		tmp = ft_strjoin(ret, app);
		if (tmp == NULL)
			error_exit(NULL, "ft_strdup", strerror(errno), e_failure);
		free(ret);
		ret = tmp;
		target++;
	}
	return (ret);
}

void	if_no_match(t_queue *queue, int counter, \
t_split *format, int token_type)
{
	char	*join_string;

	if (counter == 0)
	{
		join_string = format_to_str(format);
		if (join_string == NULL)
			error_exit(NULL, NULL, strerror(errno), e_failure);
		insert_queue(queue, join_string, counter, token_type);
		free(join_string);
	}
	return ;
}

t_queue	*wildcard_expander(t_queue *queue, t_split *format, int token_type)
{
	DIR				*dir_ptr;
	struct dirent	*file;
	int				counter;

	counter = 0;
	dir_ptr = init_expander();
	while (1)
	{
		errno = 0;
		file = readdir(dir_ptr);
		if (file == NULL && errno != 0)
			error_exit(NULL, "readdir", strerror(errno), e_failure);
		if (file == NULL)
			break ;
		if (file->d_name[0] == '.' || \
		!check_format(format, format, file->d_name))
			continue ;
		if (insert_queue(queue, file->d_name, counter, token_type) == NULL)
			return (NULL);
		counter++;
	}
	if_no_match(queue, counter, format, token_type);
	closedir(dir_ptr);
	return (queue);
}
