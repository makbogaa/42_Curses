CC = cc
CFLAGS = -Wall -Wextra -Werror -I./minilibx -g -fPIE
LFLAGS = -L./minilibx -lmlx -lX11 -lXext -lGL -lm -pie
MLX = ./minilibx/libmlx.a
LIBFT = ./libft/libft.a
PRINTF = ./printf/libftprintf.a
GNL = ./gnl/gnl.a
SRCS = main.c walk.c map.c map_check.c map_check2.c map_valid_check.c map_xpm_check.c
OBJS = $(SRCS:.c=.o)
NAME = so_long

all: $(MLX) $(LIBFT) $(PRINTF) $(GNL) $(NAME)

$(MLX):
	make -C ./minilibx

$(LIBFT):
	make -C ./libft

$(PRINTF):
	make -C ./printf

$(GNL):
	make -C ./gnl

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) $(MLX) $(LIBFT) $(PRINTF) $(GNL) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	make clean -C ./minilibx || rm -rf ./minilibx/*.o
	make clean -C ./libft
	make clean -C ./printf
	make clean -C ./gnl

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBFT) $(PRINTF) $(GNL)
	make fclean -C ./libft
	make fclean -C ./printf
	make fclean -C ./gnl

re: fclean all

.PHONY: all clean fclean re
