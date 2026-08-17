
NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRC = actions.c destroy.c init.c main.c monitor.c parse_args.c philo.c start.c utils.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
