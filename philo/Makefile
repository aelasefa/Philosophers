NAME := philo

SRCS := philo.c philo_utils.c init.c \
		parse.c philo_routine.c  monitor.c \
		lock_forks.c actions.c

OBJS := $(SRCS:.c=.o)
CC = cc -g3
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY 	: clean
