/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrabko <magrabko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:17:43 by magrabko          #+#    #+#             */
/*   Updated: 2025/02/26 16:04:56 by magrabko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _DEFAULT_SOURCE

# include "../libft/libft.h"
# include "parsing.h"
# include "process.h"
# include "structures.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern int	g_sig;

/* SIGNALS */
void		setup_signals_parent(void);
void		handle_sigint_parent(int sig);
void		setup_dfl_child(void);
void		setup_signals_heredoc(void);
void		handle_sigint_heredoc(int sig);

/* UTILS */
int			search_set(char c, char *set);
size_t		find_char(char *str, char c);
size_t		find_last_char(char *str);
char		find_next_char(char *str);
t_env		*search_var(t_env *env, char *var);

/* CLEANUP & ERROR HANDLER */
void		clean_all(t_parse *parse, int is_exit);
void		free_ptr(void **ptr);
void		free_tab(char ***tab);
void		free_redir_list(t_redir *redir);
void		free_command_list(t_parse *parse);
void		free_env_list(t_env *env);
void		err_exit(char *str);

#endif
