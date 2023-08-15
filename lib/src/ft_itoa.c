/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:02:03 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:02:04 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_get_nlen(int n, int *n_size)
{
	if (n == 0)
		*n_size += 1;
	while (n)
	{
		n /= 10;
		*n_size += 1;
	}
}

static long long	ft_init(int n, int *flag, int *n_size)
{
	long long	new;

	new = n;
	if (n < 0)
	{
		*flag = 1;
		*n_size = 1;
		return (-new);
	}
	else
	{
		*flag = 0;
		*n_size = 0;
		return (new);
	}
}

char	*ft_itoa(int n)
{
	int			flag;
	int			n_size;
	char		*s;
	long long	abs_n;

	n_size = 0;
	flag = 0;
	abs_n = ft_init(n, &flag, &n_size);
	ft_get_nlen(abs_n, &n_size);
	s = malloc(sizeof(char) * (n_size + 1));
	if (!s)
		return (0);
	s[n_size] = 0;
	if (flag)
		s[0] = '-';
	while (n_size-- > flag)
	{
		s[n_size] = '0' + (abs_n % 10);
		abs_n /= 10;
	}
	return (s);
}
