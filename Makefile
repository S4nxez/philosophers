# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dansanc3 <dansanc3@student.42madrid>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/09 22:23:23 by dansanc3          #+#    #+#              #
#    Updated: 2025/08/27 22:29:44 by dansanc3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the executable
NAME = philo

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address -I$(PHILO_DIR)

# Philo.h library path
PHILO_DIR = include/
OBJ_DIR = obj
SRC_DIR = src

# Source files
SRC = main philo_functions utils is_number

# Object files
OBJS = $(addprefix obj/, $(addsuffix .o, $(SRC)))
OBJF = $(OBJ_DIR)/

SRCS = $(addsuffix .c, $(SRC))

# Compilation rule
all: $(OBJF) $(LIBFT) $(NAME)

# Regla para compilar los archivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(PHILO_DIR)/philo.h | $(OBJF)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJF):
		@mkdir -p $(OBJ_DIR)/

# Rule to clean object files
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

# Rule to clean all generated files
fclean: clean
	rm -f $(NAME) fclean

# Rule to recompile the entire project
re: fclean all

# Phony targets
.PHONY: all bonus clean fclean re
