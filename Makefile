# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hthomas <hthomas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/04 09:45:09 by hthomas           #+#    #+#              #
#    Updated: 2022/03/13 19:08:10 by hthomas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

--MAKE = make
--CC = gcc
--CFLAGS += -Wall -Werror -Wextra
--LDFLAGS +=# -g3 -fsanitize=address
--OPTI = -Ofast -flto -march=native#-O3

--COMMONS =	srcs/check_map.c		\
			srcs/color.c			\
			srcs/error.c			\
			srcs/move.c 			\
			srcs/move2.c 			\
			srcs/parse_map.c 		\
			srcs/parse.c 			\
			srcs/save_bmp.c			\
			srcs/sprite.c			\
			srcs/sprite2.c			\
			srcs/utils.c 			\
			srcs/set_elements.c

--SRCS =	$(--COMMONS)		\
			srcs/dda.c			\
			srcs/draw.c			\
			srcs/key.c 			\
			srcs/main.c 		\
			srcs/make_img.c 	\
			srcs/put_pixel.c 	\
			srcs/utils2.c

--SRCS_BONUS = $(--COMMONS)				\
			srcs_bonus/dda.c			\
			srcs_bonus/draw_minimap.c	\
			srcs_bonus/draw.c			\
			srcs_bonus/key.c 			\
			srcs_bonus/main.c 			\
			srcs_bonus/make_img.c 		\
			srcs_bonus/put_pixel.c 		\
			srcs_bonus/utils2.c

--OBJS = $(--SRCS:.c=.o)
--OBJS_BONUS = $(--SRCS_BONUS:.c=.o)

--INCL = includes/
--HEADER = $(--INCL)cub3d.h

--LIBFT = libft.a
--LIBFTDIR = libft
--LIBFTINCL = includes/
--LIBFTLINK = -L $(--LIBFTDIR)/$(LIBFTINCL) -lft

--UNAME_S := $(shell uname -s)
ifeq ($(--UNAME_S), Linux)
	--LIBMLXDIR	= libmlxlinux
	--MLX_INCLUDE = -lm -lXext -lX11
	ENV			= -D LINUX
else
	--LIBMLXDIR	= ogl
	--MLX_INCLUDE = -framework OpenGL -framework AppKit
	ENV			=
endif
--LIBMLX = libmlx.a
--LIBMLXLINK = -L $(--LIBMLXDIR) -lmlx


###########################ALL
all : $(--LIBFTDIR)/$(--LIBFT) $(--LIBMLXDIR)/$(--LIBMLX) $(NAME)

$(NAME) : $(--OBJS) $(--HEADER) $(--LIBFTDIR)/$(--LIBFT) $(--LIBMLXDIR)/$(--LIBMLX)
	$(--CC) $(--OPTI) $(--LDFLAGS) -o $@ $(--OBJS) $(--LIBFTLINK) $(--LIBMLXLINK) $(--MLX_INCLUDE) $(ENV)

bonus : $(--OBJS_BONUS) $(--HEADER) $(--LIBFTDIR)/$(--LIBFT) $(--LIBMLXDIR)/$(--LIBMLX)
	$(--CC) $(--OPTI) $(--LDFLAGS) -o $(NAME) $(--OBJS_BONUS) $(--LIBFTLINK) $(--LIBMLXLINK) $(--MLX_INCLUDE) $(ENV)

###########################LIBS
$(--LIBFTDIR)/$(--LIBFT) :
	$(--MAKE) -C libft all

$(--LIBMLXDIR)/$(--LIBMLX) :
	$(--MAKE) -C $(--LIBMLXDIR) all

%.o: %.c $(--HEADER)
	$(--CC) -c $(--LDFLAGS) -I $(--INCL) -o $@ $<

###########################CLEAN
clean:
	#echo "$(REDL_FG)Deleting .o$(CLEAR_COLOR)"
	cd $(--LIBFTDIR) && $(--MAKE) clean
	# cd $(--LIBMLXDIR) && $(--MAKE) clean
	rm -rf $(--OBJS) $(--OBJS_BONUS) $(--LIBFT) $(--LIBMLX)

fclean:		clean
	#echo "$(RED_FG)Deleting exe$(CLEAR_COLOR)"
	cd $(--LIBFTDIR) && $(--MAKE) fclean
	cd $(--LIBMLXDIR) && $(--MAKE) clean
	rm -f $(NAME) a.out bonus

re:		fclean all

.PHONY: clean fclean

###########################TEST
test: $(NAME)
	./$< maps/test2.cub

test_bonus: bonus
	./$(NAME) maps/test2.cub

test_save: $(NAME)
	./$< maps/test2.cub --save

#.SILENT:




###########################COLORS
--BLACK_FG =	\033[38;5;0m
--RED_FG =		\033[38;5;196m
--REDL_FG =		\033[1;31m
--GREEN_FG =	\033[38;5;46m
--CYAN_FG =		\033[0;36m
--YELLOW_FG =	\033[1;33m

--BLACK_BG =	\033[48;5;0m
--BLUE_BG =		\033[48;5;39m
--PINK_BG =		\033[48;5;213m
--YELLOW_BG =	\033[48;5;11m
--RANLIB_BG =	\033[48;5;172m
--GREEN_BG =	\033[48;5;46m

--CLEAR_COLOR =	\033[m
###########################
