/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:02:07 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:02:07 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memcpy(void *dest, const void *src, unsigned int n)
{
	unsigned char	*dest_local;
	unsigned char	*src_local;

	dest_local = dest;
	src_local = (unsigned char *)src;
	if (dest_local == 0 && src_local == 0)
		return (0);
	while (n--)
		*dest_local++ = *src_local++;
	return (dest);
}
