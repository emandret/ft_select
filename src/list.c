/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 00:42:19 by emandret          #+#    #+#             */
/*   Updated: 2017/11/01 09:35:09 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static t_elem	*new_elem(char *name)
{
	t_elem	*new;

	if (!(new = (t_elem*)ft_memalloc(sizeof(t_elem))))
		return (NULL);
	new->name = ft_strdup(name);
	return (new);
}

static t_elem	*push_elem(t_elem *first, char *name)
{
	t_elem	*elem;

	if (!first)
		return (new_elem(name));
	elem = first;
	while (elem->next)
		elem = elem->next;
	elem->next = new_elem(name);
	elem->next->prev = elem;
	return (first);
}

t_elem			*st_list_del(t_elem **first, t_elem *to_del)
{
	if (to_del->prev == to_del && to_del->next == to_del)
		st_term_kill();
	to_del->next->prev = to_del->prev;
	to_del->prev->next = to_del->next;
	to_del->next->hovered = true;
	*first = to_del->next;
	return (to_del->next);
}

size_t			st_list_size(t_elem *first)
{
	t_elem	*elem;
	size_t	i;

	elem = first;
	i = 0;
	while (1)
	{
		i++;
		if ((elem = elem->next) == first)
			break ;
	}
	return (i);
}

t_elem			*st_fill_list(char **elems, int nb)
{
	t_elem	*first;
	t_elem	*last;
	int		i;

	first = NULL;
	i = 0;
	while (i < (nb - 1))
	{
		first = push_elem(first, elems[i + 1]);
		i++;
	}
	last = first;
	while (last->next)
		last = last->next;
	last->next = first;
	first->prev = last;
	return (first);
}
