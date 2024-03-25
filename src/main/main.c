/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:06:40 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/03/25 13:31:06 by rivasque         ###   ########.fr       */
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
	(void)argc;
	(void)argv;
	t_data *data;

	data = create_blank_data();
	get_envp(data, envp);
	read_shell(data);
	return (0);
}
