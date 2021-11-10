SRCFOLD		= srcs/

SRCS		=	${SRCFOLD}main.c

OBJS		= ${SRCS:.c=.o}

NAME		= parser_tester

CC			= clang

CFLAGS		= -Wall -Wextra -Werror -g3

IFLAGS		= -Ilibft -Iincludes

LFLAGS		= -Llibft -lft

RM			= rm -f

%.o: %.c
	${CC} ${CFLAGS} ${IFLAGS} -c $< -o ${<:.c=.o}

${NAME}:		 ${OBJS}
	make -C libft
	${CC} ${CFLAGS} ${IFLAGS} ${OBJS} -o ${NAME} ${LFLAGS}

all:			${NAME}

clean:
	${RM} ${OBJS}
	make clean -C libft/

fclean:			clean
	${RM} ${NAME}
	make fclean -C libft/

re:				fclean all

.PHONY:			all clean fclean re bonus

