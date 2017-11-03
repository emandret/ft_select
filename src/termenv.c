/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 00:44:47 by emandret          #+#    #+#             */
/*   Updated: 2017/11/03 02:58:45 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

int		put(int c)
{
	write(0, &c, 1);
	return (0);
}

bool	st_term_mode(bool reset)
{
	char					*name;
	static struct termios	oldt;
	struct termios			newt;

	if (!(name = getenv("TERM")))
	{
		ft_putendl_fd("ENV is not defined", 2);
		return (false);
	}
	if (tgetent(NULL, name) == -1)
		return (false);
	if (!oldt.c_iflag && !oldt.c_oflag && tcgetattr(0, &oldt) == -1)
		return (false);
	if (reset && !tcsetattr(0, TCSADRAIN, &oldt))
		return (true);
	if (!reset && !tcgetattr(0, &newt))
	{
		newt.c_lflag &= ~(ICANON | ECHO);
		newt.c_cc[VMIN] = 1;
		newt.c_cc[VTIME] = 1;
		if (!tcsetattr(0, TCSADRAIN, &newt))
			return (true);
	}
	return (false);
}

void	st_term_kill(void)
{
	tputs(tgetstr("ve", NULL), 0, &put);
	tputs(tgetstr("te", NULL), 0, &put);
	if (!st_term_mode(true))
		exit(-1);
	exit(0);
}
