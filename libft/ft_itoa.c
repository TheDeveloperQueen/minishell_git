/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivasque <rivasque@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:25:32 by rivasque          #+#    #+#             */
/*   Updated: 2024/02/29 10:24:51 by rivasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countn(long n)
{
	int		count;

	count = 0;
	if (n == 0)
		return (1);
	while (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static int	ft_isneg(long n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	nbr;
	long	i;
	long	sign;

	nbr = (long)n;
	sign = ft_isneg(nbr);
	result = (char *)ft_calloc((ft_countn(nbr) + 1), sizeof(char));
	if (!result)
		return (NULL);
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	i = sign + ft_countn(nbr) - 1;
	while (i >= (0 + sign))
	{
		result[i] = nbr % 10 + '0';
		nbr = nbr / 10;
		i--;
	}
	return (result);
}
