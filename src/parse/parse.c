/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:00:02 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/04 23:01:24 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_array_command_len(t_token_node *token_list)
{
	int	len;

	len = 1;
	while (token_list)
	{
		if (token_list->type == T_PIPE)
			len++;
		token_list = token_list->next;
	}
	return (len);
}

t_command	*create_blank_command(void)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (!new_command)
		return (NULL);
	new_command->args = NULL;
	new_command->name_and_args = NULL;
	new_command->name_and_args_splt = NULL;
	new_command->name = NULL;
	new_command->args_splitted = NULL;
	new_command->infiles = NULL;
	new_command->outfiles = NULL;
	return (new_command);
}

int	add_arg(char **old_arg, char *to_add)
{
	char	*new_arg;

	if (!to_add[0])
		return (0);
	if (!*old_arg)
	{
		new_arg = ft_strdup(to_add);
		if (!new_arg)
			return (1);
		*old_arg = new_arg;
		return (0);
	}
	new_arg = ft_strjoin_char(*old_arg, to_add, ' ');
	if (!new_arg)
		return (1);
	free(*old_arg);
	*old_arg = new_arg;
	return (0);
}

int	ft_is_infile(t_io_type type)
{
	if (type == IO_IN || type == IO_HEREDOC)
		return (1);
	return (0);
}

int	ft_is_outfile(t_io_type type)
{
	if (type == IO_OUT || type == IO_APPEND)
		return (1);
	return (0);
}
