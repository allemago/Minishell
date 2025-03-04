/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 14:18:04 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/26 15:40:56 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "structures.h"
# include <errno.h>
# include <sys/wait.h>

# define NO_EXIT 0
# define IS_EXIT 1
# define PATH_NOT_SET 0
# define PATH_SET 1
# define NOT_LAST 0
# define IS_LAST 1
# define ALL_SPACES " \t\n\v\f\r"
# define ARGC_MSG "minishell: error: try <./minishell>\n"
# define ERR_MEM_MSG "minishell: malloc: cannot allocate memory\n"
# define SYNTAX_TOK "minishell: syntax error near unexpected token `%c'\n"
# define SYNTAX_NWL "minishell: syntax error near unexpected token `newline'\n"
# define EOFMQ_MSG "minishell: unexpected EOF while looking for matching `%c'\n"
# define EOF_MSG "minishell: syntax error: unexpected end of file\n"
# define CMD_NOT_FOUND_MSG "command not found"
# define NO_FILE_MSG "No such file or directory"
# define RED "\001\e[1;91m\002"
# define YELLOW "\001\e[1;93m\002"
# define CYAN "\001\e[1;96m\002"
# define GREEN "\001\e[1;92m\002"
# define MAGENTA "\001\e[1;95m\002"
# define RESET "\001\033[0m\002 "

/* STRUCT INIT */
int		init_new_command(t_command *new_command, char *cmd);
int		init_new_env(t_env *new_env, char *envp);
int		init_new_redir(t_redir *new_redir, char *str);
int		init_single_env(t_parse *parse);
void	init_parse(t_parse *parse);

/* CHECKS & INIT INPUT */
int		setup_input(t_parse *parse);

/* SPLIT COMMANDS */
int		in_quotes(char *str, int *quotes);
int		pass_quotes(char *s, size_t *i);
char	*epur_str(char *str, char *tmp, size_t i, size_t j);
char	**split_command(t_parse *parse, char c);
void	free_tab_size(char ***tab, size_t words);

/* ENV */
int		get_var(t_env *new_env, char *envp);
int		get_value(t_env *new_env, char *envp);
int		join_env(t_env *env, t_env *new_env);
t_env	*find_first_env(t_env *env);
t_env	*find_last_env(t_env *env);
t_env	*new_env(char *envp);
char	**env_to_tab(t_parse *parse, int is_sort);
void	env_list(t_parse *parse, char **envp);

/* COMMAND */
int		command_list(t_parse *parse);
int		command_type(t_parse *parse);
int		get_cmd_name(t_command *command, char *input, size_t i);
int		resolve_path(t_command *cmd, int set_flag);
int		add_path_to_arg(t_command *cmd, char *path);
int		path_not_found(t_command *cmd, char *msg);

/* REDIR */
int		get_file_name(t_redir *redir, char *str);
int		get_redir(t_command *command);
int		in_redir(t_redir *new_redir, char *str);
int		out_redir(t_redir *new_redir, char *str);

/* ARGS */
int		arg_tab(t_command *command);

/* QUOTES & EXPANSION */
int		handle_quotes(t_parse *parse);
char	*expansion(t_parse *parse, char *str, char *tmp, size_t *index);

/* UTILS */
int		find_dollar(char *str);
char	*is_dir(t_command *cmd, char *str, int set_flag);
size_t	find_next_pipe(char *str, char c);
size_t	extract_and_copy(char *str, char *tmp, int *in_q);
size_t	pass_redir_file(char *input);
void	define_is_last_red(t_redir *redir);

#endif