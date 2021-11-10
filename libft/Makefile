SRCS_MEMORY	= ft_calloc.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_itoa.c \
			ft_longtoa_base.c \
			ft_strdup.c \
			ft_strndup.c \
			ft_strmapi.c \
			ft_split.c \
			ft_splitjoin.c \
			ft_tabdup.c \
			ft_add_str_to_tab.c \
			ft_free_tab.c \
			ft_tab_size.c

SRCS_PRINT = ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c

SRCS_TOOLS 	= ft_atoi.c \
			ft_atoi_n.c \
			ft_get_signed_nb_len.c \
			ft_tablen.c \
			ft_check_base.c \
			ft_abs.c \
			ft_strtoll.c

SRCS_LIST	= ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstdup.c \
			ft_lstcontain_data.c \
			ft_lstmap.c

SRCS_DLIST	= ft_dlstnew.c \
			ft_dlstsize.c \
			ft_dlstlast.c \
			ft_dlstfirst.c \
			ft_dlstadd_front.c \
			ft_dlstadd_back.c \
			ft_dlstadd_after.c \
			ft_dlstadd_before.c \
			ft_dlstdelone.c \
			ft_dlstclear.c \
			ft_dlstarg_to_list.c \
			ft_dlstiter.c \
			ft_dlstsplit.c \
			ft_dlstdup.c \
			ft_dlstmap.c

SRCS_STRING	= ft_memmove.c \
			ft_bzero.c \
			ft_strncmp.c \
			ft_strcmp.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_memcmp.c \
			ft_memchr.c \
			ft_strrchr.c \
			ft_strchr.c \
			ft_strchr_charset.c \
			ft_memset.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strnstr.c \
			ft_isspace.c \
			ft_isupper.c \
			ft_islower.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_strchr_index.c \
			ft_strlen.c

SRCS_GNL	= get_next_line.c \
			get_next_line_utils.c

SRCS		= ${SRCS_GNL} ${SRCS_MEMORY} ${SRCS_PRINT} ${SRCS_TOOLS} ${SRCS_LIST} ${SRCS_DLIST} ${SRCS_STRING}

OBJS		= ${SRCS:.c=.o}

NAME		= libft.a

CC			= clang

CFLAGS		= -g3 -Wall -Wextra -Werror -I.

RM			= rm -f

.c.o		= ${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:		${OBJS}
			ar rcs ${NAME} ${OBJS}

all:			${NAME}

clean:
				${RM} ${OBJS}

fclean:			clean
			${RM} ${NAME}

re:				fclean all

.PHONY:			all clean fclean re
