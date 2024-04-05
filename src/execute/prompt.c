/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:46:35 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/05 13:04:02 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_program(t_data *data)
{
	t_commands_array	*cmds_array;

	cmds_array = get_commands(data->input, data->envp);
	if (!cmds_array)
	{
		clear_shell(data, cmds_array);
		exit(EXIT_FAILURE);
	}
	if (process_heredocs(cmds_array))
	{
		printf("error processing heredocs");
		clear_shell(data, cmds_array);
		exit(EXIT_FAILURE);
	}
	ft_exec_cmds(data, cmds_array, 0, 0);
	free_commands_array(cmds_array);
	free(data->input);
	data->input = NULL;
	data->exit_value = 0;
}

void	read_shell(t_data *data)
{
	//signals();
	while (1)
	{
		data->input = readline("ourShell>");
		//data->input = "ls > out2 | cat out2";
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
