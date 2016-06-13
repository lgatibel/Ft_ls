# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/11 17:23:28 by lgatibel          #+#    #+#              #
#    Updated: 2016/04/19 15:15:54 by lgatibel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

SRC_NAME = main.c ft_ls_display.c ft_ls_sort.c ft_ls_link.c ft_ls_right.c \
		ft_ls_verif.c ft_ls_stat.c ft_ls_parse.c ft_ls_set.c ft_ls_sort_annexe.c \
		ft_ls_display_annexe.c ft_ls_args.c

OBJ_PATH = ./objs/

SRC_PATH = ./srcs/

OBJ = $(addprefix $(OBJ_PATH),$(SRC_NAME:.c=.o))

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))

CFLAGS = -Wall -Wextra -Werror

INC = -I./includes

LIBFT = ./Libft/libft.a

LIBFT_PATH = ./Libft/

INC_LIBFT = -I./Libft/includes

CC = clang

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_PATH)
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "Create :\n$(NAME)\ndone1!\n"

$(addprefix $(OBJ_PATH),%.o) : $(addprefix $(SRC_PATH),%.c)
	@mkdir -p $(OBJ_PATH) 2> /dev/null
	@$(CC) $(CFLAGS) -c $< $(INC) $(INC_LIBFT) -o $@

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -rf $(OBJ_PATH)
	@echo "Delete :\n$(OBJ)\ndone1!\n"

fclean: clean 
	@rm -rf ./Libft/objs/
	@rm -f $(NAME)
	@echo "Delete :\n$(NAME)\ndone1!\n"

re: fclean all

norme:
	@norminette $(SRC) ./includes/
