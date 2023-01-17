# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seungjoon <seungjoon@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 12:18:03 by seunchoi          #+#    #+#              #
#    Updated: 2023/01/17 14:41:25 by seungjoon        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = miniRT

INCLUDE = -I./includes -I./get_next_line -I./mlx -I./libft
LIBS = -L./mlx -lmlx -L./libft -lft

SRC_DIR = ./srcs/
BONUS_DIR = ./bonus_srcs/
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
exit.c \
compo_list.c \
file1.c \
file2.c \
file3.c

BONUS_LIST = main_bonus.c \
ray_bonus.c \
vec1_bonus.c \
vec2_bonus.c \
image_bonus.c \
camera_bonus.c \
color_bonus.c \
mlx_utils_bonus.c \
sphere_bonus.c \
hit_bonus.c \
obj_list_bonus.c \
scene_bonus.c \
vec3_bonus.c \
light1_bonus.c \
light2_bonus.c \
plane_bonus.c \
cylinder_bonus.c \
utils_bonus.c \
exit_bonus.c \
compo_list_bonus.c \
file1_bonus.c \
file2_bonus.c \
file3_bonus.c

GNL_LIST = get_next_line.c \
get_next_line_utils.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_LIST))
OBJS = $(SRCS:.c=.o)

BONUS_SRCS = $(addprefix $(BONUS_DIR), $(BONUS_LIST))
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

GNL_SRCS = $(addprefix $(GNL_DIR), $(GNL_LIST))
GNL_OBJS = $(GNL_SRCS:.c=.o)

ifdef BO
	OBJ_FILES = $(BONUS_OBJS) $(GNL_OBJS)
else
	OBJ_FILES = $(OBJS) $(GNL_OBJS)
endif

.c.o :
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all :
	rm -f $(BONUS_OBJS)
	make $(NAME)

$(NAME) : $(OBJ_FILES)
	$(MAKE) -C./mlx
	$(MAKE) -C./libft
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -o $(NAME) $(OBJ_FILES) -framework OpenGL -framework Appkit

bonus :
	# rm -f $(OBJS)
	make BO=1 $(NAME)

clean :
	$(MAKE) -C./mlx clean
	$(MAKE) -C./libft clean
	rm -f $(OBJS) $(BONUS_OBJS) $(GNL_OBJS)

fclean : clean
	$(MAKE) -C./libft fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re