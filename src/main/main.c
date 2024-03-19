/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:06:40 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/03/19 18:41:20 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
