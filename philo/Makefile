NAME    = philo
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
LDFLAGS = -pthread
SRCS    = main.c utils.c init.c routine.c monitor.c atoi.c libft.c write.c
OBJ_DIR = obj

OBJS    = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
