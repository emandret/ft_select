/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 00:42:19 by emandret          #+#    #+#             */
/*   Updated: 2017/11/03 02:53:11 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static size_t	get_mxl(t_elem *first)
{
	size_t	mxl;
	t_elem	*elem;

	mxl = 0;
	elem = first;
	while (elem->next != first)
	{
		if (mxl < ft_strlen(elem->name))
			mxl = ft_strlen(elem->name);
		elem = elem->next;
	}
	return (mxl);
}

static size_t	get_wpl(size_t col_size, size_t mxl)
{
	size_t	i;

	i = 0;
	while (col_size >= mxl)
	{
		col_size -= mxl;
		i++;
	}
	return (i);
}

static bool		check_size(struct winsize w, size_t mxl, size_t list_size)
{
	size_t	n;

	n = (w.ws_col * w.ws_row) / ((mxl + 1) * list_size);
	if (!n || mxl > w.ws_col)
	{
		ft_putstr_fd("Window size is too small", 2);
		return (false);
	}
	return (true);
}

static void		print_elem(t_elem *elem, int mxl)
{
	if (elem->hovered && !elem->selected)
		tputs(tgetstr("us", NULL), 0, &put);
	else if (elem->selected && !elem->hovered)
		tputs(tgetstr("mr", NULL), 0, &put);
	else if (elem->hovered && elem->selected)
	{
		tputs(tgetstr("us", NULL), 0, &put);
		tputs(tgetstr("mr", NULL), 0, &put);
	}
	ft_putstr_fd(elem->name, 0);
	tputs(tgetstr("me", NULL), 0, &put);
	if ((mxl -= ft_strlen(elem->name)) < 0)
		mxl = 0;
	while (mxl--)
		ft_putchar_fd(' ', 0);
}

bool			st_print_elems(t_elem *first)
{
	struct winsize	w;
	size_t			mxl;
	size_t			wpl;
	t_elem			*elem;

	ioctl(0, TIOCGWINSZ, &w);
	mxl = get_mxl(first) + 1;
	if (!check_size(w, mxl, st_list_size(first)))
		return (false);
	wpl = get_wpl(w.ws_col, mxl);
	elem = first;
	tputs(tgetstr("cl", NULL), 0, &put);
	while (wpl > 0)
	{
		print_elem(elem, mxl);
		wpl--;
		if (!wpl)
		{
			ft_putchar('\n');
			wpl = get_wpl(w.ws_col, mxl);
		}
		if ((elem = elem->next) == first)
			break ;
	}
	return (true);
}
