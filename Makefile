NAME = wolf3d

CC = gcc

SRC = ft_keypress.c  \
		ft_map.c  	\
		ft_calcul.c \
		ft_draw.c 		\
		ft_inits.c 		\
		ft_move.c 		\
		main.c			\
		get_next_line.c

CFLAGS = -Wall -Werror -Wextra -g3 -O3 -I ./includes -I /usr/X11/include

MLXFLAGS = -L/usr/X11/lib -lmlx -lX11 -lXext

all: $(NAME)

$(NAME):
	make -C libft
	$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(SRC) -L libft -lft

clean:
	rm -rf $(OBJ)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all, fclean, clean, re 
