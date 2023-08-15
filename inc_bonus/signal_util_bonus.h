/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_util_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gunjkim <gunjkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 22:00:38 by gunjkim           #+#    #+#             */
/*   Updated: 2023/06/05 01:32:33 by gunjkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_UTIL_BONUS_H
# define SIGNAL_UTIL_BONUS_H

# define READLINE 1
# define CHILD 2
# define HERE_DOC 3
# define GENERAL 4

# define ON 0
# define OFF 1

void	signal_templete(int type);
void	switch_echoctl(int flag);
void	signal_x(int signo, void (*handler)(int));
void	print_quit_msg(int signo);

#endif
