# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/27 17:27:08 by mlebard           #+#    #+#              #
#    Updated: 2021/12/17 19:10:57 by acabiac          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME
NAME		=	minishell

# DIR
S_DIR		=	srcs/
I_DIR		=	include/
BIN_DIR		=	bin/
O_DIR		=	bin/obj/
O_DBG_DIR	=	bin/obj/debug/
O_FDBG_DIR	=	bin/obj/fdebug/
LIB_DIR		=	libft/

# COMPILE
CC			=	clang
CFLAGS		=	-Werror -Wextra -Wall -I$(I_DIR) -I$(LIB_DIR)
LDFLAGS		=	-L $(LIB_DIR) -lft -lreadline
DBGFLAGS	=	-g3
FDBGFLAGS	=	-g3 -fsanitize=address
DEPEND		=	$(LIB_DIR)libft.h \

DEPEND		+=	$(addprefix include/, \
				builtin.h \
				core.h \
				env.h \
				error.h \
				exec.h \
				global.h \
				lexer.h \
				parser.h \
				process.h \
				redir.h \
				sig.h \
				signals.h \
				token.h \
				utils.h)

# SRCS
SOURCES		=	testmain.c \
				minishell.c \
				file_utils.c \
				free.c \
				free_no_unlink.c \
				env.c \
				env_utils.c \
				sudoenv.c \
				sudoenv_utils.c \
				wait.c \
				signals.c \
				sig_handlers.c \
				lexer/lexer.c \
				lexer/find_token.c \
				lexer/make_token.c \
				lexer/state_cat.c \
				lexer/token_utils.c \
				parser/parser.c \
				parser/expansion.c \
				parser/format.c \
				parser/make_cmd.c \
				parser/make_plist.c \
				parser/make_redirlist.c \
				exec/exec.c \
				exec/heredoc_init.c \
				exec/heredoc_input.c \
				exec/heredoc_format.c \
				exec/paths.c \
				exec/redir.c \
				exec/pipe.c \
				builtin/cd.c \
				builtin/cd_curpath.c \
				builtin/cd_cdpath.c \
				builtin/echo.c \
				builtin/env.c \
				builtin/exit.c \
				builtin/export.c \
				builtin/export_var.c \
				builtin/pwd.c \
				builtin/unset.c \
				builtin/exec_builtin.c \
				error/error_hub.c
SRCS		=	$(addprefix $(S_DIR),$(SOURCES))

# OBJS
OBJECTS		=	$(SOURCES:.c=.o)
OBJS		=	$(addprefix $(O_DIR),$(OBJECTS))
DBG_OBJS	=	$(addprefix $(O_DBG_DIR),$(OBJECTS))
FDBG_OBJS	=	$(addprefix $(O_FDBG_DIR),$(OBJECTS))

all				:	libft
				@echo "Building $(NAME):"
				@make --no-print-directory $(NAME)

$(NAME)			:	$(OBJS)
				@echo "Linking $(NAME)..."
				@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
				@echo "$(NAME) built successfully!"

$(OBJS)			:	$(O_DIR)%.o: $(S_DIR)%.c $(DEPEND)
				@echo "Compiling $<"
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

debug			:	libft
				@echo "[DEBUG] Building $(NAME):"
				@make --no-print-directory build_debug

build_debug		:	$(DBG_OBJS)
				@echo "[DEBUG] Linking $(NAME)..."
				@$(CC) $(CFLAGS) $(DBGFLAGS) $^ -o $(NAME) $(LDFLAGS)
				@echo "[DEBUG] $(NAME) built successfully!"

$(DBG_OBJS)		:	$(O_DBG_DIR)%.o: $(S_DIR)%.c $(DEPEND)
				@echo "Compiling $<"
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) $(DBGFLAGS) -c $< -o $@

fdebug			:	libft
				@echo "[FULL DEBUG] Building $(NAME):"
				@make --no-print-directory build_fdebug

build_fdebug	:	$(FDBG_OBJS)
				@echo "[FULL DEBUG] Linking $(NAME)..."
				@$(CC) $(CFLAGS) $(FDBGFLAGS) $^ -o $(NAME) $(LDFLAGS)
				@echo "[FULL DEBUG] $(NAME) built successfully!"

$(FDBG_OBJS)	:	$(O_FDBG_DIR)%.o: $(S_DIR)%.c $(DEPEND)
				@echo "Compiling $<"
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) $(FDBGFLAGS) -c $< -o $@

libft			:
				@make --no-print-directory -C $(LIB_DIR)

norm			:
				@echo "$(NAME): Checking norm for all source and header files"
				@norminette $(S_DIR) $(I_DIR) $(LIB_DIR)

clean			:
				@echo "$(NAME): cleaning objs"
				rm -r -f $(BIN_DIR)

fclean			:	clean
				@echo "$(NAME): cleaning binary"
				rm -r -f $(NAME)

allclean		:	fclean
				@make fclean --no-print-directory -C $(LIB_DIR)

re				:	fclean all

.PHONY			:	all debug fdebug libft sanitize norm clean fclean allclean re
