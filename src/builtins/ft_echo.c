/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:15:46 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/20 16:24:52 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-')
		i++;
	else
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_command *cmd)
{
	int		flag;
	
	flag = 0;
	if (!cmd->args)
		printf("\n");
	else
	{
		while (cmd->args && check_n(cmd->args->content))
		{
			cmd->args = cmd->args->next;
			flag = 1;
		}
		print_list(cmd->args, " ");
		if (!flag)
			printf("\n");
	}
	return (0);
}
