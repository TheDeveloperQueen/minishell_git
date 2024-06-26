/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 08:18:54 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/09 11:11:39 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd_array	*get_commands(char *line, t_data *data,
						int *missing_quote, int *wrong_token)
{
	t_token_node	*token_list;
	t_cmd_array		*commands;
	int				error;

	token_list = tokenize(line, missing_quote);
	if (!token_list)
		return (NULL);
	error = format_tokens(&token_list, wrong_token);
	if (error)
		return (ft_clear_token_lst(&token_list), NULL);
	error = expand_tokens(token_list, data);
	if (error)
		return (ft_clear_token_lst(&token_list), NULL);
	commands = parse_commands_array(token_list, wrong_token);
	ft_clear_token_lst(&token_list);
	if (!commands)
		return (NULL);
	error = set_name_and_args_fields(commands);
	if (error)
		return (free_commands_array(commands), NULL);
	return (commands);
}
