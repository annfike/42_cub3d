NAME = cub3D

SRCS =	main.c utils.c draw.c map_parse.c map_check.c map_check_walls.c

GNL = gnl/get_next_line.c gnl/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
GNL_OBJS = $(GNL:.c=.o)


CC = cc
CCFLAGS = -Wall -Wextra -Werror 

all: $(NAME)

$(NAME):	$(OBJS) $(GNL_OBJS)
	make -C ./mlx  
	$(CC) $(CCFLAGS) -Lmlx -lmlx -framework OpenGL -framework AppKit $(OBJS) $(GNL_OBJS) -o $(NAME)

debug:	$(OBJS) $(GNL_OBJS)
	make -C ./mlx
	$(CC) $(CCFLAGS) -fsanitize=address -Lmlx -lmlx -framework OpenGL -framework AppKit $(OBJS) $(GNL_OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(GNL_OBJS)

fclean: clean
	make clean -C mlx/
	rm -f $(NAME)


re: fclean all