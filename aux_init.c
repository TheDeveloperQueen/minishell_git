/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:30:04 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/16 13:30:49 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*init_cmd(void)
{
	return ((t_command *) malloc(sizeof(t_command)));
}

t_data	*init_data(void)
{
	return ((t_data *) malloc(sizeof(t_data)));
}
