# Program name
NAME = philo

# compiler
CC = cc

# compiler flags
CFLAGS = -Wall -Werror -Wextra -MMD -O3
INCLUDE = -I./include
DEBUG_FLAGS = -g -O0 -fsanitize=address

# src files and path for them
VPATH = src
SRC = main.c philo_thread.c philo_utils.c parse_int.c

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

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@
	
$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: 	clean
	rm -rf $(NAME)

re: fclean all 

.PHONY: all debug clean fclean re
-include $(DEP)