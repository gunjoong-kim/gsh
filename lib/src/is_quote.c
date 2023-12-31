/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:59:13 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 21:59:14 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_quote(const char *s)
{
	if (ft_strncmp(s, "\'", 1) == 0)
		return (1);
	if (ft_strncmp(s, "\"", 1) == 0)
		return (2);
	return (0);
}
