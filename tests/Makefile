# For single test, run make with one of the names specified in the TESTS variable

TESTS := hash_table signals echo scanner parser environ builtin_pool env wildcard

CYAN  := \33[1;36m
RESET := \033[0m
LOG   := printf "[$(CYAN)INFO$(RESET)] %s\n"

SRC_DIR   := ../src
LIBFT_DIR := ../libft
INC_DIRS  := ../include $(LIBFT_DIR)

# Insert each new directory here
SRC_DIRS := table signals builtins scanner parser parser/grammar helpers expansion
SRC_DIRS := $(addprefix $(SRC_DIR)/, $(SRC_DIRS))
SRC_DIRS += $(SRC_DIR)

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

CFLAGS  := -Wall -Werror -Wextra -g $(addprefix -I,$(INC_DIRS))
LDFLAGS := -L $(LIBFT_DIR) -lft -lcriterion -lreadline

define run
 	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ && ./$@ --verbose
 	make clean --no-print-directory
endef

################################################################################
##                                 TESTS                                      ##
################################################################################

all: $(TESTS)

# test name: all source-files used by this test
hash_table: hash_table.c hash_table_utils.c test_hash_table.c
	@$(call run, "$^")

signals: sig_events.c sig_setup.c test_signals.c
	@$(call run, "$^")

wildcard: exp_utils.c wildcard.c test_wildcard.c
	@$(call run, "$^")

SCANNER := scanner.c scanner_utils.c token_word.c
scanner: $(SCANNER) test_scanner.c
	@$(call run, "$^")

PARSER := parser.c table.c rules1.c rules2.c rules3.c rules4.c rules5.c
PARSER += tree.c tree_utils.c syntax_error.c $(SCANNER)
parser: $(PARSER) test_parser.c
	@$(call run, "$^")

ENVIRON := environ.c environ2.c
environ: $(ENVIRON) test_environ.c
	@$(call run, "$^")

BUILTIN := echo.c
echo: $(BUILTIN) test_echo.c
	@$(call run, "$^")

BUILTIN += env.c
env: $(BUILTIN) $(ENVIRON) builtin_pool.c test_env.c
	@$(call run, "$^")

builtin_pool: $(BUILTIN) $(ENVIRON) builtin_pool.c test_builtin_pool.c
	@$(call run, "$^")

# Makefile rules to clean stdin/stdout/stderr tests' files
clean:
	@$(RM) -r $(TESTS)
	@$(LOG) "Removing objects"

fclean: clean

re: fclean all

.PHONY: all hash_table signals echo clean fclean re
