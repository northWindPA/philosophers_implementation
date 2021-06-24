// <====> COLORS <====>
NCLR        = \033[0m
BLACK       = \033[0;30m
RED         = \033[0;31m
GREEN       = \033[0;32m
BROWN       = \033[0;33m
BLUE        = \033[0;34m
PURPLE      = \033[0;35m
CYAN        = \033[0;36m
BOLD_GRAY   = \033[0;37m
DARK_GRAY   = \033[1;30m
BOLD_GREEN  = \033[1;31m
BOLD_GREEN  = \033[1;32m
YELLOW      = \033[1;33m
BOLD_BLUE   = \033[1;34m
BOLD_PURPLE = \033[1;35m
BOLD_CYAN   = \033[1;36m
WHITE       = \033[1;37m
// <====> COLORS <====>

NAME = philo

CC = gcc -Wall -Wextra -Werror

SRCS =	$(shell find . -name "*.c")

OBJS = $(SRCS:.c=.o)

.c.o:
	@ $(CC) -o $@ -c $^
	@ echo "$(BLUE)[$^ $(BROWN) ⬅ ...is compiled ✅]$(NCLR)"

all: $(NAME)
	@ echo "$(GREEN)[🎉🀰🀰🀰🀰🀰🀰🀰🀰🀰🀰🀰🀰🀰🀰🀰 SUCCESS 🀰🀰🀰🀰🀰🀰🀰🀰🀰🀰🀰🀰🀰🀰🀰 📣] $(NCLR)"

$(NAME): $(OBJS)
	@ rm -rf $(NAME)
	@ $(CC) $(OBJS) -o $(NAME)

debug:
	$(CC) -g $(SRCS)

clean:
	@ rm -f $(OBJS)
	@ echo "$(BROWN)[🔄 Objects: $(PURPLE)$(OBJS)$(BROWN) have been removed 🗑 ]$(NCLR)"

fclean: clean
	@ rm -f $(NAME)
	@ echo "$(BROWN)[🚮 Binary: $(PURPLE)$(NAME)$(BROWN) has been removed 🗑 ]$(NCLR)"

re: fclean all

.PHONY: all clean fclean re
