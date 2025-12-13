NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -pthread -g #-Werror

SRC = main.c init.c actions.c monitor.c utils.c philosopher.c destroy.c ft_usleep.c
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
