##
## EPITECH PROJECT, 2024
## Need4Stek
## File description:
## Makefile
##

CC = gcc
CFLAGS = -W -Wall -Wextra -Wpedantic -Iinclude -lm
EXECNAME = ai

RED = \033[0;31m
GREEN = \033[0;32m
NO_COLOR = \033[0m

SRCS = ./src/main.c \
	   ./src/utils.c \
	   ./src/ai.c \
	   ./src/my_str_to_word_array.c
OBJS = $(SRCS:./src/%.c=./obj/%.o)
OBJDIR = obj

all: $(EXECNAME)

$(EXECNAME): $(OBJS)
	@echo -e "$(GREEN)Linking $(EXECNAME)...$(NO_COLOR)"
	@$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo -e "$(GREEN)Compiling $<...$(NO_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo -e "$(RED)Cleaning up...$(NO_COLOR)"
	@echo "Removing object files..."
	@rm -f $(OBJS)
	@echo "Removing directory: $(OBJDIR)"
	@rm -rf $(OBJDIR)

fclean: clean
	@echo -e "$(RED)Removing executable $(EXECNAME)...$(NO_COLOR)"
	@rm -f $(EXECNAME)

re: fclean all
	@echo -e "$(GREEN)Rebuilding...$(NO_COLOR)"

.PHONY: all clean fclean re
