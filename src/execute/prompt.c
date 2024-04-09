/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:46:35 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/09 11:14:14 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_program(t_data *data)
{
	t_cmd_array	*cmds_array;
	int			missing_quote;
	int			wrong_token;

	missing_quote = 0;
	wrong_token = 0;
	cmds_array = get_commands(data->input, data, &missing_quote, &wrong_token);
	if (!cmds_array)
	{
		if (missing_quote || wrong_token)
		{
			free(data->input);
			data->input = NULL;
			return ;
		}
		clear_shell(data, cmds_array);
		exit(EXIT_FAILURE);
	}
	if (process_heredocs(cmds_array, data))
	{
		printf("error processing heredocs");
		clear_shell(data, cmds_array);
		exit(EXIT_FAILURE);
	}
	data->status = ft_exec_cmds(data, cmds_array, 0, 0);
	free_commands_array(cmds_array);
	free(data->input);
	data->input = NULL;
}

void	read_shell(t_data *data)
{
	//signals();
	while (1)
	{

		data->input = readline(PROMPT);
		//data->input = "ls > out2 | cat out2";
		if (!data->input)
		{
			rl_replace_line("", 0);
			printf("exit\n");
			exit(1);
		}
		if (!ft_strlen(data->input) || only_space(data->input))
		{
			free(data->input);
			data->input = NULL;
			continue ;
		}
		add_history(data->input);
		execute_program(data);
	}
	rl_clear_history();
}
