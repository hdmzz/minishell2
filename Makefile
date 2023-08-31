O = objs/
S = srcs/
P = parser/
X = exec/
L = lexer/
U = utils/
R = redirections/
C = cleanup/
SIG = signal/
B = builtins/

NAME =	minishell

HEADER = include/minishell.h \
			include/pipes.h \
			include/typedef.h

SRC = $Smain.c \
		$Sexec/exec.c \
		$Slexer/lexer.c \
		$Slexer/token_utils.c \
		$Slexer/token_utils2.c \
		$Slexer/token_utils3.c \
		$S$P/parser.c \
		$S$P/parser_utils.c \
		$S$P/pipes_conformity.c \
		$S$P/parser_heredoc.c \
		$S$U/utils.c \
		$Serror/error.c \
		$S$Rright_redirections.c \
		$S$Rleft_redirections.c \
		$S$Rheredoc.c \
		$S$Rredir.c \
		$S$Xexec_heredoc.c \
		$S$Xpipes.c \
		$S$(SIG)handle_signal.c \
		$S$Bexit.c \
		$S$Bpwd_builtins.c \
		$S$Bexport.c\
		$S$Becho.c \
		$S$Benv_builtins.c \
		$S$Bcd_builtins.c \
		$S$Bunset_builtins.c \
		$S$Rredir2.c \
		$S$Bdispatch_builtins.c \
		$S$Ccleanup.c \
		$S$Xpipes_utils.c


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
	@mkdir -p $@$R
	@mkdir -p $@$B
	@mkdir -p $@$(SIG)

$(OBJ): | $O

$(OBJ): $O%.o: $S% Makefile $(HEADER) libft/libft.h libft/libft.a
	$(CC) $(CFLAGS) -lreadline -c $< -o $@ -I ./include

libft:
	@make -C libft

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LIBFLAGS) -o $@ -I ./include -lreadline

clean:
	rm -rf $(SRC:$S%=$O%.o)
	rm -rf $(SRC:$S%=$D%.d)
	@make clean -C libft

fclean:	clean
	rm -rf $(NAME)
	@make fclean -C libft

re:	fclean all 
