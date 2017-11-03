/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 00:42:19 by emandret          #+#    #+#             */
/*   Updated: 2017/11/01 01:40:46 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static t_hooks	*new_key_hook(char *key, t_hook *hook)
{
	t_hooks	*new;

	if (!(new = (t_hooks*)ft_memalloc(sizeof(t_hooks))))
		return (NULL);
	new->key = ft_strdup(key);
	new->hook = hook;
	return (new);
}

void			st_key_hook(t_hooks **first, char *key, t_hook *hook)
{
	t_hooks	*key_hook;

	if (first)
	{
		if (*first)
		{
			key_hook = *first;
			while (key_hook->next)
				key_hook = key_hook->next;
			key_hook->next = new_key_hook(key, hook);
		}
		else
			*first = new_key_hook(key, hook);
	}
}

t_hook			*st_find_hook(t_hooks *first, char *key)
{
	while (first)
	{
		if (!ft_strcmp(key, first->key))
			return (first->hook);
		first = first->next;
	}
	return (NULL);
}
