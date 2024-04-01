/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:06:40 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/01 11:44:24 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*t_data	*init_data(void)
{
	t_data 
	
	((t_data *) malloc(sizeof(t_data)));
	
}*/

t_data	*create_blank_data(void)
{
	t_data	*new_data;

	new_data = malloc(sizeof(t_data));
	if (!new_data)
		return (NULL);
	new_data->envp = NULL;
	new_data->heredoc = 0;
	new_data->input = NULL;
	return (new_data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = create_blank_data();
	get_envp(data, envp);
	data->stdin = dup(0);
	data->stdout = dup(1);
	read_shell(data);
	return (0);
}
