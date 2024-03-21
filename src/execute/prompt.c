/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:46:35 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/21 11:53:40 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void    execute_program(t_data *data)
{

	t_commands_array	*cmds_array;

	cmds_array = get_commands(data->input);
	if (!cmds_array)
		exit(EXIT_FAILURE);
    exec_cmd_lst(data, cmds_array);
    if (open("heredoc", F_OK))
        unlink("heredoc");
    free_commands_array(cmds_array);
	free(data);
}

void	read_shell(void)
{
	t_data *data;

	data = init_data();
	
	//signals();
	while (1)
	{
        //data->input = readline("ourShell>");
		data->input = "cd -";
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
