/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:01:39 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:01:40 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

# include "list.h"

void			*ft_memcpy(void *dest, const void *src, unsigned int n);
char			*ft_strdup(const char *s);
unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int size);
int				ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
char			*ft_substr(char const *s, unsigned int start, unsigned int len);
int				ft_strequal(char *s1, char *s2);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
int				is_alpha(const char c);
int				is_and_or(const char *s);
int				is_op(const char *s);
int				is_parenthsis(const char *s);
int				is_pipe(const char *s);
int				is_quote(const char *s);
int				is_redirection(const char *s);
int				is_ws(const char c);
int				is_digit(const char c);
int				is_name(const char c);
void			free_str_array(char **argv);
void			ft_putstr_fd(int fd, const char *str);
char			*ft_strchr(const char *s, int c);
char			*ft_strnstr(const char *haystack, \
				const char *needle, size_t len);
char			*ft_itoa(int n);
int				ft_atoi(const char *str);
void			free_tree(t_tree_node *root);

#endif