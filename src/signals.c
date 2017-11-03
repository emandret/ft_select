/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 10:39:14 by emandret          #+#    #+#             */
/*   Updated: 2017/11/03 03:15:36 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

void	handle_sigint(int sig)
{
	(void)sig;
	st_term_kill();
}

void	handle_sigtstp(int sig)
{
	(void)sig;
	tputs(tgetstr("ve", NULL), 0, &put);
	tputs(tgetstr("te", NULL), 0, &put);
	st_term_mode(true);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, "\032");
}

void	handle_sigcont(int sig)
{
	(void)sig;
	signal(SIGTSTP, &handle_sigtstp);
	st_term_mode(false);
	tputs(tgetstr("ti", NULL), 0, &put);
	tputs(tgetstr("cl", NULL), 0, &put);
	tputs(tgetstr("vi", NULL), 0, &put);
}

void	handle_sigwinch(int sig)
{
	(void)sig;
	tputs(tgetstr("cl", NULL), 0, &put);
	// need to handle reprinting after window size change
}

void	handle_signals(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGTSTP, &handle_sigtstp);
	signal(SIGCONT, &handle_sigcont);
	signal(SIGWINCH, &handle_sigwinch);
}
