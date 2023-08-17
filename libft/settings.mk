ifndef SETTINGS_MK
 SETTINGS_MK += 1

NAME	= libft.a

SRCLIBFT = ft_atoi.c\
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_printf.c \
	ft_put.c \
	ft_putnb.c \
	ft_isspace.c \
	ft_atoll.c \
	get_next_line.c \
	get_next_line_utils.c \
	ft_isdigitstr.c \
	ft_strspn.c \
	ft_strcmp.c \
	ft_int_overflow.c \
	ft_free_split.c \
	ft_strnlen.c \
	ft_strndup.c \
	ft_vsprintf.c \
	ft_recompose_split.c \
	ft_str_is_alnum.c \
	ft_free_ptr.c

SRC_BONUS	= ft_lstadd_back_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstmap_bonus.c \
			ft_lstnew_bonus.c \
			ft_lstsize_bonus.c

CC = gcc
CFLAGS += -Wall -Wextra -Werror
endif
