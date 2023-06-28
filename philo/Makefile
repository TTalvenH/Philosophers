# Program name
NAME = philo

# compiler
CC = cc

# compiler flags
CFLAGS = -Wall -Werror -Wextra -MMD -O0
INCLUDE = -I./include
DEBUG_FLAGS = -g -O0 -fsanitize=address

# src files and path for them
VPATH = src:src/routine:src/utils
SRC = main.c philo_thread.c philo_utils.c parse_int.c routine.c pick_forks.c philo_utils2.c

# obj files and path for them
OBJ_DIR = obj
OBJ =$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

#dependencies
DEP =$(OBJ:.o=.d)

# rules
all: $(NAME)

debug: CFLAGS := $(filter-out -O3,$(CFLAGS))
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: 	clean
	rm -rf $(NAME)

re: fclean all 

.PHONY: all debug clean fclean re
-include $(DEP)