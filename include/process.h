/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 00:05:15 by magrabko          #+#    #+#             */
/*   Updated: 2025/03/04 10:22:30 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "structures.h"

# define IS_SORT 1
# define EXIT_SIGINT 130
# define EXIT_SIGQUIT 131
# define EXIT_EOF 42
# define EXPORT_MSG "minishell: export: `%s': not a valid identifier\n"
# define NUM_ARG_MSG "minishell: exit: %s: numeric argument required\n"
# define TOO_MANY_ARG_MSG "minishell: exit: too many arguments\n"
# define NO_ARG_MSG "minishell: env: arguments not accepted\n"
# define CD_MSG "minishell: cd: "
# define CD_ARG_MSG "minishell: cd: too many arguments\n"
# define CD_HOME_MSG "minishell: cd: HOME not set\n"
# define CWD_MSG "getcwd: cannot access parent directories: "
# define STDIN_EOF_WARNING "minishell: warning: "
# define STDIN_EOF_MSG "here-document delimited by end-of-file (wanted `"

/* EXEC */
void	exec_input(t_parse *parse);
void	exec_pipeline(t_parse *parse);
void	exec_builtin(t_parse *parse, t_command *cmd);
void	handle_builtin(t_parse *parse, t_command *cmd);
void	execute_builtin_child(t_parse *parse, t_command *cmd);
void	exec_command(t_parse *parse, t_command *command);

/* BUILTINS */
void	ft_echo(t_command *cmd);
void	ft_cd(t_parse *parse, t_command *cmd, t_env *home);
void	ft_pwd(t_parse *parse);
void	ft_export(t_parse *parse, t_command *cmd, size_t i, size_t j);
void	ft_unset(t_parse *parse, t_command *cmd);
void	ft_env(t_parse *parse, t_command *cmd, int is_sort);
void	ft_exit(t_parse *parse, t_command *cmd);

/* FORKS */
void	fork_pipe_processes(t_parse *parse, int **pipes);
void	wait_for_child(t_parse *parse, pid_t pid);
void	wait_for_children(t_parse *parse);

/* PIPES */
void	close_unused_fds(int **pipes, int cmd_nbr);
void	free_int_tab(int **tab);
int		**create_pipes(int cmd_nbr);

/* REDIR */
int		check_heredoc(t_parse *parse);
int		handle_redir(t_command *cmd, int *has_in, int *has_out);
void	handle_builtin_with_redir(t_parse *parse, t_command *cmd);

/* ERROR HANDLER */
void	msg_code_error(t_parse *parse, char *msg, char *arg);
int		is_command_found(t_command *command);

/* UTILS */
size_t	is_var_valid(t_parse *parse, char *var);
void	remove_env_var(t_parse *parse, t_env *ptr);
char	*get_pwd(t_parse *parse);
int		define_exit_status(int status);
int		define_exit_arg(char *arg);
int		is_numeric(char *str);
int		is_n_option(char *str);
int		set_pwd(t_parse *parse, t_env *old_pwd, t_env *pwd, char *str_old_pwd);

#endif
