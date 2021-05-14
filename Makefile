NAME = philo_one

CC = gcc -Wall -Wextra -Werror

SRCS =	$(shell find . -name "*.c")

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) -o $@ -c $^

all: $(NAME)

$(NAME): $(OBJS)
	rm -rf $(NAME)
	$(CC) $(OBJS) -o $(NAME)

debug:
	gcc -g $(SRCS)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
