# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/13 15:44:05 by ltrinchi          #+#    #+#              #
#    Updated: 2022/09/22 13:51:34 by mdegraeu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS_WITHOUT_PATH = \
					mlx_utils.c \
					main.c \
					effective.c \
					check_contact.c

OBJS_SRCS_WITHOUT_PATH = $(SRCS_WITHOUT_PATH:.c=.o)

HEADER_WITHOUT_PATH = cube.h

PATH_TO_SRCS = ./srcs/
PATH_TO_OBJS = ./objs/
PATH_TO_HEADER = ./inclds/

SRCS = $(addprefix $(PATH_TO_SRCS), $(SRCS_WITHOUT_PATH))

OBJS_SRCS = $(addprefix $(PATH_TO_OBJS), $(OBJS_SRCS_WITHOUT_PATH))

OBJS = $(OBJS_SRCS)

HEADER = $(addprefix $(PATH_TO_HEADER), $(HEADER_WITHOUT_PATH))

	######### COMMANDS ###########
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
CFLAGS_MLX = -framework OpenGL -framework AppKit
RM = rm -rf
	################################

	######### RESSOURCES ###########

		###### LIBFT ######
PATH_TO_LIBFT = ./libft/
LIBFT_A = $(PATH_TO_LIBFT)libft.a
		#################

		###### MLX ######
PATH_TO_MLX = ./mlib/
LIBMLX_A = $(PATH_TO_MLX)libmlx.a
		#################

	################################

	####### COLORS FOR PRINTF #######
GREEN 		= \033[0;32m
RED			= \033[0;91m
YELLOW      = \033[0;93m
WHITE       = \033[1;49;97m
	#################################


all: rsc $(PATH_TO_OBJS) $(NAME)
	printf "$(GREEN)✅ $(NAME) is up to date$(WHITE) 👏\n"  

rsc:
	make -C $(PATH_TO_LIBFT)
	make -C $(PATH_TO_MLX)

$(PATH_TO_OBJS):
	mkdir -p ./objs/

$(LIBFT_A): rsc

$(LIBMLX_A): rsc

$(OBJS_SRCS):$(PATH_TO_OBJS)%.o	: $(PATH_TO_SRCS)%.c Makefile $(HEADER) $(LIBFT_A) $(LIBMLX_A)
	printf "\033[2K\r$(YELLOW)⏳ Compiling:$(WHITE) $< 🤞\n"
	$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(LIBMLX_A) $(CFLAGS_MLX) -o $(NAME)

git: fclean
	git add *
	git add -u
	git commit

clean:
	make clean -C $(PATH_TO_LIBFT)
	make clean -C $(PATH_TO_MLX)
	$(RM) $(PATH_TO_OBJS)
	printf "$(RED)👌 Files has been deleted in $(PATH_TO_OBJS) ($(NAME))$(WHITE)\n"  
	printf "$(GREEN)✅ Clean 👍$(WHITE)\n"  

fclean: clean
	$(RM) $(LIBFT_A)
	$(RM) $(LIBMLX_A)
	$(RM) $(NAME)
	printf "$(RED)👌 libmlx.a has been deleted$(WHITE)\n"  
	printf "$(RED)👌 libft.a has been deleted$(WHITE)\n"  
	printf "$(RED)👌 $(NAME) has been deleted$(WHITE)\n"  

re: fclean all
.PHONY: all rsc git clean fclean re
.SILENT:
