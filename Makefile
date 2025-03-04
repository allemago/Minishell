# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/23 14:17:50 by magrabko          #+#    #+#              #
#    Updated: 2025/03/04 10:30:51 by magrabko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=				minishell

CFLAGS= 			-Wall -Wextra -Werror -g3

INCLD=  			-I ./include/

CYAN= 				\033[1;36m
GREEN=				\033[1;32m
RESET= 				\033[0m
NOPRINT=			--no-print-directory

SRC_PATH=			src
SRC_FILES=			main.c 														\

PARS_PATH=			src/parsing
PARS_FILES=			arg_tab.c cmd_list.c cmd_path.c cmd_utils.c env_list.c 		\
					env_utils.c expansion.c parse_input.c quotes.c redir_list.c	\
					split_cmd.c split_utils.c struct_init.c utils_parse.c		\

EXEC_PATH=			src/process
EXEC_FILES=			builtins_utils.c builtins.c env.c exec_input.c exec_pipes.c \
					exec_single.c heredoc.c pipes_init.c redirections.c 		\
					utils_process.c												\

UTILS_PATH=			src/utils
UTILS_FILES=		cleanup.c error_handler.c signals.c utils.c					\

LIBFT_PATH=			libft
LIBFT_FLAGS=		-L$(LIBFT_PATH) -lft
LIBFT=        		$(LIBFT_PATH)/libft.a

SRC=				$(SRC_PATH)/$(SRC_FILES)		\
					$(PARS_PATH)/$(PARS_FILES)		\
					$(EXEC_PATH)/$(EXEC_FILES)		\
					$(UTILS_PATH)/$(UTILS_FILES)	\

OBJ_PATH=			obj
OBJ= 				$(addprefix $(OBJ_PATH)/, $(notdir $(SRC:.c=.o)))

all: $(LIBFT) $(NAME)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)
	
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INCLD) -c $< -o $@

$(OBJ_PATH)/%.o: $(PARS_PATH)/%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INCLD) -c $< -o $@

$(OBJ_PATH)/%.o: $(EXEC_PATH)/%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INCLD) -c $< -o $@

$(OBJ_PATH)/%.o: $(UTILS_PATH)/%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INCLD) -c $< -o $@

$(LIBFT):
	@$(MAKE) $(NOPRINT) -C $(LIBFT_PATH)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) -o $(NAME) -lreadline $(LIBFT_FLAGS)
	@printf "\n\n${CYAN}"
	@printf "   ░█▄█░▀█▀░█▀█░▀█▀░█▀▀░█░█░█▀▀░█░░░█░░\n"
	@printf "   ░█░█░░█░░█░█░░█░░▀▀█░█▀█░█▀▀░█░░░█░░\n"
	@printf "   ░▀░▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░▀░▀░▀▀▀░▀▀▀░▀▀▀\n"
	@printf "\n\n${RESET}"

clean:
	@rm -rf $(OBJ_PATH)
	@$(MAKE) $(NOPRINT) -C $(LIBFT_PATH) clean
	@printf "\n\n${GREEN}"
	@printf "   ░█▀▀░█░░░█▀▀░█▀█░█▀█░█░█░█▀█░░█\n"
	@printf "   ░█░░░█░░░█▀▀░█▀█░█░█░█░█░█▀▀░░▀\n"
	@printf "   ░▀▀▀░▀▀▀░▀▀▀░▀░▀░▀░▀░▀▀▀░▀░░░░▀\n"
	@printf "\n\n${RESET}"

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) $(NOPRINT) -C $(LIBFT_PATH) fclean

re: fclean all

copy_dbg:
		@cp -r ~/Debug/minishell_debug/.vscode .vscode

.PHONY: all clean fclean re copy_dbg rd_supp
