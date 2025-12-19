/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:10:02 by maleca            #+#    #+#             */
/*   Updated: 2025/12/19 20:26:24 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	get_forks(t_philo *philo)
{
	philo->forks[0] = philo->idx;
	philo->forks[1] = (philo->idx + 1) % philo->table->nb_philo;
}

void	init_forks(t_table *table)
{
	int	i;

	table->fork_locks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->fork_locks)
		hdl_err(ERR_MALLOC, table, NULL);
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->fork_locks[i], NULL))
			hdl_err(ERR_MUTEX, table, NULL);
		i++;
	}
}



t_philo	**init_philo(t_table *table)
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
		philo[i]->times_ate = 0;
		philo[i]->table = table;
		get_forks(philo[i]);
		i++;
	}
	return (philo);
}

void	init_global_locks(t_table *table)
{
	init_forks(table);
	if (!pthread_mutex_init(&table->print_lock, NULL))
		msg_err(ERR_MUTEX);
}

void	init(int ac, char **av, t_table *table)
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
	init_global_locks(table);
	init_philo(table);
}
