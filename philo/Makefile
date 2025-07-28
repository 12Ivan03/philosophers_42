CC = cc
CFLAGS = -I./include -Wall -Wextra -Werror 
# -g -fsanitize=thread -pthread
CLIB = -c

BUILD_PATH = ./build

SRC_FILES = ./main.c \
			./utils.c \
			./check_argv.c \
			./init_mutex.c \
			./declaration_manager.c \
			./declaration_philosophers.c \
			./create_threads.c \
			./routine.c \
			./routine_helper.c \
			./routine_helper_two.c \
			./grim_onlooker.c \
			./killer_function.c \
			./get_time_of_day.c \
			./printf_error.c \
			./clear_mutex.c \
			./clear_mutex_helper.c \
			./get_info_mutex.c \
			./one_philo.c \


OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_FILES := $(OBJ_FILES:%=$(BUILD_PATH)/%)

NAME = philo

all: $(NAME)

$(BUILD_PATH)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o  $@

%.o: %.c
	$(CC) $(CFLAGS) $(CLIB) $^ -o $@

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)

clean:
	rm -f $(OBJ_FILES)

fclean : clean
	rm -f $(NAME)

re: clean fclean all

.PHONY: clean fclean all
