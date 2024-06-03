NAME= minishell

CC= cc
CFLAGS= -g -Wall -Werror -Wextra

SRC_BI= $(addprefix sources/built_ins/, $(SOURCES_BUILT_IN))
SOURCES_BUILT_IN=	cd_built_in.c				\
					exp_built_in.c 				\
					unset_built_in.c			\
					echo_built_in.c 			\
					pwd_built_in.c				\
					env_built_in.c				\
					exit_built_in.c						

SRC_EX= $(addprefix sources/executor/, $(SOURCES_EXECUTOR))
SOURCES_EXECUTOR=	commands.c					\
					executor.c					\
					free_utils.c				\
					global_utils.c				\
					main.c						\
					redirections.c				\
					run_errors.c				\
					run_utils.c					\
					signals.c

SRC_PA= $(addprefix sources/parser/, $(SOURCES_PARSER))
SOURCES_PARSER=		expander_utils.c			\
					expander.c					\
					get_data_path.c				\
					here_doc.c					\
					parser_utils.c				\
					parser.c					\
					tokenizer_utils.c			\
					tokenizer.c					\
					tree_constructor_utils.c	\
					tree_constructor.c
		
OBJ_DIR= objects
OBJ=	$(addprefix $(OBJ_DIR)/, $(SRC_BI:sources/built_ins/%.c=%.o)) \
		$(addprefix $(OBJ_DIR)/, $(SRC_EX:sources/executor/%.c=%.o)) \
		$(addprefix $(OBJ_DIR)/, $(SRC_PA:sources/parser/%.c=%.o))

LIBFT_DIR= ./libft
LIBFT= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $@ $(LIBFT)

$(OBJ_DIR)/%.o: sources/built_ins/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: sources/executor/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: sources/parser/%.c
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