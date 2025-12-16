/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:10:02 by maleca            #+#    #+#             */
/*   Updated: 2025/12/16 16:53:52 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_forks(t_table *table, t_philo *philo)
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
	i = 0;
	while (i < table->nb_philo)
	{
		philo[i].idx = i;
		philo[i].fork = 1;
		philo[i].last_meal = 0;
		philo[i].table = table;
		i++;
	}
}

// void	init_multi_thread(t_table *table, t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < table->nb_philo)
// 	{
// 		if (pthread_create(philo[i].philo_tid, NULL, philo_routine, NULL))
// 			hdl_err(ERR_PHILO_TRHD, table);
// 		philo[i].idx = i;
// 		i++;
// 	}
// }

void	init_philo(t_table *table)
{
	int	i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(pthread_t) * table->nb_philo);
	if (!philo)
		msg_err(ERR_MALLOC_PHILO);
	init_forks(table, philo);
	table->philo = philo;
	philo->table = table;
	if (table->nb_philo == 1)
	{
		if (pthread_create(philo->philo_tid, NULL, philo_routine, table))
			hdl_err(ERR_PHILO_TRHD, table);
	}
	// else
	// 	multi_thread(table, philo);
	// table->undertaker_tid = malloc(sizeof(pthread_t));
	// if (!table->undertaker_tid)
	// 	hdl_err(ERR_ARGS, table);
	// if (pthread_create(table->undertaker_tid, NULL, undertaker_routine, NULL))
	// 	hdl_err(ERR_UNDERTAKER_TRHD , table);
}

void	init(int ac, char **av, t_table *table)
{
	int	i;
	
	table = malloc(sizeof(t_table));
	if (!table)
		msg_err(ERR_MALLOC);
	i = 1;
	while (i < ac - 1)
	{
		table->nb_philo = positive_atoi(av[i++]);
		table->time_to_die = positive_atoi(av[i++]);
		table->time_to_eat = positive_atoi(av[i++]);
		table->time_to_sleep = positive_atoi(av[i++]);
		table->min_to_eat = -1;
	}
	if (ac == 6)
		table->min_to_eat = positive_atoi(av[i++]);
	init_philo(table);
}
