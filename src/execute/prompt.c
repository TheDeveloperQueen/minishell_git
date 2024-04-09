/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:46:35 by ritavasques       #+#    #+#             */
/*   Updated: 2024/04/09 12:02:08 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute_program(t_data *data)
{
	int			missing_quote;
	int			wrong_token;

	missing_quote = 0;
	wrong_token = 0;
	data->cmds = get_commands(data->input, data, &missing_quote, &wrong_token);
	if (!data->cmds)
	{
		if (missing_quote || wrong_token)
		{
			free(data->input);
			data->input = NULL;
			return ;
		}
		clear_shell(data);
		exit(EXIT_FAILURE);
	}
	if (process_heredocs(data->cmds, data))
	{
		printf("error processing heredocs");
		clear_shell(data);
		exit(EXIT_FAILURE);
	}
	data->status = ft_exec_cmds(data, 0, 0);
	free_commands_array(data->cmds);
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
