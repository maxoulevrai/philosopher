/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:10:02 by maleca            #+#    #+#             */
/*   Updated: 2025/11/24 17:32:43 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	*init_table(int ac, char **av, t_table *table)
{
	size_t	i;
	t_table *args;
	
	i = 1;
	while (av[i])
	{
		if (!ft_is_digit(av[i]))
			return (NULL);
	}
	init(ac, av, args);
	return (args);
}
