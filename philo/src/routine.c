/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:09:35 by maleca            #+#    #+#             */
/*   Updated: 2026/01/08 18:00:04 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*mims_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->table->start = get_current_time();
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[0]]);
	print_status(philo, "has taken a fork");
	philo_sleep(philo->table->time_to_sleep);
	print_status(philo, "died");
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[0]]);
	return (0);
}

static void	grail_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[0]]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[1]]);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	philo_sleep(philo->table->time_to_eat);
	philo->last_ate = get_current_time();
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[0]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[1]]);
	philo_sleep(philo->table->time_to_sleep);
	print_status(philo, "is sleeping");
}

static void	think_routine(t_philo *philo)
{
	print_status(philo, "is thinking");
	while (philo->forks[0])
}

static void	*start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->table->start = get_current_time();
	if (philo->idx % 2 == 0)
		usleep(10);
	if (philo->table->time_to_eat != -1)
	{
		while (philo->times_ate < philo->table->time_to_eat)
		{
			grail_routine(philo);
			think_routine(philo);
		}
	}
	return (NULL);
}

void	multi_thread(t_table *table)
{
	int	i;

	i = 0;
	table->start = get_current_time();
	if (pthread_create(&table->undertaker_tid, NULL, undertaker_routine, table))
		end_simulation(ERR_UNDERTAKER_TRHD, table);
	while (i < table->nb_philo)
	{
		if (pthread_create(&table->philo[i]->philo_tid, NULL, start, table->philo[i]))
			end_simulation(ERR_PHILO_TRHD, table);
		i++;
	}
}
