NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -rf
SRC = 	inorder.c \
		list_control.c \
		queue_control.c \
		stack_control.c \
		ft_memcpy.c \
		ft_strdup.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strncmp.c \
		ft_substr.c \
		ft_strequal.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_split.c \
		is_and_or.c \
		is_op.c \
		is_parenthsis.c \
		is_pipe.c \
		is_quote.c \
		is_redirection.c \
		is_ws.c \
		is_quote.c \
		is_alpha.c \
		is_digit.c \
		is_name.c \
		free_str_array.c \
		ft_putstr_fd.c \
		ft_strchr.c \
		ft_strnstr.c \
		ft_itoa.c \
		ft_atoi.c \
		
		

SRC_PATH = ./src
OBJ_PATH = ./obj

OBJ_NAME = $(SRC:.c=.o)
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

INC = -I ./inc

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@test -d $(OBJ_PATH) || mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

all:
	make $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

re:
	make fclean
	make all

clean:
	$(RM) $(OBJ)
	$(RM) obj

fclean: clean
	$(RM) $(NAME)

.PHONY: all clean fclean re
