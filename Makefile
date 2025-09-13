# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlouis <nlouis@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/19 09:35:53 by nlouis            #+#    #+#              #
#    Updated: 2025/03/28 12:21:46 by nlouis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                          SOLONG MAKEFILE 🎮                                  #
# **************************************************************************** #

# Compiler
CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -pthread -I include -I bonus/include -I libft/include -I mlx

# Directories
OBJDIR	:= objs
LIBDIR	:= libft/lib

# Executable
NAME	:= so_long

# Source files
SRC		:= $(shell find srcs -name "*.c")

# Object files
OBJ		:= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

# Libft
LIBFT	:= $(LIBDIR)/libft.a

# Libraries
LDFLAGS := -L libft/lib -lft -L mlx -lmlx -lXext -lX11 -lm

# Colors
GREEN	:= \033[0;32m
CYAN	:= \033[0;36m
YELLOW	:= \033[1;33m
RESET	:= \033[0m

# Default rule
.DEFAULT_GOAL := all

# Build rules
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "$(CYAN)🚀 Built: $@$(RESET)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)🛠️  Compiled:$(RESET) $<"

$(LIBFT):
	@make -C libft

clean:
	@rm -rf $(OBJDIR)
	@make -C libft clean
	@echo "$(YELLOW)🧹 Cleaned object files.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@echo "$(YELLOW)🗑️  Removed binary.$(RESET)"

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                              💡 USAGE GUIDE                                  #
# **************************************************************************** #
# make            → Build so_long and libft 📦
# make clean      → Remove all object files 🧹
# make fclean     → Remove object files and binary 🗑️
# make re         → Clean and rebuild everything 🔁
# **************************************************************************** #
