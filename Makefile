NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRC = \
	main.c \
	philo_functions.c \
	utils.c \
	is_number.c \
	starving.c \
	ft_atoi.c \
	clean.c \
	forks.c \
	main_helpers.c

OBJ = \
	obj/main.o \
	obj/philo_functions.o \
	obj/utils.o \
	obj/is_number.o \
	obj/starving.o \
	obj/ft_atoi.o \
	obj/clean.o \
	obj/forks.o \
	obj/main_helpers.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

obj/%.o: src/%.c include/philo.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re