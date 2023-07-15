O = objs/
S = srcs/
P = parser/
X = exec/
L = lexer/
U = utils/

NAME =	minishell

HEADER = include/minishell.h

SRC = $Smain.c \
		$Sexec/exec.c \
		$Slexer/lexer.c \
		$Slexer/token_utils.c \
		$Slexer/token_utils2.c \
		$Slexer/token_utils3.c \
		$Sparser/parser.c \
		$Sparser/parser_utils.c \
		$Sparser/pipes_conformity.c \
		$Sutils/utils.c \
		$Serror/error.c

OBJ = $(SRC:$S%=$O%.o)

CC = gcc
CFLAGS = -g3 -Wall -Wextra -Werror
LIBFLAGS =  libft/libft.a

.PHONY: all libft fclean re

all: libft $(NAME)

$O:
	@mkdir -p $@
	@mkdir -p $@error
	@mkdir -p $@lexer
	@mkdir -p $@parser
	@mkdir -p $@exec
	@mkdir -p $@utils

$(OBJ): | $O

$(OBJ): $O%.o: $S% Makefile $(HEADER) libft/libft.a
	$(CC) $(CFLAGS) -g3 -lreadline -c $< -o $@

libft:
	@make -C libft

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -g3 $^ -lreadline $(LIBFLAGS) -o $@

clean:
	rm -rf $(SRC:$S%=$O%.o)
	rm -rf $(SRC:$S%=$D%.d)
	@make clean -C libft

fclean:	clean
	rm -rf $(NAME)
	@make fclean -C libft

re:	fclean all 
