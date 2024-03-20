/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:06:40 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/03/20 15:01:49 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	*init_data(void)
{
	return ((t_data *) malloc(sizeof(t_data)));
}

int	main(void)
{
	read_shell();
	return (0);
}
