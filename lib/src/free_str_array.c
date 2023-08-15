/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:01:53 by gunjkim           #+#    #+#             */
/*   Updated: 2023/05/31 22:01:53 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_str_array(char **argv)
{
	char	**tmp;

	tmp = argv;
	while (*tmp != NULL)
	{
		free(*tmp);
		tmp++;
	}
	free(argv);
}
