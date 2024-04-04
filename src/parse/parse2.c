/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:50:03 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/04 11:50:43 by rivasque         ###   ########.fr       */
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

t_command	*parse_command(t_token_node **curr_tok)
{
	t_command	*comm;
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
			error = add_arg(&comm->name_and_args, (*curr_tok)->content);
		else
			error = add_io(*curr_tok, &comm->infiles, &comm->outfiles);
		*curr_tok = (*curr_tok)->next;
	}
	if (error)
		return (free_command(comm), NULL);
	return (comm);
}

t_command	**get_empty_command_array(int len)
{
	t_command	**com_array;
	int			i;

	i = 0;
	com_array = malloc(sizeof(t_command *) * len);
	if (!com_array)
		return (NULL);
	while (i < len)
	{
		com_array[i] = NULL;
		i++;
	}
	return (com_array);
}

t_commands_array	*parse_commands_array(t_token_node	*token_list)
{
	t_commands_array	*com;
	int					i;

	i = 0;
	com = malloc(sizeof(t_commands_array));
	if (!com)
		return (NULL);
	com->len = get_array_command_len(token_list);
	com->comm_array = get_empty_command_array(com->len);
	if (!com->comm_array)
		return (free(com), NULL);
	while (i < com->len && token_list)
	{
		if (token_list->type != T_WORD)
			return (free_commands_array(com), NULL);//parse error
		com->comm_array[i] = parse_command(&token_list);
		if (!com->comm_array[i])
			return (free_commands_array(com), NULL);
		i++;
		if (token_list)
			token_list = token_list->next;
	}
	if (i != com->len)
		return (free_commands_array(com), NULL); //parse error: more commands were expected
	return (com);
}

int	split_comds_args(t_commands_array *comds)
{
	int		i;
	char	**str_arr;

	i = 0;
	while (i < comds->len)
	{
		if (comds->comm_array[i]->name_and_args)
		{
			str_arr = ft_split(comds->comm_array[i]->name_and_args, ' ');
			if (!str_arr)
				return (1);
			comds->comm_array[i]->name_and_args_splt = str_arr;
			if (str_arr[0])
			{
				comds->comm_array[i]->name = str_arr[0];
				str_arr++;
				if (str_arr[0])
					comds->comm_array[i]->args_splitted = str_arr;
			}
		}
		i++;
	}
	return (0);
}
