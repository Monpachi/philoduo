################################################################################
#                                     CONFIG                                   #
################################################################################
# MAKEFLAGS += 	--silent
NAME		=	philo
NAME_BONUS	=	bonus
RM			=	rm -f
CC			=	clang
CFLAGS		=	-g3 -pthread -fsanitize=thread
# CFLAGS		=	-g3 -pthread

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
	@$(RM) $(OBJS) $(OBJS_PHILO);

fclean	:	clean
	$(RM) $(NAME)

re		:	fclean all

.PHONY: all clean fclean re
