NAME = cub3d

SRCS =  main.c		\
		grapic.c	\

SRCS +=	get_next_line/get_next_line.c		\
		get_next_line/get_next_line_utils.c	\

OBJS = $(SRCS:.c=.o)

INC = ./include

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -L./minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit

LIBS =	Libft/libft.a						\
		minilibx_opengl_20191021/libmlx.a	\


all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C ./Libft bonus
	@$(MAKE) -C ./minilibx_opengl_20191021 all
	@cc $(LDFLAGS) $^ $(LIBS) -o $(NAME)
	@echo "Cub3d"

%.o: %.c
	@echo "Compiling $<"
	@cc $(CFLAGS) -c $< -o $@ -I$(INC)
	@tput cuu1; tput el

clean :
	@$(MAKE) -C ./Libft fclean
	@$(MAKE) -C ./minilibx_opengl_20191021 clean
	@rm -rf $(OBJS)
	@echo "Cleaning Complete!"

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re