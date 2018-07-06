# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nperrin <nperrin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:28:32 by fjanoty           #+#    #+#              #
#    Updated: 2017/12/04 12:02:53 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re gdb

# -g -fsanitize=address 
# -Ofast
#  -Wall -Wextra -Werror
export CFLAGS	= -g -Wall -Wextra -Werror
#export CFLAGS	= -O2 -Werror -Wall -Wextra
#export CFLAGS	= -g3 #-Wall -Wextra

#-fsanitize=address
export CC	= gcc

#-g -fsanitize=address

# //////////////// cross platforme
OS	:=	$(shell uname -s)
PROC	:= $(shell uname -p)
# ////////////////

NAME			= rtv1
SRC_DIR			= ./src
LIB_FT			= ./libft
LIB_QUATER		= ./quaternion

ifeq "$(OS)" "Windows_NT"
exit # sorry but not sorry =)
endif
ifeq "$(OS)" "Linux"
LIB_MLX			= ./minilibx
endif
ifeq "$(OS)" "Darwin"
LIB_MLX			= ./minilibx_macos
endif

all:
	make -C $(LIB_MLX)
	make -C $(LIB_FT)
	make -C $(LIB_QUATER)
	make -C $(SRC_DIR)
	

clean:
	make -C $(LIB_FT)  		clean
	make -C $(LIB_QUATER)	clean
	make -C $(SRC_DIR) 		clean

fclean: clean
	make -C $(LIB_FT)		fclean
	make -C $(LIB_QUATER)	fclean
	make -C $(SRC_DIR)		fclean

re: fclean all
