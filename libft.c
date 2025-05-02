/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbenhssi <nbenhssi@student.1337.ma>        #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-25 09:24:54 by nbenhssi          #+#    #+#             */
/*   Updated: 2025-04-25 09:24:54 by nbenhssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *nptr)
{
	int	signe;
	int	nbr;
	int	i;

	signe = 1;
	nbr = 0;
	i = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		printf("invalid atoi\n");
		exit (0);
	}
	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9')
		{
			printf("invalid atoi\n");
			exit (0);
		}
		nbr = nbr * 10;
		nbr += nptr[i] - '0';
		i++;
	}
	return (signe * nbr);
}
