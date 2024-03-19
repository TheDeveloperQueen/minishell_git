/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:46:35 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/18 18:58:15 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void    execute_program(t_data *data, t_command *cmd, t_commands_array *cmds_array, t_io_node *fd)
{
    exec_cmd_lst(data, cmd, cmds_array, fd);
    if (open("heredoc", F_OK))
        unlink("heredoc");
    free_cmd(cmd);
	free(data);
}

void	read_shell(void)
{
	t_data              *data;
    t_command           *cmd;
    t_commands_array    *cmds_array;
    t_io_node           *fd;   
    
	//signals();
	while (1)
	{
        data->input = readline("ourShell>");
        if (!data->input)
        {
            rl_replace_line("", 0);
            printf("exit\n");
            exit_shell();
        }
		if (!ft_strlen(data->input))
		{
			free(data->input);
			continue ;
		}
		add_history(data->input);
		execute_program(data, cmd, cmds_array, fd);
	}
	rl_clear_history();
}
