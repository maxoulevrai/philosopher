/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:10:02 by maleca            #+#    #+#             */
/*   Updated: 2025/11/27 21:34:17 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->fork = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->fork)
		hdl_err(ERR_MALLOC, table);
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL))
			hdl_err(ERR_MUTEX, table);
		i++;
	}
}


void	init_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philo_tid = malloc(sizeof(pthread_t) * table->nb_philo);
	if (!table->philo_tid)
		msg_err(ERR_MALLOC_PHILO);
	while (i < table->nb_philo)
	{
		if (pthread_create(&table->philo_tid[i], NULL, philo_routine, NULL))
			hdl_err(ERR_PHILO_TRHD, table);
		i++;
	}
	table->undertaker_tid = malloc(sizeof(pthread_t));
	if (!table->undertaker_tid)
		hdl_err(ERR_ARGS, table);
	if (pthread_create(table->undertaker_tid, NULL, undertaker_routine, NULL))
		hdl_err(ERR_UNDERTAKER_TRHD , table);
	init_forks(table);
}

void	init_table(int ac, char **av, t_table **table)
{
	int	i;
	
	*table = malloc(sizeof(t_table));
	if (!table)
		msg_err(ERR_MALLOC);
	i = 1;
	while (i < ac - 1)
	{
		(*table)->nb_philo = positive_atoi(av[i++]);
		(*table)->time_to_die = positive_atoi(av[i++]);
		(*table)->time_to_eat = positive_atoi(av[i++]);
		(*table)->time_to_sleep = positive_atoi(av[i++]);
		(*table)->min_to_eat = -1;
	}
	if (ac == 6)
		(*table)->min_to_eat = positive_atoi(av[i++]);
	init_philo(*table);
}
