/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:47:21 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/10 10:55:27 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_data	*create_blank_data(void)
{
	t_data	*new_data;

	new_data = malloc(sizeof(t_data));
	if (!new_data)
		return (NULL);
	new_data->envp = NULL;
	new_data->input = NULL;
	new_data->stdin = do_dup(0);
	new_data->stdout = do_dup(1);
	new_data->status = 0;
	return (new_data);
}

t_data	*init_mini_shell(char **envp)
{
	t_data	*data;

	data = create_blank_data();
	if (!data)
		return (NULL);
	init_env(envp, data);
	return (data);
}
