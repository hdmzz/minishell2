S = src/
O = obj/
D = dep/
LIBFT = libft.a

include settings.mk

OBJ = $(SRCLIBFT:%=$O%.o)
DEP = $(SRCLIBFT:%=$D%.d)
DEPA = $(LIBFT:%=$D%.d)

RM = /bin/rm -rf
RMDIR = /bin/rmdir

.PHONY: all clean fclean re

all: $(NAME)

$O:
	@mkdir $@

$(OBJ): | $O

$(OBJ): $O%.o: % libft.h Makefile settings.mk
	$(CC) $(CFLAGS) -c $< -o $@

$D:
	@mkdir $@

$(DEP): | $D

$(DEP): $D%.d: %
	$(CC) $(CFLAGS) -MM -MF $@ -MT "$O$*.O $@" $<

$(NAME): $(OBJ)
	ar -rcs $@ $^

cleanobj:
	$(RM) $(wildcard $(OBJ))

cleanobjdir: cleanobj
	$(RM) $O

clean: cleanobjdir

fclean: clean
	$(RM) $(NAME)
	$(RM) $D

re: fclean all

-include $(DEP)
