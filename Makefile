NAME := philos

SRCS := philo/philo.c philo/philo_utils.c philo/init.c \
		philo/parse.c philo/philo_routine.c 

OBJS := $(SRCS:.c=.o)
PHILO_DIR = philo
CC = cc 
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY 	: clean
