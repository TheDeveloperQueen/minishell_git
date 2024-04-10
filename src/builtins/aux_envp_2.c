/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_envp_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 09:08:03 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/10 09:37:59 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_envp_3(t_data *data)
{
	lst_add_back(&data->envp, lst_add_new(ft_strdup("PWD"), getcwd(NULL, 0)));
	lst_add_back(&data->envp, lst_add_new(ft_strdup("SHLVL"), ft_strdup("1")));
	lst_add_back(&data->envp, lst_add_new(ft_strdup("_"),
			ft_strdup("/usr/bin/env")));
}
