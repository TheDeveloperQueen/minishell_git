/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:38:25 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/03 14:35:29 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_delimiter(char *delimiter, char *str)
{
	if (ft_strcmp(delimiter, str) == 0
		&& ft_strlen(delimiter) == ft_strlen(str))
		return (1);
	return (0);
}

void	ft_heredoc(t_io_node *io, int p[2])
{
	char	*line;

	//signal(SIGINT, ft_heredoc_sigint_handler);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_is_delimiter(io->io_arg, line))
			break ;
		if (!ft_strlen(line))
		{
			free(line);
			continue ;
		}
		ft_putstr_fd(line, p[1]);
		ft_putstr_fd("\n", p[1]);
		free(line);
	}
	free(line);
	//ft_clean_ms();
	exit(0);
}

int	rx_heredocs(t_io_node *io_list)
{
	int	p[2];
	pid_t	pid;
	int	child_status;

	while (io_list)
	{
		if (io_list->io_type == IO_HEREDOC)
		{
			pipe(p);
			//g_minishell.signint_child = true;
			//pid = (signal(SIGQUIT, SIG_IGN), fork());
			pid = fork();
			if (!pid)
				ft_heredoc(io_list, p);
			waitpid(pid, &child_status, 0);
			close(p[1]);
			if (WIFEXITED(child_status) && WEXITSTATUS(child_status) != 0)
				return (1);
			io_list->fd = p[0];
		}
		io_list = io_list->next;
	}
	return (0);
}

int	process_heredocs(t_commands_array *cmds)
{
	int			i;
	t_command	**cmd_array;
	int			error;

	i = 0;
	error = 0;
	cmd_array = cmds->comm_array;
	while (i < cmds->len && !error)
	{
		error = rx_heredocs(cmd_array[i]->infiles);
		i++;
	}
	return (error);
}
