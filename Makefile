NAME = minishell
LDFLAGS = -L libft -lft -lreadline
LIBFT = libft/libft.a

SRC = minishell.c
SRCS = $(addprefix src/, $(SRC))

all: $(NAME)

INCLUDE = include/

CFLAGS = -Wall -Werror -Wextra -g

CYAN = \33[1;36m
RESET = \033[0m
LOG = printf "[$(CYAN)INFO$(RESET)] %s\n"

$(LIBFT):
	@make -C libft --no-print-directory

$(NAME):	$(SRCS) $(INCLUDE) $(LIBFT)
	@$(LOG) "Compiling $@"
	@$(CC) $(SRCS) $(CFLAGS) -I include -I libft $(LDFLAGS) -o $@

leaks:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./$(NAME)

clean:
	@$(RM) -r $(NAME)
	@$(LOG) "Removing $(NAME)"

fclean: clean

re: fclean all

.PHONY: all clean fclean re bonus
