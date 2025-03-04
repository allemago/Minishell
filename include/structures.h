/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 13:57:47 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/25 16:24:11 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minishell.h"

typedef enum e_builtin_type
{
	CMD_FOUND = 0,
	EXIT_BT = 1,
	ECHO_BT = 2,
	CD_BT = 3,
	PWD_BT = 4,
	EXPORT_BT = 5,
	UNSET_BT = 6,
	ENV_BT = 7,
	CMD_NOT_FOUND = 127,
	NO_CMD = 250
}						t_builtin_type;

typedef enum e_redir_type
{
	IN_RED = 1,
	HEREDOC = 2,
	OUT_RED = 3,
	APPEND = 4
}						t_redir_type;

typedef struct s_env
{
	char				*var;
	char				*value;
	struct s_env		*prev;
	struct s_env		*next;
}						t_env;

typedef struct s_redir
{
	int					type;
	int					is_last;
	char				*file_name;
	char				*heredoc_delim;
	struct s_redir		*prev;
	struct s_redir		*next;
}						t_redir;

typedef struct s_command
{
	char				*input_cmd;
	char				*cmd_name;
	int					cmd_type;
	size_t				arg_nbr;
	char				**arg;
	size_t				redir_nbr;
	t_redir				*redir;
	struct s_command	*prev;
	struct s_command	*next;
}						t_command;

typedef struct s_parse
{
	char				*input;
	char				**commands;
	size_t				cmd_nbr;
	int					exit_code;
	t_command			*command;
	t_env				*env;
	char				**env_tab;
}						t_parse;

#endif