# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seungjoon <seungjoon@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 12:18:03 by seunchoi          #+#    #+#              #
#    Updated: 2023/01/05 10:50:41 by seungjoon        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minirt

INCLUDE = -I./includes -I./get_next_line -I./mlx -I./libft
LIBS = -L./mlx -lmlx -L./libft -lft

SRC_DIR = ./srcs/
GNL_DIR = ./get_next_line/

SRC_LIST = main.c \
ray.c \
vec1.c \
vec2.c \
image.c \
camera.c \
color.c \
mlx_utils.c \
sphere.c \
hit.c \
obj_list.c \
scene.c \
vec3.c \
light1.c \
light2.c \
plane.c \
cylinder.c \
utils.c \
init_compo.c \
exit.c \
compo_list.c

GNL_LIST = get_next_line.c \
get_next_line_utils.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_LIST))
OBJS = $(SRCS:.c=.o)

GNL_SRCS = $(addprefix $(GNL_DIR), $(GNL_LIST))
GNL_OBJS = $(GNL_SRCS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(OBJS) $(GNL_OBJS)
	$(MAKE) -C./mlx
	$(MAKE) -C./libft
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -o $(NAME) $(OBJS) $(GNL_OBJS) -framework OpenGL -framework Appkit

all : $(NAME)

clean :
	$(MAKE) -C./mlx clean
	$(MAKE) -C./libft clean
	rm -f $(OBJS) $(GNL_OBJS)

fclean : clean
	$(MAKE) -C./libft fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re