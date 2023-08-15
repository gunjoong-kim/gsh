NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directoris
SRC_DIR = ./src/
BONUS_SRC_DIR = ./src_bonus/
OBJ_DIR = ./obj/
INC_DIR = ./inc/
BONUS_INC_DIR = ./inc_bonus/
LIB_DIR = ./lib/
LIB_INC_DIR = ./lib/inc/
RL_LIB_DIR = ./readline/lib
RL_INC_DIR = ./readline/include

# LIBS
READLINE_LIBS = -lreadline -L$(RL_LIB_DIR)
LIBFT_LIBS = -lft -L$(LIB_DIR)

# FILES
SRC_FILES = minishell.c \
			minishell_util.c \
			cmd.c \
			exec_ast.c \
			pipe.c \
			redirection.c \
			and_or.c \
			error.c \
			heredoc_pipe.c \
			heredoc.c \
			env_util1.c \
			env_util2.c \
			dic.c \
			signal_util.c \
			builtin.c \
			env.c \
			export.c \
			unset.c \
			cd.c \
			pwd.c \
			exit.c \
			echo.c \
			toki.c \
			toki_case.c \
			toki_utils1.c \
			toki_utils2.c \
			toki_expand.c \
			toki_expand_utils.c \
			toki_expand_utils2.c \
			toki_expand_env1.c \
			toki_expand_env2.c \
			toki_expand_env3.c \
			toki_expand_tokenize.c \
			toki_expand_wildcard1.c \
			toki_expand_wildcard2.c \
			toki_expand_wildcard3.c \
			parse_tree.c \
			parse_tree_utils.c \
			parse_tree_case1.c \
			parse_tree_case2.c \
			parse_tree_case_paren.c \
			parse_tree_case_red1.c \
			parse_tree_case_red2.c \
			parse_tree_case_cmd.c \
			parse_tree_case_arg.c \
			wildcard_expander.c \

BONUS_SRC_FILES = $(SRC_FILES:.c=_bonus.c)
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
BONUS_SRCS = $(addprefix $(BONUS_SRC_DIR), $(BONUS_SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
BONUS_OBJS = $(addprefix $(OBJ_DIR), $(BONUS_SRC_FILES:.c=.o))

all: $(NAME)

$(NAME):
	$(MAKE) -C ./lib
	$(MAKE) -C ./readline
	@make make_mandatory

bonus:
	$(MAKE) -C ./lib
	$(MAKE) -C ./readline
	@make make_bonus

make_mandatory: $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(READLINE_LIBS) $(LIBFT_LIBS)
	touch $@

make_bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJS) $(READLINE_LIBS) $(LIBFT_LIBS)
	touch $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< -I$(INC_DIR) -I$(LIB_INC_DIR) -I$(RL_INC_DIR)

$(OBJ_DIR)%.o : $(BONUS_SRC_DIR)%.c
	@test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< -I$(BONUS_INC_DIR) -I$(LIB_INC_DIR) -I$(RL_INC_DIR)

clean:
	$(MAKE) -C ./lib fclean
	$(MAKE) -C ./readline fclean
	rm -rf $(OBJ_DIR)
	rm -rf make_mandatory
	rm -rf make_bonus

fclean: clean
	rm -rf $(NAME)

re:
	make fclean
	make all

.PHONY: $(NAME) all clean fclean re bonus