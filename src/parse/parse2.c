/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:50:03 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/11 12:26:21 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_io(t_token_node *token, t_io_node **io_in, t_io_node **io_out)
{
	t_io_node	*new_io;

	new_io = ft_new_io(token->content, token->io_type);
	if (!new_io)
		return (1);
	token->content = NULL;
	if (ft_is_infile(token->io_type))
		ft_add_io(io_in, new_io);
	else if (ft_is_outfile(token->io_type))
		ft_add_io(io_out, new_io);
	return (0);
}

t_cmd	*parse_command(t_token_node **curr_tok)
{
	t_cmd		*comm;
	int			error;

	comm = create_blank_command();
	if (!comm)
		return (NULL);
	error = 0;
	while (*curr_tok && (*curr_tok)->type != T_PIPE)
	{
		if (error)
			return (free_command(comm), NULL);
		if ((*curr_tok)->io_type == IO_NONE)
			error = add_arg(&comm->name_and_args, &(*curr_tok)->content);
		else
			error = add_io(*curr_tok, &comm->infiles, &comm->outfiles);
		*curr_tok = (*curr_tok)->next;
	}
	if (error)
		return (free_command(comm), NULL);
	return (comm);
}

t_cmd	**get_empty_command_array(int len)
{
	t_cmd		**com_array;
	int			i;

	i = 0;
	com_array = malloc(sizeof(t_cmd *) * len);
	if (!com_array)
		return (NULL);
	while (i < len)
	{
		com_array[i] = NULL;
		i++;
	}
	return (com_array);
}

void	aux_wrapper(t_cmd_array *cmds, t_token_type token_type,
			int *wrong_token)
{
	*wrong_token = 1;
	free_commands_array(cmds);
	print_unexpected_token_error(token_type);
}

t_cmd_array	*parse_commands_array(t_token_node	*token_list,
						int *wrong_token)
{
	t_cmd_array	*cmds;
	int			i;

	i = 0;
	cmds = malloc(sizeof(t_cmd_array));
	if (!cmds)
		return (NULL);
	cmds->len = get_array_command_len(token_list);
	cmds->array = get_empty_command_array(cmds->len);
	if (!cmds->array)
		return (free(cmds), NULL);
	while (i < cmds->len && token_list)
	{
		if (token_list->type != T_WORD)
			return (aux_wrapper(cmds, token_list->type, wrong_token), NULL);
		cmds->array[i] = parse_command(&token_list);
		if (!cmds->array[i++])
			return (free_commands_array(cmds), NULL);
		if (token_list)
			token_list = token_list->next;
	}
	if (i != cmds->len)
		return (aux_wrapper(cmds, T_WORD, wrong_token), NULL);
	return (cmds);
}
