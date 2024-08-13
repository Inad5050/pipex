# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dangonz3 <dangonz3@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/07 09:09:40 by dangonz3          #+#    #+#              #
#    Updated: 2024/08/13 17:56:55 by dangonz3         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
CC = gcc
CCFLAGS = -Wall -Wextra -Werror

#colors
COLOR_GREEN = \033[0;32m
COLOR_RESET = \033[0m

#sources
SRC_DIR = sources/
SRC_FILES = 
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(SRC:.c=.o)

SRC_BONUS_DIR = sources_bonus/
SRC_BONUS_FILES = 
SRC_BONUS = $(addprefix $(SRC_BONUS_DIR), $(SRC_BONUS_FILES))
OBJ_BONUS = $(SRC_BONUS:.c=.o)

#headers
INCLUDE = -I./includes/

#LIBFT
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
	
#program
all: $(LIBFT_LIB) $(NAME)
	@echo "$(COLOR_GREEN)------------ PROCESS FINISHED ------------ $(COLOR_RESET)"

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME) $(INCLUDE)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR) all -s
	
%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@ $(INCLUDE)
	@echo "$(COLOR_GREEN)------------ MESSAGE: $@ COMPILED ------------ $(COLOR_RESET)"
	
#bonus

bonus: $(LIBFT_LIB) $(NAME_BONUS)
	@echo "$(COLOR_GREEN)------------ PROCESS FINISHED ------------ $(COLOR_RESET)"

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CCFLAGS) $(OBJ_BONUS) $(LIBFT_LIB) -o $(NAME) $(INCLUDE)

#additional

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean -s
	@echo "$(COLOR_GREEN)------------ MESSAGE: CLEANING COMPLETED ------------ $(COLOR_RESET)"
	
fclean: 
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)
	rm -f $(NAME)
	rm -f $(NAME_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean -s
	@echo "$(COLOR_GREEN)------------ MESSAGE: CLEANING COMPLETED ------------ $(COLOR_RESET)"

re: fclean all

rebonus: fclean all bonus

.PHONY:	all clean fclean re
