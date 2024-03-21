NAME= minishell

CC= cc
CFLAGS= -g -Wall -Werror -Wextra

SRC= $(addprefix sources/, $(SOURCES))

SOURCES=parser.c \
		tokenizer.c \
		tokenizer_utils.c \
		expander.c \
		expander_utils.c \
		utils.c \
		utils_update.c \
		tree_constructor.c \
		tree_constructor_utils.c \
		signals.c \
		get_data_path.c \
		here_docker.c \
		built_in_exp.c \
		echo.c \
		unset.c \
		pwd.c \
		free_utils.c

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