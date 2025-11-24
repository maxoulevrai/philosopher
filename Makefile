NAME = philo

RED				= \e[31m
GREEN			= \e[32m
YELLOW			= \e[33m
BLUE			= \e[34m
MAGENTA			= \e[35m
CYAN			= \e[36m
RESET			= \e[m

SRCS_DIR = src/
INC = includes/pipex.h
SRCS = $(SRCS_DIR)pipex.c \

OBJS = $(SRCS:%.c=build/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	@echo "$(GREEN)Linking $@$(NO_COLOR)"
	@$(CC) $(CFLAGS) -o $@ $^ 
	@echo "$(GREEN)Build complete$(NO_COLOR)"

$(OBJS) $(INC) | build

$(OBJS): | build


build:
	@mkdir -p build

build/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<$(NO_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files$(NO_COLOR)"
	@rm -rf build

fclean: clean
	@echo "$(RED)Cleaning executable$(NO_COLOR)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 