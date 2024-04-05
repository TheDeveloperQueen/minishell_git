/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:06:40 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/05 21:02:56 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	*create_blank_data(void)
{
	t_data	*new_data;

	new_data = malloc(sizeof(t_data));
	if (!new_data)
		return (NULL);
	new_data->shell_name = SHELL_NAME;
	new_data->envp = NULL;
	new_data->input = NULL;
	new_data->stdin = do_dup(0);
	new_data->stdout = do_dup(1);
	return (new_data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = create_blank_data();
	if (envp[0] == NULL)
		get_envp_3(data);
	else
		get_envp(data, envp);
	read_shell(data);
	return (0);
}
