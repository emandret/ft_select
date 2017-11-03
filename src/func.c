/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 02:04:04 by emandret          #+#    #+#             */
/*   Updated: 2017/11/01 08:12:23 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

t_elem	*st_key_hook_esc(t_elem *elem)
{
	(void)elem;
	st_term_kill();
	return (NULL);
}

t_elem	*st_key_hook_space(t_elem *elem)
{
	if (elem->hovered)
	{
		if (elem->selected)
			elem->selected = false;
		else
			elem->selected = true;
	}
	return (st_hook_key_right(elem));
}

t_elem	*st_hook_key_right(t_elem *elem)
{
	elem->hovered = false;
	elem->next->hovered = true;
	return (elem->next);
}

t_elem	*st_hook_key_left(t_elem *elem)
{
	elem->hovered = false;
	elem->prev->hovered = true;
	return (elem->prev);
}
