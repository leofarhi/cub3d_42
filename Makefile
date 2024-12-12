# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 15:45:34 by lfarhi            #+#    #+#              #
#    Updated: 2024/12/12 14:33:31 by pfischof         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3d
SRC = srcs/
SRCS = ${SRC}main.c
SRCS += ${SRC}game/game.c
SRCS += ${SRC}engine/engine.c

SRCS += ${SRC}parsing/frees.c
SRCS += ${SRC}parsing/get_cub.c
SRCS += ${SRC}parsing/init_parsing.c
SRCS += ${SRC}parsing/parsing.c
SRCS += ${SRC}parsing/parsing_error.c

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -Qunused-arguments
BONUS_FLAGS = -DBONUS=1
LIBFT_FLAGS = -L ./libft -I ./libft -lft
MLX_FLAGS = -L ./minilibx -I ./minilibx -lmlx -Imlx -lXext -lX11 -lm -lz
MLXE_FLAGS = -L ./mlxe -I ./mlxe -lmlxe
LFLAGS = -I includes ${MLXE_FLAGS} ${MLX_FLAGS} ${LIBFT_FLAGS}

LIBFT = libft/libft.a
MINILIBX = minilibx/libmlx.a
MLXE = mlxe/libmlxe.a

all: ${NAME}

${NAME}: ${MINILIBX} ${LIBFT} ${MLXE} ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LFLAGS} -o ${NAME}

bonus: CFLAGS += ${BONUS_FLAGS}
bonus: ${NAME}

${MINILIBX}:
	@make -C minilibx

${MLXE}:
	@make -C mlxe

${LIBFT}:
	@make -C libft

%.o: %.c
	${CC} ${CFLAGS} ${LFLAGS} -c $< -o ${<:.c=.o}

clean:
	rm -f ${OBJS}
	@make -C minilibx clean
	@make -C libft clean
	@make -C mlxe clean

fclean: clean
	rm -f ${NAME}
	@make -C minilibx clean
	@make -C libft fclean
	@make -C mlxe fclean

re: fclean all

.PHONY: all clean fclean re bonus mlx libft mlxe
