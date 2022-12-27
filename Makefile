# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seungjoon <seungjoon@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 12:18:03 by seunchoi          #+#    #+#              #
#    Updated: 2022/12/22 15:18:24 by seungjoon        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minirt

INCLUDE = -I./includes -I./mlx
LIBS = -L./mlx -lmlx

SRCS = main.c ray.c vec1.c vec2.c image.c camera.c color.c mlx_utils.c sphere.c hit.c obj_list.c scene.c \
vec3.c light.c plane.c cylinder.c
OBJS = $(SRCS:.c=.o)

.c.o :
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(OBJS)
	$(MAKE) -C./mlx
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) -o $(NAME) $(OBJS) -framework OpenGL -framework Appkit

all : $(NAME)

clean :
	$(MAKE) -C./mlx clean
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re