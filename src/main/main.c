/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:06:40 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/11 09:12:19 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_signal_state	g_signals;

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	((void)argc, (void)argv);
	data = init_mini_shell(envp);
	ft_init_signals();
	read_shell(data);
	return (0);
}
