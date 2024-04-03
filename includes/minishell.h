/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:09:56 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/03 12:24:10 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	"../libft/libft.h"
#include	"token.h"
# include	<stdio.h>
# include	<stdlib.h>
# include	<fcntl.h>
# include	<unistd.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<sys/wait.h>
# include	<dirent.h>

typedef struct s_io_node
{
	char				*io_arg;
	t_io_type			io_type;
	int					fd;
	struct s_io_node	*next;
}						t_io_node;

// Data for each command
typedef struct	s_command
{
	//command name
	char			*name;
	//Comand arguments(not taking into account the command itself)
	char			**args_splitted;
	t_list			*args;
	t_io_node		*infiles;
	int				fd_in;
	t_io_node		*outfiles;
	int				fd_out;
	int				pipe_fd[2];
	int				return_value;
	//type of pipe
	int				pipe;
	char		*name_and_args;
	char		**name_and_args_splt;
}					t_command;

typedef struct s_commands_array
{
	t_command	**comm_array;
	int			len;
}				t_commands_array;

typedef struct s_data
{
	//Environment variables
	t_llist	*envp;
	int		status;	
	//return value (last command)
	pid_t	last_pid;
	int		exit_value;
	// User input
	char	*input;
	int		stdin;
	int		stdout;
}			t_data;

// Command functions
t_commands_array	*parse_commands_array(t_token_node *token_list);
int					split_comds_args(t_commands_array *comds);
t_commands_array	*get_commands(char *line, t_llist *envp);
int		is_builtin(t_command *cmd);
void	get_args(t_command *cmd);
//char	**get_array_cmds(t_command *cmd);

//path functions
char	*paths(t_data *data, t_command *cmd);

//Envp functions
void    get_envp(t_data *data, char **envp);
void	print_env(t_data *data, char *print1, char *print2);
int		valid_name(char *str);
char	**array_env(t_llist *envp, char *delimiter);
int		check_dup_env(t_data *data, char *name);
void	update_envp_value(t_data *data, char *argument);
void	replace_env(t_data *data, char *name, char *n_value);
char    *search_env(t_data *data, char *name);
char	*check_envp(t_data *data, char *name, char *value);

//Builtin functions
int		ft_echo(t_command *cmd);
int		ft_pwd(t_command *cmd);
int		ft_export(t_command *cmd, t_data *data);
int		ft_cd(t_data *data, t_command *cmd);
int		ft_env(t_data *data);
int		ft_exit(t_command *cmd, t_data *data);
int		ft_unset(t_command *cmd, t_data *data);

//execute
int		exec_builtin(t_command *cmd, t_data *data);
int	ft_exec_simple_cmd(t_data *data, t_command *cmd, int piped);
int	ft_exec_cmds(t_data *data, t_commands_array *cmds, int index, int piped);
void	read_shell(t_data *data);

//Manage files
t_io_node			*ft_new_io(char *io_arg, t_io_type type);
void				ft_clear_io_lst(t_io_node **lst);
void				ft_add_io(t_io_node **lst, t_io_node *new);
int		open_file(char *file, int mode);
int		do_dup2(int fd1, int fd2);
int	process_heredocs(t_commands_array *cmds);
int	ft_out(t_io_node *io_list);
int	ft_in(t_io_node *io_list);
int	ft_append(t_io_node *io_list);
int	process_io(t_command *cmd);

//free functions
void	free_array(char **argv);
void	free_data(t_data *data);
void	free_command(t_command *com);
void	free_commands_array(t_commands_array *commands);
void	exit_shell(t_data *data, t_command *cmd);

#endif