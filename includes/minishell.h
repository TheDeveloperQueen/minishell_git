/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:09:56 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/25 12:23:20 by rivasque         ###   ########.fr       */
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
# include	<dirent.h>

// files
# define IN 1
# define OUT 2
//Pipes
# define READ 0
# define WRITE 1
# define NO_PIPE 0
# define PIPE_IN 1
# define PIPE_OUT 2
# define PIPE_IN_OUT 3

typedef struct s_io_node
{
	char				*io_arg;
	t_io_type			io_type;
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
	//Has here_doc
	int		heredoc;
	int		status;	
	//return value (last command)
	pid_t	last_pid;
	int		exit_value;
	// User input
	char	*input;
}			t_data;


// Init
t_data	*init_data();

// Command functions
int		is_builtin(t_command *cmd);
void	get_args(t_command *cmd);
//char	**get_array_cmds(t_command *cmd);

//path functions
int		has_path(t_command *cmd);
char	*paths(t_data *data, t_command *cmd);

//Envp functions
void    get_envp(t_data *data, char **envp);
void	print_env(t_data *data, char *print1, char *print2);
int		valid_name(char *str);
char	**array_env(t_data *data, char *delimiter);
int		check_dup_env(t_data *data, char *name);
void	update_envp_value(t_data *data, char *argument);
void	*replace_env(t_data *data, char *name, char *n_value);
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
void	do_cmd(t_command *cmd, t_commands_array *cmds_array, t_data *data, int index);
void    exec_cmd_lst(t_data *data, t_commands_array *cmds_array);
void	child_process(t_data *data, t_command *cmd);
void    full_execute(t_data *data, t_command *cmd);
void	parent_process(t_data *data);
void	read_shell(t_data *data);

//Manage files
int		close_file(int fd);
int		open_file(char *file, int mode);
void		get_fd_in(t_command *cmd);
void		get_fd_out(t_command *cmd);
int		do_dup(int fd);
int		do_dup2(int fd1, int fd2);
void	check_pipe(t_command *cmd, t_commands_array *cmds_array, int index);
int		set_pipes(t_command *cmd);
int		set_files(t_command *cmd);
char	*here_doc(char *delimiter);
int		has_here_doc(t_command *cmd, t_data *data);

//free functions
void	free_array(char **argv);
void	free_data(t_data *data);
void	free_cmd(t_command *cmd);
void	free_cmds_array(t_commands_array *cmds_array);
void	exit_shell(t_data *data, t_command *cmd);

t_io_node			*ft_new_io(char *io_arg, t_io_type type);
void				ft_clear_io_lst(t_io_node **lst);
void				ft_add_io(t_io_node **lst, t_io_node *new);
t_commands_array	*parse_commands_array(t_token_node *token_list);
void				free_command(t_command *com);
void				free_commands_array(t_commands_array *commands);
int					split_comds_args(t_commands_array *comds);
t_commands_array	*get_commands(char *line);

#endif