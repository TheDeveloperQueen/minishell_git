/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoto-gu <acoto-gu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:06:29 by acoto-gu          #+#    #+#             */
/*   Updated: 2024/04/08 20:16:18 by acoto-gu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*create_one_char_token(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 4);
	if (!str)
		return (NULL);
	str[0] = '\'';
	str[1] = c;
	str[2] = '\'';
	str[3] = '\0';
	return (str);
}

void	print_unexpected_token_error(t_token_type type_of_token)
{
	char	*msg;
	char	*msg_aux;

	if (type_of_token == T_PIPE)
		msg_aux = ft_strjoin("syntax error near unexpected token ", "'|'\n");
	else if (type_of_token == T_D_GREAT_THAN)
		msg_aux = ft_strjoin("syntax error near unexpected token ", "'>>'\n");
	else if (type_of_token == T_D_LESS_THAN)
		msg_aux = ft_strjoin("syntax error near unexpected token ", "'<<'\n");
	else if (type_of_token == T_MORE_THAN)
		msg_aux = ft_strjoin("syntax error near unexpected token ", "'>'\n");
	else if (type_of_token == T_LESS_THAN)
		msg_aux = ft_strjoin("syntax error near unexpected token ", "'<'\n");
	else
		msg_aux = ft_strjoin("syntax error near unexpected token ",
				"'newline'\n");
	msg = create_error_msg(msg_aux);
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg_aux);
	free(msg);
}
