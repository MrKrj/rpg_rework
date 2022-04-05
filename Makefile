##
## EPITECH PROJECT, 2017
## my_rpg
## File description:
## Makefile
##
## ========================================================================== ##
NAME = my_rpg

CC = gcc


## ========================================================================== ##
PATH_BASICS	=	./sources/
BASICS	=	main.c									\

## ========================================================================== ##
PATH_UTILS	=	./sources/utils/
UTILS	=	tuple.c									\

## ========================================================================== ##
PATH_CORE	=	./sources/core/
CORE	=	core.c									\
			window.c								\
			timed.c									\
			gameObject.c							\

## ========================================================================== ##
PATH_DICTS	=	./sources/dicts/
DICTS	=	spriteDict.c							\
			compDict.c								\


## ========================================================================== ##
PATH_COMPS	=	./sources/components/
COMPS	=	graphics.c								\


## ========================================================================== ##
PATH_SCENES	=	./sources/scenes/
SCENES	=	intro.c									\


## ========================================================================== ##
SRC	=	$(addprefix $(PATH_BASICS), $(BASICS))		\
		$(addprefix $(PATH_UTILS), 	$(UTILS))		\
		$(addprefix $(PATH_CORE), 	$(CORE))		\
		$(addprefix $(PATH_DICTS), 	$(DICTS))		\
		$(addprefix $(PATH_COMPS), 	$(COMPS))		\
		$(addprefix $(PATH_SCENES), $(SCENES))		\


## ========================================================================== ##
REDDARK	=	\033[31;1m
RED	=	\033[31;1m
GREEN	=	\033[32;1m
YEL	=	\033[33;1m
BLUE	=	\033[34;1m
PINK	=	\033[35;1m
CYAN	=	\033[36;1m
WHITE	=	\033[0m


## ========================================================================== ##
OBJ	=	$(SRC:.c=.o)

CFLAGS = -export-dynamic -rdynamic -g -I./includes/ -D_GNU_SOURCE -W -Wall -Wextra -pedantic -O3 -O2

LDFLAGS = -lm -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -ldl


## ========================================================================== ##
all:	$(NAME)
	@printf "$(GREEN)\n$(WHITE)"
	@printf "$(GREEN)  [$(WHITE)MY_RPG$(GREEN)] → "
	@printf "$(WHITE)Compilation terminée. "
	@printf "$ Binaire : $(CYAN) ./%s$(WHITE)\n\n" $(NAME)

$(NAME):	$(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)


## ========================================================================== ##
clean:
	@rm -f $(OBJ)
	@printf "$(GREEN)\n$(WHITE)"
	@printf "$(GREEN)  [$(WHITE)MY_RPG$(GREEN)] → "
	@printf "$(WHITE)Suppression terminée.\n\n"

fclean: clean
	@rm -f *~
	@rm -f $(NAME)

re: fclean all

.PHONY: all rc clean fclean re


## ========================================================================== ##
%.o:	%.c
	@printf "$(GREEN)[$(WHITE)MY_RPG$(GREEN)] — $(WHITE)%-45s\n" $<
	@printf "$(GREEN) → $(RES) %-70s" $@
	@printf "$(GREEN)[$(WHITE)√$(GREEN)]\n\n"
	@gcc $(CFLAGS) -o $@ -c $<

## ========================================================================== ##
