# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hugothms <hugothms@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/04 09:45:09 by hugothms          #+#    #+#              #
#    Updated: 2020/05/04 12:49:04 by hugothms         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
--MAKE = make
--CC = gcc
--CFLAGS += -Wall -Werror -Wextra
--LDFLAGS += #-g3 -fsanitize=address
--OPTI = -Ofast -flto -march=native #-O3

--SRCS =	srcs/error.c			\
			srcs/color.c			\
			srcs/get_next_line.c	\
			srcs/main.c 			\
			srcs/parse.c 			\
			srcs/save_bmp.c			\
			srcs/utils.c 			\
			srcs/set_elements.c		\
			srcs/main.c 			
			

--OBJS = $(--SRCS:.c=.o)
--OBJSLIBFT =$(--LIBFTDIR)*.o

--INCL = includes/
--HEADER = $(--INCL)minirt.h

--LIBFT = libft.a
--LIBFTDIR = libft/
--LIBFTLINK = -L $(--LIBFTDIR) -lft

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBMLXDIR	= libmlxlinux
	MLX_INCLUDE = -lm -lXext -lX11
	ENV			= -D LINUX
else
	LIBMLXDIR	= libmlx
	MLX_INCLUDE = -framework OpenGL -framework AppKit
	ENV			=
endif
--LIBMLX = libmlx.a
--LIBMLXLINK = -L $(LIBMLXDIR) -lmlx







all : compilelibft compilelibmlx $(NAME)

$(NAME) : $(--OBJSLIBFT) $(--OBJS)
	$(--CC) $(--OPTI) $(--LDFLAGS) -o $@ $^ $(--LIBFTLINK) $(--LIBMLXLINK) $(MLX_INCLUDE) $(ENV)

compilelibft :
	$(--MAKE) -C libft all

compilelibmlx :
	$(--MAKE) -C $(LIBMLXDIR) all

%.o: %.c $(--INCL)
	$(--CC) -c $(--LDFLAGS) -I$(--INCL) -o $@ $<

clean:
	#echo "$(REDL_FG)Deleting .o$(CLEAR_COLOR)"
	cd $(--LIBFTDIR) && $(--MAKE) clean
	# cd $(LIBMLXDIR) && $(--MAKE) clean
	rm -rf $(--OBJS) $(--LIBFT) $(--LIBMLX)

fclean:		clean
	#echo "$(RED_FG)Deleting exe$(CLEAR_COLOR)"
	cd $(--LIBFTDIR) && $(--MAKE) fclean
	# cd $(LIBMLXDIR) && $(--MAKE) fclean
	rm -f $(NAME) a.out

re:		fclean all


.PHONY: clean fclean




###########################
--BLACK_FG =	\033[38;5;0m
--RED_FG =	\033[38;5;196m
--REDL_FG =	\033[1;31m
--GREEN_FG =	\033[38;5;46m
--CYAN_FG =	\033[0;36m
--YELLOW_FG =	\033[1;33m

--BLACK_BG =	\033[48;5;0m
--BLUE_BG =	\033[48;5;39m
--PINK_BG =	\033[48;5;213m
--YELLOW_BG =	\033[48;5;11m
--RANLIB_BG =	\033[48;5;172m
--GREEN_BG =	\033[48;5;46m

--CLEAR_COLOR =	\033[m
###########################


test: $(NAME)
	./$< scenes/test.cub

test_save: $(NAME)
	./$< scenes/test.cub -save



# gcc -g3 -fsanitize=address -lmlx -framework OpenGL -framework AppKit srcs/*.c -Iincludes libft/libft.a && ./a.out example.rt -save
#"sudo apt-get update" "sudo apt install gdb" "sudo apt install gcc"
#https://stackoverflow.com/c/42network/questions/950/954#954
#.SILENT:

