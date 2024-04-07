/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:09:56 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/07 15:32:47 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "token.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <dirent.h>

# define SHELL_NAME "🔥ourHell"

typedef struct s_io_node
{
	char				*io_arg;
	t_io_type			io_type;
	int					fd;
	struct s_io_node	*next;
}						t_io_node;

// Data for each command
typedef struct s_command
{
	t_list			*name_and_args;
	t_list			*args;
	char			**name_and_args_splt;
	char			*name;
	t_io_node		*infiles;
	t_io_node		*outfiles;
}					t_command;

typedef struct s_commands_array
{
	t_command	**comm_array;
	int			len;
}				t_commands_array;

typedef struct s_data
{
	char	*shell_name;
	t_llist	*envp;
	int		status;	
	pid_t	last_pid;
	int		exit_value;
	char	*input;
	int		stdin;
	int		stdout;
}			t_data;

// Command functions
t_commands_array	*parse_commands_array(t_token_node *token_list);
t_commands_array	*get_commands(char *line, t_data *data, int *missing_quote);
int					is_builtin(t_command *cmd);
t_command			*create_blank_command(void);
char				*expand_env_vars(char *word, t_data *data);
int					expand_tokens(t_token_node *tkn_lst, t_data *data);
int					set_name_and_args_fields(t_commands_array *comds);

//path functions
char				*paths(t_data *data, t_command *cmd);

//Envp functions
void				get_envp(t_data *data, char **envp);
void				print_env(t_data *data, char *print1, char *print2);
int					valid_name(char *str, t_data *data);
char				*name_env(t_list *lst);
char				**array_env(t_llist *envp);
int					check_dup_env(t_data *data, char *name);
void				update_envp_value(t_data *data, char *argument);
void				replace_env(t_data *data, char *name, char *n_value);
char				*search_env(t_data *data, char *name);
char				*check_envp(t_data *data, char *name, char *value);
char				**envp_3_var(void);
void				get_envp_3(t_data *data);

//Builtin functions
int					ft_echo(t_command *cmd);
int					ft_pwd(t_command *cmd);
int					ft_export(t_command *cmd, t_data *data);
int					ft_cd(t_data *data, t_command *cmd);
int					ft_env(t_data *data);
int					ft_exit(t_command *cmd, t_data *data);
int					ft_unset(t_command *cmd, t_data *data);

//execute
int					exec_builtin(t_command *cmd, t_data *data);
int					ft_exec_simple_cmd(t_data *data, t_command *cmd,
						int piped, t_commands_array *cmds);
int					ft_exec_cmds(t_data *data, t_commands_array *cmds,
						int index, int piped);
void				read_shell(t_data *data);

//Manage files
t_io_node			*ft_new_io(char *io_arg, t_io_type type);
void				ft_clear_io_lst(t_io_node **lst);
void				ft_add_io(t_io_node **lst, t_io_node *new);
int					open_file(char *file, int mode, int flag);
int					do_dup(int fd);
int					do_dup2(int fd1, int fd2, t_data *data,
						t_commands_array *cmds);
int					process_heredocs(t_commands_array *cmds, t_data *data);
int					ft_out(t_io_node *io_list, t_data *data,
						t_commands_array *cmds, int flag);
int					ft_in(t_io_node *io_list, t_data *data,
						t_commands_array *cmds, int flag);
int					ft_append(t_io_node *io_list, t_data *data,
						t_commands_array *cmds, int flag);
int					process_io(t_command *cmd, t_data *data,
						t_commands_array *cmds, int flag);

//free functions
void				free_array(char **argv);
void				free_data(t_data *data);
void				free_command(t_command *com);
void				free_commands_array(t_commands_array *commands);
void				clear_shell(t_data *data, t_commands_array *commands);

#endif