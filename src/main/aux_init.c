/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:30:04 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/19 18:41:11 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command	*init_cmd(void)
{
	return ((t_command *) malloc(sizeof(t_command)));
}

t_data	*init_data(void)
{
	return ((t_data *) malloc(sizeof(t_data)));
}
