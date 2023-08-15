/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:59:16 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 21:59:17 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_redirection(const char *s)
{
	if (ft_strncmp(s, "<<", 2) == 0 || ft_strncmp(s, ">>", 2) == 0)
		return (2);
	if (ft_strncmp(s, "<", 1) == 0 || ft_strncmp(s, ">", 1) == 0)
		return (1);
	return (0);
}
