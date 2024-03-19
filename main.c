/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:22:32 by rivasque          #+#    #+#             */
/*   Updated: 2024/03/18 19:15:53 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	t_command	*cmd;
	t_data	*data;
	
	cmd = init_cmd();
	data = init_data();
	cmd->name = argv[1];
	//cmd->args = get_args(argv);
	data->envp = get_envp(envp);
	exec_builtin(cmd, data);
	/*TO TEST EXPORT: 
	print env to check that variable was added*/
	//ft_env(data->envp);
	// TO TEST CD
	//ft_pwd(cmd);
	return (0);
}



