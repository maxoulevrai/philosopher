NAME = philo

RED				= \e[31m
GREEN			= \e[32m
YELLOW			= \e[33m
BLUE			= \e[34m
MAGENTA			= \e[35m
CYAN			= \e[36m
RESET			= \e[m

SRCS_DIR = src/
INC = includes/philo.h
SRCS = main.c \
		$(SRCS_DIR)err.c \
		$(SRCS_DIR)init.c \
		$(SRCS_DIR)parsing.c \
		$(SRCS_DIR)routine.c \
		$(SRCS_DIR)time.c \
		$(SRCS_DIR)utils.c 

OBJS = $(SRCS:%.c=build/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	@echo "$(GREEN)Linking $@$(RESET)"
	@$(CC) $(CFLAGS) -o $@ $^ 
	@echo "$(GREEN)Build complete$(NO_COLOR)"

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