/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_alpha.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhwang <jhwang@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:58:48 by jhwang            #+#    #+#             */
/*   Updated: 2023/05/31 21:58:49 by jhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_alpha(const char c)
{
	if ((c >= 65 && c <= 90) || \
	(c >= 97 && c <= 122))
		return (1);
	return (0);
}
