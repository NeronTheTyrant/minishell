# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/05 16:05:10 by mlebard           #+#    #+#              #
#    Updated: 2021/12/14 17:50:55 by mlebard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME
NAME			=	libft.a

# DIR
S_DIR		=	srcs/
BIN_DIR		=	bin/
O_DIR		=	bin/obj/

# COLORS
YLW			=	\033[1;33m# Yellow
GRN			=	\033[1;32m# Green
WHT			=	\033[1;37m# White
RED			=	\033[1;31m
BLU			=	\033[1;34m
NC			=	\033[0m# No Color

OW			=	\r\033[1A\033[K# OverWrite previous line
OW2			=	\r\033[2A\033[K# OverWrite previous 2 lines
OW3			=	\r\033[3A\033[K# OverWrite previous 3 lines


# COMPILE
CC			=	clang
CFLAGS		=	-Werror -Wextra -Wall -I./

LIBFT_SRCS	=	ft_atoi.c \
				ft_atof.c \
				ft_swap.c \
				ft_itoa.c \
				ft_itoa_abs.c \
				ft_itoa_base.c \
				ft_uitoa_base.c \
				ft_uitoa_base_ptr.c \
				ft_check_base.c \
				ft_calloc.c \
				ft_realloc.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_islowercase.c \
				ft_isuppercase.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isnumber.c \
				ft_isfloat.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_iswspace.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_ishigher.c \
				ft_islower.c \
				ft_abs.c \
				ft_absd.c \
				ft_pow.c \
				ft_getnbrlen.c \
				ft_getnbrlen_us.c \
				ft_bzero.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_memswap.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				get_next_line.c \
				check_file_extension.c \
				filecheck.c \
				ft_strlen.c \
				ft_isin.c \
				ft_strchr.c \
				ft_strcmp.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strwchr.c \
				ft_split.c \
				ft_splitset.c \
				ft_strdup.c \
				ft_strndup.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_substr.c \
				strfill.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strncpy.c \
				ft_strinsert.c \
				ft_strextract.c \
				ft_strmapi.c \
				ft_strcheck_each.c \
				ft_tabint.c \
				ft_argcheck_each.c \
				ft_argcount.c \
				ft_freeargs.c \
				make_argb.c \
				argb_to_a.c \
				argb_to_r.c \
				argb_to_g.c \
				argb_to_b.c \
				str_to_rgb.c \
				ft_wctomb.c \
				ft_wclen.c \
				ft_wcslen.c \
				ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstadd_back.c \
				ft_lstlast.c \
				ft_lstsize.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c \
				ft_lstsortif.c \
				ft_lstswapone.c \
				ft_putlst.c
SRCS		=	$(addprefix $(S_DIR),$(LIBFT_SRCS))

LIBFT_OBJS	=	$(LIBFT_SRCS:.c=.o)
OBJS		=	$(addprefix $(O_DIR),$(LIBFT_OBJS))

DEPEND		=	libft.h

RM			=	rm -r -f

all			:
			@echo "Building $(NAME):"
			@make --no-print-directory $(NAME)

$(NAME)		:	$(OBJS) $(DEPEND)
			@ar rc $(NAME) $(OBJS)
			@ranlib $(NAME)
			@echo "$(NAME) built successfully!"

$(OBJS)		:	$(O_DIR)%.o: $(S_DIR)%.c
			@echo "Compiling $<"
			@mkdir -p $(@D)
			@$(CC) $(CFLAGS) -c $< -o $@

norm		:
			@echo "$(NAME): Checking norm for all source and header files"
			norminette $(SRCS) $(DEPEND)

clean		:
			@echo "$(NAME): cleaning objs"
			$(RM) $(BIN_DIR)

fclean		:	clean
			@echo "$(NAME): cleaning $(NAME)"
			$(RM) $(NAME)

re			:	fclean all

.PHONY		:	all bonus clean fclean re
