NAME = minishell

SRCS =  main.c

OBJS = $(SRCS:.c=.o)

INC = ./include

CFLAGS = -Wall -Wextra -Werror

LIBS =	Libft/libft.a


all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C ./Libft bonus
	@cc $(LDFLAGS) $^ $(LIBS) -o $(NAME)
	@echo "Minishell"

%.o: %.c
	@echo "Compiling $<"
	@cc $(CFLAGS) $(CPPFLAGS) -c $< -o $@ -I$(INC)
	@tput cuu1; tput el

clean :
	@$(MAKE) -C ./Libft fclean
	@rm -rf $(OBJS)
	@echo "Cleaning Complete!"

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re