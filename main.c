/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:06:40 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/03/19 15:20:48 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int g_fail_after = 0;
int g_num_allocs = 0;

int	main(int argc, char *argv[])
{
	t_commands_array	*commands;
	int					i;
	int					fail_after_limit;

	if (argc != 2)
		exit(EXIT_FAILURE);
	fail_after_limit = atoi(argv[1]);
	i = 0;
	while (i++ < fail_after_limit)
	{
		g_fail_after = i;
		g_num_allocs = 0;
		commands = get_commands("echo $var'hola mundo' > file1 | ls -la");
		if (commands)
		{
			printf("success without failure\n");
			free_commands_array(commands);
		}
	}
	printf("final\n");
	return (0);
}
