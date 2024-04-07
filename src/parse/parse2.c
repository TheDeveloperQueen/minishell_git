/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 11:50:03 by rivasque          #+#    #+#             */
/*   Updated: 2024/04/07 13:40:01 by acoto-gu         ###   ########.fr       */
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
			error = add_arg(&comm->name_and_args, &(*curr_tok)->content);
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

char	**create_str_arr(t_list *cmd_name_and_args)
{
	char 	**str_arr;
	int		lst_size;
	int		i;

	lst_size = ft_lstsize(cmd_name_and_args);
	str_arr = malloc(sizeof(char *) * (lst_size + 1));
	if (!str_arr)
		return (NULL);
	i = 0;
	while (cmd_name_and_args)
	{
		str_arr[i] = cmd_name_and_args->content;
		i++;
		cmd_name_and_args = cmd_name_and_args->next;
	}
	str_arr[lst_size] = NULL;
	return(str_arr);
}

int	set_name_and_args_fields(t_commands_array *comds)
{
	char		**str_arr;
	int			i;
	t_command	*cmd;

	i = 0;
	while (i < comds->len)
	{
		cmd = comds->comm_array[i];
		if (cmd->name_and_args)
		{
			if (cmd->name_and_args->next)
				cmd->args = cmd->name_and_args->next;
			str_arr = create_str_arr(cmd->name_and_args);
			if (!str_arr)
				return (1);
			cmd->name_and_args_splt = str_arr;
			if (str_arr[0])
				cmd->name = str_arr[0];
		}
		i++;
	}
	return (0);
}
