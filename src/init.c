/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:10:02 by maleca            #+#    #+#             */
/*   Updated: 2025/11/25 16:09:22 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// void	init_philo(int ac, char **av, t_table *table)
// {
	
// }

void	init_table(int ac, char **av, t_table **table)
{
	int	i;
	
	*table = malloc(sizeof(t_table));
	if (!table)
	{
		hdl_err(ERR_MALLOC, NULL);
		return ;
	}
	i = 1;
	while (i < ac)
	{
		(*table)->nb_philo = positive_atoi(av[i++]);
		(*table)->time_to_die = positive_atoi(av[i++]);
		(*table)->time_to_eat = positive_atoi(av[i++]);
		(*table)->time_to_sleep = positive_atoi(av[i++]);
		(*table)->min_to_eat = -1;
	}
	if (ac == 6)
		(*table)->min_to_eat = positive_atoi(av[i++]);
	// init_philo()
}
