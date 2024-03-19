/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_dups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ritavasques <ritavasques@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:39:56 by ritavasques       #+#    #+#             */
/*   Updated: 2024/03/18 19:53:49 by ritavasques      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int do_dup(int fd)
{
    int new_fd;

    new_fd = dup(fd);
    if (new_fd == -1)
    {
        perror("dup Error\n");
        exit(EXIT_FAILURE);
    }
    return (new_fd);
}

int do_dup2(int fd1, int fd2)
{
    int fd;

    fd = dup2(fd1, fd2);
    if (fd == -1)
    {
        perror("dup2 Error\n");
        exit(EXIT_FAILURE);
    }
    return (fd);
}
