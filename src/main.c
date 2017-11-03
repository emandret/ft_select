/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 00:42:19 by emandret          #+#    #+#             */
/*   Updated: 2017/11/03 03:00:54 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static void		ret_final(t_elem *first)
{
	t_elem	*elem;

	elem = first;
	while (1)
	{
		if (elem->selected)
		{
			ft_putstr_fd(elem->name, 0);
			ft_putchar_fd(' ', 0);
		}
		if ((elem = elem->next) == first)
			break ;
	}
}

static void		get_key(char key[4])
{
	ssize_t	ret;

	if ((ret = read(0, key, 3)))
		key[ret] = '\0';
}

static void		read_from_input(t_hooks *hook_list, t_elem **elem_list)
{
	char	key[4];
	t_elem	*curr;
	t_hook	*hook;

	ft_bzero(key, 4);
	curr = *elem_list;
	curr->hovered = true;
	while (ft_strcmp(KEY_CODE_ENTER, key))
	{
		if (!ft_strcmp(KEY_CODE_BSP, key) && curr->hovered)
			curr = st_list_del(elem_list, curr);
		if ((hook = st_find_hook(hook_list, key)))
			curr = (hook)(curr);
		st_print_elems(*elem_list);
		get_key(key);
	}
}

static t_hooks	*register_hooks(void)
{
	t_hooks	*hooks;

	hooks = NULL;
	st_key_hook(&hooks, KEY_CODE_ESC, &st_key_hook_esc);
	st_key_hook(&hooks, KEY_CODE_SPACE, &st_key_hook_space);
	st_key_hook(&hooks, KEY_CODE_RIGHT, &st_hook_key_right);
	st_key_hook(&hooks, KEY_CODE_LEFT, &st_hook_key_left);
	return (hooks);
}

int				main(int argc, char *argv[])
{
	t_hooks	*hook_list;
	t_elem	*elem_list;

	handle_signals();
	if (argc < 2)
	{
		ft_putendl_fd("No arguments", 2);
		return (-1);
	}
	hook_list = register_hooks();
	elem_list = st_fill_list(argv, argc);
	if (!st_term_mode(false))
		return (-1);
	tputs(tgetstr("ti", NULL), 0, &put);
	tputs(tgetstr("cl", NULL), 0, &put);
	tputs(tgetstr("vi", NULL), 0, &put);
	read_from_input(hook_list, &elem_list);
	tputs(tgetstr("ve", NULL), 0, &put);
	tputs(tgetstr("te", NULL), 0, &put);
	ret_final(elem_list);
	if (!st_term_mode(true))
		return (-1);
	return (0);
}
