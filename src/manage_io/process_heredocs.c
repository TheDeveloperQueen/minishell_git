/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:38:25 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/11 16:37:30 by acoto-gu         ###   ########.fr       */
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

static void	heredoc_sigint_handler(int signum)
{
	(void)signum;
	exit(SIGINT);
}

void	ft_heredoc(t_io_node *io, int p[2], t_data *data)
{
	char	*line;
	char	*aux_line;

	signal(SIGINT, heredoc_sigint_handler);
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
		aux_line = expand_env_vars(line, data);
		if (!aux_line)
			break ;
		ft_putstr_fd(aux_line, p[1]);
		ft_putstr_fd("\n", p[1]);
		free(line);
		free(aux_line);
	}
	free(line);
	clear_shell(data);
	exit(0);
}

int	rx_heredocs(t_io_node *io_list, t_data *data)
{
	int		p[2];
	pid_t	pid;
	int		child_status;

	while (io_list)
	{
		if (io_list->io_type == IO_HEREDOC)
		{
			pipe(p);
			g_is_child = 1;
			pid = fork();
			if (!pid)
				ft_heredoc(io_list, p, data);
			waitpid(pid, &child_status, 0);
			g_is_child = 0;
			close(p[1]);
			if (WIFEXITED(child_status) && WEXITSTATUS(child_status) == 2)
				return (1);
			io_list->fd = p[0];
		}
		io_list = io_list->next;
	}
	return (0);
}

int	process_heredocs(t_cmd_array *cmds, t_data *data)
{
	int			i;
	t_cmd		**cmd_array;
	int			error;

	i = 0;
	error = 0;
	cmd_array = cmds->array;
	while (i < cmds->len && !error)
	{
		error = rx_heredocs(cmd_array[i]->infiles, data);
		i++;
	}
	return (error);
}
