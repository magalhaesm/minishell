# Running make will compile and run all files prefixed with test_.
# For single test, run make with one of the names specified in the
# TESTS variable

TESTS := hash_table

SRC_DIR   := ../src
LIBFT_DIR := ../libft
INC_DIRS  := ../include $(LIBFT_DIR)

# Insert each new directory here
SRC_DIRS := table
SRC_DIRS := $(addprefix $(SRC_DIR)/, $(SRC_DIRS))
SRC_DIRS += $(SRC_DIR)

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

CFLAGS  := -Wall -Werror -Wextra -g $(addprefix -I,$(INC_DIRS))
LDFLAGS := -L $(LIBFT_DIR) -lft -lcriterion

define run
 	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@ && ./$@
 	$(RM) $@
endef

################################################################################
##                                 TESTS                                      ##
################################################################################

all: $(TESTS)

# test name: all source-files used by this test
hash_table: hash_table.c test_hash_table.c
	@$(call run, "$^")
