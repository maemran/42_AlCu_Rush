CC = cc
CFLAGS = -Wall -Wextra -g -Werror 
NAME = alum1

SRCS = main.c get_next_line.c get_next_line_utils.c\
	 utils.c linked_list_fun.c ft_atoi.c nim_logic.c check.c

OBJS_DIR = OBJS
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

$(OBJS_DIR)/%.o:%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re