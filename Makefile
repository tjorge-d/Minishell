NAME= minishell

CC= cc
CFLAGS= -g -Wall -Werror -Wextra

SRC_BI= $(addprefix sources/Built_ins/, $(SOURCES_BUILT_IN))
SRC_EX= $(addprefix sources/Executor/, $(SOURCES_EXECUTOR))
SRC_PA= $(addprefix sources/Parser/, $(SOURCES_PARSER))

SOURCES_BUILT_IN=	built_in_exp.c 				\
					unset.c						\
					echo.c 						\
					pwd.c						\
					cd_built_in.c				\
					env.c						\
					exit.c						\

SOURCES_EXECUTOR=	utils_update.c				\
					get_data_path.c				\
					free_utils.c				\
					signals.c					\
					exec.c						\
					exec_utils.c				\
					exec_utils2.c				\
					exec_utils3.c				\
					run_errors.c				\

SOURCES_PARSER=		parser.c					\
					parser_utils.c				\
					expander.c					\
					expander_utils.c			\
					tokenizer.c					\
					tokenizer_utils.c			\
					here_doc.c					\
					tree_constructor.c			\
					tree_constructor_utils.c	\
		

OBJ_DIR= objects
OBJ_BI=	$(addprefix $(OBJ_DIR)/, $(SRC_BI:sources/Built_ins/%.c=%.o))
OBJ_EX=	$(addprefix $(OBJ_DIR)/, $(SRC_EX:sources/Executor/%.c=%.o))
OBJ_PA= $(addprefix $(OBJ_DIR)/, $(SRC_PA:sources/Parser/%.c=%.o))


LIBFT_DIR= ./libft
LIBFT= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ_PA) $(OBJ_BI) $(OBJ_EX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_PA) $(OBJ_BI) $(OBJ_EX) -lreadline -o $@ $(LIBFT)

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