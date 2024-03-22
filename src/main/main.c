/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:06:40 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/03/22 13:38:25 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	*init_data(void)
{
	return ((t_data *) malloc(sizeof(t_data)));
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_data *data;

	data = init_data();
	get_envp(data, envp);
	read_shell(data);
	return (0);
}
