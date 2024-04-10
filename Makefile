NAME= minishell

CC= cc
CFLAGS= -g -Wall -Werror -Wextra

SRC_BI= $(addprefix sources/Built_ins/, $(SOURCES_BUILT_IN))
SOURCES_BUILT_IN=	built_in_exp.c 				\
					unset.c						\
					echo.c 						\
					pwd.c						\
					cd_built_in.c				\
					env.c						\
					exit.c						

SRC_EX= $(addprefix sources/Executor/, $(SOURCES_EXECUTOR))
SOURCES_EXECUTOR=	global_utils.c				\
					free_utils.c				\
					signals.c					\
					executor.c					\
					redirections.c				\
					run_utils.c					\
					commands.c					\
					run_errors.c				

SRC_PA= $(addprefix sources/Parser/, $(SOURCES_PARSER))
SOURCES_PARSER=		parser.c					\
					get_data_path.c				\
					parser_utils.c				\
					expander.c					\
					expander_utils.c			\
					tokenizer.c					\
					tokenizer_utils.c			\
					here_doc.c					\
					tree_constructor.c			\
					tree_constructor_utils.c	
		

OBJ_DIR= objects
OBJ=	$(addprefix $(OBJ_DIR)/, $(SRC_BI:sources/Built_ins/%.c=%.o)) \
		$(addprefix $(OBJ_DIR)/, $(SRC_EX:sources/Executor/%.c=%.o)) \
		$(addprefix $(OBJ_DIR)/, $(SRC_PA:sources/Parser/%.c=%.o))


LIBFT_DIR= ./libft
LIBFT= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $@ $(LIBFT)

$(OBJ_DIR)/%.o: sources/Built_ins/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: sources/Executor/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: sources/Parser/%.c
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