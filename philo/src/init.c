/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:10:02 by maleca            #+#    #+#             */
/*   Updated: 2025/12/18 19:19:39 by root             ###   ########.fr       */
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
		hdl_err(ERR_MALLOC, table);
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->fork_locks[i], NULL))
			hdl_err(ERR_MUTEX, table);
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
		philo[i] = malloc(sizeof(t_philo) * 1);
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
	if (!pthread_mutex_init(&table->sleep_lock, NULL))
		msg_err(ERR_MUTEX);
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
	init_global_locks(table);
	init_philo(table);
}
