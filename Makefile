# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emandret <emandret@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/01 00:39:13 by emandret          #+#    #+#              #
#    Updated: 2017/11/01 10:58:45 by emandret         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

SRCDIR = src
SRC = display.c hook.c list.c main.c termenv.c func.c signals.c

OBJDIR = obj
OBJ = $(SRC:.c=.o)

LIBDIR = ft_printf
LIB = ftprintf

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

all: $(LIBDIR)/lib$(LIB).a $(OBJDIR) $(NAME)

$(LIBDIR)/lib$(LIB).a:
	@make -C $(LIBDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(addprefix $(OBJDIR)/, $(OBJ))
	@$(CC) $(CFLAGS) $(addprefix $(OBJDIR)/, $(OBJ)) -o $(NAME) -L $(LIBDIR) -l $(LIB) -L /usr/lib -l termcap
	@tput setaf 77 ; echo [DONE]

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo compiled $<

clean:
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBDIR)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBDIR)

re: fclean all

.PHONY: re fclean clean all
