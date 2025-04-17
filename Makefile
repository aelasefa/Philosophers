.PHONY: all clean fclean re

all:
	$(MAKE) -C philo

clean:
	$(MAKE) -C philo clean

fclean:
	$(MAKE) -C philo fclean

re:
	$(MAKE) -C philo re
