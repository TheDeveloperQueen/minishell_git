/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:39:58 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/13 13:38:27 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_father_signals_handlers(void)
{
	signal(SIGINT, father_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	set_child_signals_handlers(void)
{
	signal(SIGINT, child_handler);
	signal(SIGQUIT, child_handler);
}

void	set_heredoc_signals_handler(void)
{
	signal(SIGINT, heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}
