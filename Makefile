NAME= minishell

CC= cc
CFLAGS= -Wall -Werror -Wextra -g

SRC= $(addprefix sources/, $(SOURCES))
SOURCES= parser.c tokenizer.c tokenizer_utils.c

OBJ_DIR= objects
OBJ= $(addprefix $(OBJ_DIR)/, $(SRC:sources/%.c=%.o))

LIBFT_DIR= ./libft
LIBFT= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $@ $(LIBFT)

$(OBJ_DIR)/%.o: sources/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

run: re
	clear && ./minishell

.PHONY: all fclean clean re run
