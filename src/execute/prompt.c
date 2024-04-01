/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:46:35 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/01 11:29:51 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* static void    execute_program(t_data *data)
{
	t_commands_array	*cmds_array;

	cmds_array = get_commands(data->input, data->envp);
	if (!cmds_array)
		exit(EXIT_FAILURE);
	exec_cmd_lst(data, cmds_array);
	if (open("heredoc", F_OK))
		unlink("heredoc");
	free_commands_array(cmds_array);
	data->input = NULL;
	data->heredoc = 0;
	data->exit_value = 0;
} */

static void	execute_program(t_data *data)
{
	t_commands_array	*cmds_array;

	cmds_array = get_commands(data->input, data->envp);
	if (!cmds_array)
		exit(EXIT_FAILURE);
	if (process_heredocs(cmds_array))
		printf("error processing heredocs");
	set_cmds_pipe_types(cmds_array);
	exec_cmd_lst(data, cmds_array);
	// if (open("heredoc", F_OK))
	// 	unlink("heredoc");
	free_commands_array(cmds_array);
	data->input = NULL;
	data->heredoc = 0;
	data->exit_value = 0;
}

void	read_shell(t_data *data)
{
	//signals();
	while (1)
	{
		//data->input = readline("ourShell>");
		data->input = "ls > out2 | cat out2";
		if (!data->input)
		{
			rl_replace_line("", 0);
			printf("exit\n");
			exit(1);
		}
		if (!ft_strlen(data->input))
		{
			free(data->input);
			continue ;
		}
		add_history(data->input);
		execute_program(data);
	}
	rl_clear_history();
}
