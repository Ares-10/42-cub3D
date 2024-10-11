NAME = cub3d

SRCS =  main.c			\
		graphic.c		\
		utils.c			\
		graphic_init.c	\
		graphic_draw.c	\

SRCS += parsing/check_map_valid.c	\
		parsing/check_valid.c		\
		parsing/parse_map.c			\
		parsing/parse.c				\
		parsing/t_str_func.c		\
		parsing/utils.c				\

SRCS +=	lib/get_next_line/get_next_line.c		\
		lib/get_next_line/get_next_line_utils.c	\

OBJS = $(SRCS:.c=.o)

INC = ./include

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -L./lib/minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit

LIBS =	./lib/libft/libft.a						\
		./lib/minilibx_opengl_20191021/libmlx.a	\


all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C ./lib/libft bonus
	@$(MAKE) -C ./lib/minilibx_opengl_20191021 all
	@cc $(LDFLAGS) $^ $(LIBS) -o $(NAME)
	@echo "Cub3d"

%.o: %.c
	@echo "Compiling $<"
	@cc $(CFLAGS) -c $< -o $@ -I$(INC)
	@tput cuu1; tput el

clean :
	@$(MAKE) -C ./lib/libft fclean
	@$(MAKE) -C ./lib/minilibx_opengl_20191021 clean
	@rm -rf $(OBJS)
	@echo "Cleaning Complete!"

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re