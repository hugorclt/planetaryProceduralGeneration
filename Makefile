.DEFAULT_GOAL := all

NAME        = phyzical
SRC_DIR     = srcs
OBJS_DIR    = .objs

# Source and object files
CPP_SRCS      = $(shell find $(SRC_DIR) -name '*.cpp')
C_SRCS    = $(shell find $(SRC_DIR) -name '*.c')
OBJS        = $(patsubst $(SRC_DIR)/%.cpp, $(OBJS_DIR)/%.o, $(CPP_SRCS)) \
              $(patsubst $(SRC_DIR)/%.c, $(OBJS_DIR)/%.o, $(C_SRCS))

# Include directories
INCL        = $(addprefix -I, $(shell find $(SRC_DIR) -type d))

# Tools
CCX          = g++
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g3
OPENGL_LIBS = -lglfw -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl

# Build objects
build_objects: $(OBJS)

# Compile Cpp source files
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.cpp
	@printf "\033[0;33mCompiling Cpp object... %-38.38s \r" $@
	@mkdir -p $(dir $@)
	$(CCX) $(CFLAGS) -std=c++20 -c $< -o $@ -MMD $(INCL)

# Compile C source files
$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "\033[0;33mCompiling C object... %-38.38s \r" $@
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCL)

# Link kernel
$(NAME): build_objects
	@echo "\033[0;32m\nLinking... $(NAME)\033[0m"
	$(CCX) $(CFLAGS) -std=c++20 $(OBJS) -o $(NAME) $(OPENGL_LIBS)
	@echo "\033[1;32mKfs: compiled and assembled! :)) \033[0m"

# Default target
all: $(NAME)

# Clean object files
clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJS_DIR)
	@echo "\033[1;31mObjects cleaned!\033[0m"

# Full clean (including the final program)
fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;31mProgram cleaned!\033[0m"
	@echo "\033[1;31mIso cleaned!\033[0m"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re 
