################################################################################
##                                MINISHELL                                   ##
################################################################################

NAME  := minishell

CYAN  := \33[1;36m
RESET := \033[0m
LOG   := printf "[$(CYAN)INFO$(RESET)] %s\n"

################################################################################
##                                DIRECTORIES                                 ##
################################################################################

OBJ_DIR   := obj
LIBFT_DIR := libft
INC_DIRS  := include $(LIBFT_DIR)
SRC_DIRS  := table signals builtins scanner parser parser/grammar debug
SRC_DIRS  += helpers exec expansion
SRC_DIRS  := $(addprefix src/, $(SRC_DIRS))
SRC_DIRS  += src

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

LIBFT   := $(LIBFT_DIR)/libft.a
DEBUG   := scanning.c parsing.c

HEADERS := minishell.h hash_table.h builtins.h parser.h parser.h tree.h
HEADERS += helpers.h exec.h expansion.h

SOURCES := minishell.c hash_table.c hash_table_utils.c
SOURCES += sig_setup.c sig_events.c
SOURCES += echo.c pwd.c unset.c builtin_utils.c
SOURCES += scanner.c scanner_utils.c token_word.c parser.c syntax_error.c
SOURCES += tree.c tree_utils.c table.c
SOURCES += rules1.c rules2.c rules3.c rules4.c rules5.c
SOURCES += environ.c environ2.c builtin_pool.c env.c path.c error.c string.c
SOURCES += exec.c exec_cmd.c pcall.c exec_redir.c exec_utils.c exec_pipe.c
SOURCES += exp_utils.c wildcard.c

SOURCES += $(DEBUG)

OBJS := $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

################################################################################
##                                 COMPILATION                                ##
################################################################################

CFLAGS  := -Wall -Werror -Wextra -g $(addprefix -I,$(INC_DIRS))
LDFLAGS := -L $(LIBFT_DIR) -lft -lreadline

all: $(NAME)

test: $(NAME)
	@make -C tests --no-print-directory

$(NAME):	$(OBJS) | $(LIBFT)
	@$(LOG) "Linking objects to $@"
	$(CC) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: %.c $(HEADERS) | $(OBJ_DIR)
	@$(LOG) "Compiling $@"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@$(LOG) "Creating objects directory"
	@mkdir $@

$(LIBFT):
	@make bonus -C $(LIBFT_DIR) --no-print-directory

leaks: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
		--suppressions=readline.supp ./$(NAME)

checks: $(NAME)
	valgrind -q --leak-check=full --show-leak-kinds=all --track-fds=yes \
		--track-origins=yes --trace-children=yes \
		--trace-children-skip='*/bin/*,*/sbin/*' \
		--suppressions=readline.supp ./minishell

clean:
	@$(RM) -r $(OBJS)
	@$(LOG) "Removing objects"
	@$(RM) -r $(OBJ_DIR)
	@$(LOG) "Removing objects directory"

fclean: clean
	@$(RM) -r $(NAME)
	@$(LOG) "Removing $(NAME)"
	@make fclean -C $(LIBFT_DIR) --no-print-directory --silent

re: fclean all

.PHONY: all clean fclean re
