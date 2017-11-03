/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 00:43:22 by emandret          #+#    #+#             */
/*   Updated: 2017/11/01 10:58:25 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "../ft_printf/src/printf/inc/ft_printf.h"
# include "termcaps.h"
# include <termios.h>
# include <stdbool.h>
# include <term.h>
# include <sys/ioctl.h>
# include <signal.h>

typedef struct		s_elem
{
	char			*name;
	bool			hovered;
	bool			selected;
	struct s_elem	*prev;
	struct s_elem	*next;
}					t_elem;

typedef t_elem		*(t_hook)(t_elem *curr);

typedef struct		s_hooks
{
	char			*key;
	t_hook			*hook;
	struct s_hooks	*next;
}					t_hooks;

/*
** display.c
*/
bool				st_print_elems(t_elem *first);

/*
** termenv.c
*/
bool				st_term_mode(bool reset);
void				st_term_kill(void);
int					put(int c);

/*
** list.c
*/
size_t				st_list_size(t_elem *first);
t_elem				*st_list_del(t_elem **first, t_elem *to_del);
t_elem				*st_fill_list(char **elems, int nb);

/*
** hook.c
*/
void				st_key_hook(t_hooks **first, char *key, t_hook *hook);
t_hook				*st_find_hook(t_hooks *first, char *key);

/*
** func.c
*/
t_elem				*st_key_hook_esc(t_elem *elem);
t_elem				*st_key_hook_space(t_elem *curr);
t_elem				*st_hook_key_right(t_elem *curr);
t_elem				*st_hook_key_left(t_elem *curr);

/*
** signals.c
*/
void				handle_sigint(int sig);
void				handle_sigtstp(int sig);
void				handle_sigcont(int sig);
void				handle_signals(void);

#endif
