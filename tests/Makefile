# For single test, run make with one of the names specified in the TESTS variable

TESTS := hash_table signals scanner parser environ wildcard string quotes
TESTS += echo env pwd unset cd export exit builtin_pool expand path

CYAN  := \33[1;36m
RESET := \033[0m
LOG   := printf "[$(CYAN)INFO$(RESET)] %s\n"

OBJ_DIR   := ../obj
SRC_DIR   := ../src
LIBFT_DIR := ../libft
INC_DIRS  := ../include $(LIBFT_DIR)

# Insert each new directory here
SRC_DIRS := table signals builtins scanner parser parser/grammar helpers expansion
SRC_DIRS := $(addprefix $(SRC_DIR)/, $(SRC_DIRS))
SRC_DIRS += $(SRC_DIR)

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

SOURCES := hash_table.c hash_table_utils.c
SOURCES += events.c handlers.c error.c
SOURCES += scanner.c scanner_utils.c token_word.c
SOURCES += parser.c table.c rules1.c rules2.c rules3.c rules4.c rules5.c
SOURCES += tree.c tree_utils.c syntax_error.c string.c
SOURCES += environ.c environ2.c error.c string.c string.c path.c
SOURCES += builtin_pool.c echo.c env.c pwd.c unset.c cd.c exit.c export.c
SOURCES += expand.c exp_utils.c string.c quotes.c wildcard.c wildcard_utils.c
SOURCES += exit_utils.c heredoc_utils.c

OBJS := $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

CFLAGS  := -Wall -Werror -Wextra -g $(addprefix -I,$(INC_DIRS))
LDFLAGS := -L $(LIBFT_DIR) -lft -lcriterion -lreadline

define run
 	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ && ./$@ --verbose
endef

################################################################################
##                                 TESTS                                      ##
################################################################################

all: $(TESTS) clean

# test name: $(dependencies) test file
.PHONY: hash_table
hash_table: $(OBJS) test_hash_table.c
	@$(call run, "$^")

.PHONY: signals
signals: $(OBJS) test_signals.c
	@$(call run, "$^")

.PHONY: scanner
scanner: $(OBJS) test_scanner.c
	@$(call run, "$^")

.PHONY: parser
parser: $(OBJS) test_parser.c
	@$(call run, "$^")

.PHONY: environ
environ: $(OBJS) test_environ.c
	@$(call run, "$^")

.PHONY: echo
echo: $(OBJS) test_echo.c
	@$(call run, "$^")

.PHONY: env
env: $(OBJS) test_env.c
	@$(call run, "$^")

.PHONY: pwd
pwd: $(OBJS) test_pwd.c
	@$(call run, "$^")

.PHONY: unset
unset: $(OBJS) test_unset.c
	@$(call run, "$^")

.PHONY: cd
cd: $(OBJS) test_cd.c
	@$(call run, "$^")

.PHONY: exit
exit: $(OBJS) test_exit.c
	@$(call run, "$^")

.PHONY: export
export: $(OBJS) test_export.c
	@$(call run, "$^")

.PHONY: builtin_pool
builtin_pool: $(OBJS) test_builtin_pool.c
	@$(call run, "$^")

.PHONY: string
string: $(OBJS) test_string.c
	@$(call run, "$^")

.PHONY: wildcard
wildcard: $(OBJS) test_wildcard.c
	@$(call run, "$^")

.PHONY: quotes
quotes: $(OBJS) test_quotes.c
	@$(call run, "$^")

.PHONY: expand
expand: $(OBJS) test_expander.c
	@$(call run, "$^")

.PHONY: path
path: $(OBJS) test_path.c
	@$(call run, "$^")

# Makefile rules to clean stdin/stdout/stderr test's files
clean:
	@$(RM) -r $(TESTS)
	@$(LOG) "Removing objects"

fclean: clean

re: fclean all

.PHONY: all clean fclean re
