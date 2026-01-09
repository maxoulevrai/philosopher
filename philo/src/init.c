/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:10:02 by maleca            #+#    #+#             */
/*   Updated: 2026/01/09 17:09:35 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	get_forks(t_philo *philo)
{
	philo->forks[0] = philo->idx;
	philo->forks[1] = (philo->idx + 1) % philo->table->nb_philo;
}

static int	init_forks(t_table *table)
{
	int	i;

	table->fork_locks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->fork_locks)
		end_simulation(ERR_MALLOC, table);
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->fork_locks[i], NULL))
			return (end_simulation(ERR_MUTEX, table), 1);
		i++;
	}
	return (0);
}

static t_philo	**init_philo(t_table *table)
{
	int	i;
	t_philo	**philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * table->nb_philo);
	if (!philo)
		msg_err(ERR_MALLOC_PHILO);
	while (i < table->nb_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (msg_err(ERR_MALLOC), NULL);
		philo[i]->idx = i;
		philo[i]->last_ate = 0;
		philo[i]->times_ate = 0;
		philo[i]->table = table;
		get_forks(philo[i]);
		i++;
	}
	return (philo);
}

static int	init_global_locks(t_table *table)
{
	if (init_forks(table))
		return (msg_err(ERR_MUTEX), 1);
	if (pthread_mutex_init(&table->print_lock, NULL))
		return (msg_err(ERR_MUTEX), 1);
	return (0);
}

t_table	*init(int ac, char **av, t_table *table)
{
	int	i;
	
	table = malloc(sizeof(t_table));
	if (!table)
		msg_err(ERR_MALLOC);
	i = 1;
	table->nb_philo = positive_atoi(av[i++]);
	table->time_to_die = positive_atoi(av[i++]);
	table->time_to_eat = positive_atoi(av[i++]);
	table->time_to_sleep = positive_atoi(av[i++]);
	table->min_to_eat = -1;
	if (ac == 6)
		table->min_to_eat = positive_atoi(av[i++]);
	if (init_global_locks(table))
		return (msg_err(ERR_MUTEX), NULL);
	table->philo = init_philo(table);
	if (!table->philo)
		return (msg_err(ERR_MUTEX), NULL);
	table->stop = 0;
	return (table);
}
