/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:15:46 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/08 07:57:25 by acoto-gu         ###   ########.fr       */
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
	if (i == 1)
		return (0);
	return (1);
}

void	special_print_list(t_list *lst, char *delimiter, t_data *data)
{
	while (lst)
	{
		if (lst->next)
		{
			if (ft_strcmp(lst->content, "~") == 0)
				ft_putstr(search_env(data, "HOME"));
			else
				ft_putstr(lst->content);
			ft_putstr(delimiter);
		}
		else
		{
			if (ft_strcmp(lst->content, "~") == 0)
				ft_putstr(search_env(data, "HOME"));
			else
				ft_putstr(lst->content);
		}
		lst = lst->next;
	}
}

int	ft_echo(t_command *cmd, t_data *data)
{
	int		flag;

	flag = 0;
	if (!cmd->args)
		ft_putstr("\n");
	else
	{
		while (cmd->args && check_n(cmd->args->content))
		{
			cmd->args = cmd->args->next;
			flag = 1;
		}
		special_print_list(cmd->args, " ", data);
		if (!flag)
			ft_putstr("\n");
	}
	return (0);
}
