/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:02:19 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:02:19 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char			*new;
	unsigned int	s_len;

	s_len = ft_strlen(s);
	new = malloc(sizeof(char) * (s_len + 1));
	if (!new)
		return (0);
	new = ft_memcpy(new, s, s_len);
	new[s_len] = 0;
	return (new);
}
