# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nperrin <nperrin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/05 01:32:20 by fjanoty           #+#    #+#              #
#    Updated: 2017/12/06 17:11:50 by fjanoty          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: clean all fclean re


# //////////////// cross platforme
OS	:=	$(shell uname -s)
PROC	:= $(shell uname -p)
# ////////////////


#-fsanitize=address -g3
NAME	=	osc_to_serial
DEPS =  


SRC		= 						\
		main.c					\
		tinyosc.c				\
		ardurino_serial.c		\
		ft_strsplit.c			\
		osc_wrapeur.c			\


OBJ			= $(SRC:.c=.o)


LIB_DIR		= 
LIB_NAME	=  

ifeq "$(OS)" "Linux"
endif
ifeq "$(OS)" "Darwin"
endif


all: $(NAME)

$(NAME): $(OBJ)
ifeq "$(OS)" "Darwin"
		@$(CC) $(CFLAGS) -o $(NAME)  $(LIB_DIR)  $(FRAMEWORK) $(LIB_NAME) $(OBJ)
endif
ifeq "$(OS)" "Linux"
		@$(CC) $(CFLAGS) -o $(NAME)  $(LIB_DIR)  $(FRAMEWORK) $(OBJ) $(LIB_NAME)
endif
#		-L /usr/lib/ -lmlx -lm -lX11 -lXext
#

%.o: %.c $(DEPS)
	@$(CC) $(CFLAGS) -o $@ -c $< -I .

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
