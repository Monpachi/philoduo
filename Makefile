# # **************************************************************************** #
# #                                                                              #
# #                                                         :::      ::::::::    #
# #    Makefile                                           :+:      :+:    :+:    #
# #                                                     +:+ +:+         +:+      #
# #    By: vchan <vchan@student.42.fr>                +#+  +:+       +#+         #
# #                                                 +#+#+#+#+#+   +#+            #
# #    Created: 2022/07/02 16:49:26 by lseiller          #+#    #+#              #
# #    Updated: 2022/07/27 12:55:40 by vchan            ###   ########.fr        #
# #                                                                              #
# # **************************************************************************** #

# # COLORS/FORMAT #
# _END		=	\e[0m
# _BOLD		=	\e[1m
# _RESET		=	\033[2K
# _GREY		=	\e[30m
# _RED		=	\e[31m
# _GREEN		=	\e[32m
# _YELLOW		=	\e[33m
# _BLUE		=	\e[34m

# # FLAGS #
# MAKEFLAGS	+=	--silent
# #CC_FLAGS	=	-Wall -Wextra -Werror -pthread
# # CC_FLAGS	=	-g3 -pthread
# CC_FLAGS	=	-g3 -pthread -fsanitize=thread

# # FILES #
# DIR 		=	./
# DIR_OBJS	=	./objs/

# SRCS		=	srcs/main.c \
# 				srcs/time.c \
# 				srcs/init.c \
# 				srcs/lock_unlock.c \
# 				srcs/rotine.c \
# 				srcs/utils.c


# # CMDS #
# RM			=	rm -rf
# ECHO		= echo -n

# # COMPILED_SOURCES #
# OBJS		=	$(SRCS:%.c=$(DIR_OBJS)%.o)
# NAME		=	philo

# # **************************************************************************** #

# all:			$(NAME)

# $(NAME):		$(OBJS)
# 				$(ECHO) "$(_RESET)\r$(_GREEN) All files compiled into '$(DIR_OBJS)'. $(_END)\n"
# 				$(CC) $(CC_FLAGS) $(OBJS) -o $(NAME)
# 				$(ECHO) "$(_RESET)\r$(_GREEN) Program '$(NAME)' created. $(_END)\n"

# $(OBJS):		| $(DIR_OBJS)

# $(DIR_OBJS)%.o:	$(DIR)%.c
# 				$(ECHO) "$(_RESET)\r$(_BLUE)Compiling $<$(_END)"
# 				$(CC) $(CC_FLAGS) -c $< -o $@

# $(DIR_OBJS):
# 				mkdir $(DIR_OBJS)

# # bonus:

# clean:
# 				$(RM) $(DIR_OBJS)
# 				$(ECHO) "$(_RESET)\r$(_RED) '$(DIR_OBJS)' has been deleted. $(_END)\n"

# fclean:			clean
# 				$(RM) $(NAME)
# 				$(ECHO) "$(_RESET)\r$(_RED) '$(NAME)' has been deleted. $(_END)\n"

# re:				fclean all

# .PHONY:		all clean fclean re philo bonus


# -----------------------------------------------------------------------------


################################################################################
#                                     CONFIG                                   #
################################################################################
# MAKEFLAGS += 	--silent
NAME		=	philo
NAME_BONUS	=	bonus
RM			=	rm -f
CC			=	clang
CFLAGS		=	-g3 -pthread -fsanitize=thread

# COLORS/FORMAT #
_END		=	\e[0m
_BOLD		=	\e[1m
_RESET		=	\033[2K
_GREY		=	\e[30m
_RED		=	\e[31m
_GREEN		=	\e[32m
_YELLOW		=	\e[33m
_BLUE		=	\e[34m

################################################################################
#                          PROGRAM'S SRCS / OBJS                               #
################################################################################

SRCS		=	srcs/time.c \
				srcs/init.c \
				srcs/lock_unlock.c \
				srcs/routine.c \
				srcs/utils.c

OBJS		= 	$(SRCS:.c=.o)

SRC_PHILO	=	srcs/main.c
OBJS_PHILO=	$(SRC_PHILO:.c=.o)

INCLUDE		= -I ./include

all: $(NAME)

%.o:			%.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

################################################################################
#                                 Makefile rules                               #
################################################################################


$(NAME):	$(OBJS) $(OBJS_PHILO)
	$(CC) $(CFLAGS) -o $@ $^ || $(MAKE) $@

clean	:
	@$(RM) $(OBJS) $(OBJS_SO_LONG);

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all

.PHONY: all clean fclean re
