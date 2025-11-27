/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:42:20 by maleca            #+#    #+#             */
/*   Updated: 2025/11/27 19:59:28 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	only_digits(char *s)
{
	size_t	i;
	
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	positive_atoi(const char *nptr)
{
	size_t					i;
	unsigned long long int	nbr;

	i = 0;
	nbr = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + (nptr[i] - '0');
		i++;
	}
	if (nbr > INT_MAX)
		nbr = -1;
	return ((int)nbr);
}

bool	is_valid(int ac, char **av)
{
	int	i;
	int nb;

	i = 1;
	nb = 0;
	while (i < ac)
	{
		if (!only_digits(av[i]))
			msg_err(ERR_DIGITS);
		nb = positive_atoi(av[i]);
		if (i == 1 && (nb > MAX_PHILO || nb == 1))
			msg_err(ERR_MAX_COUNT);
		if (i != 1 && nb == -1)
			msg_err(ERR_MAX_COUNT);
		i++;
	}
	return (true);
}
