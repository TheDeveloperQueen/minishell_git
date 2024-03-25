/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 19:00:02 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/03/25 15:08:27 by acoto-gu         ###   ########.fr       */
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
