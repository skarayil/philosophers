NAME	= philo_bonus
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= main_bonus.c utils_bonus.c init_bonus.c routine_bonus.c monitor_bonus.c atoi_bonus.c libft_bonus.c string_bonus.c child_bonus.c write_bonus.c
OBJ_DIR	= obj_bonus
OBJS	= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re