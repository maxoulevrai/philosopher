/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:09:35 by maleca            #+#    #+#             */
/*   Updated: 2026/01/02 19:06:32 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*mims_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->forks[0]);
	print_status(philo, "has taken a fork");
	philo_sleep(philo->table->time_to_sleep);
	print_status(philo, "died");
	pthread_mutex_unlock(philo->forks[0]);
	return (0);
}

void	grail_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[0]]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[1]]);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	philo_sleep(philo->table->time_to_eat);
	philo->last_ate = get_current_time;
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[0]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[1]]);
	philo_sleep(philo->table->time_to_sleep);
	print_status(philo, "is sleeping");
}

void	think_routine(t_philo *philo)
{
	print_status(philo, "is thinking");
	philo_sleep(philo->table->time_to_die)
}

void	*start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->table->start = get_current_time();
	if (philo->idx % 2 == 0)
		usleep(10);
	grail_routine(philo);
	think_routine(philo);

}

void	multi_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_create(&table->philo[i]->philo_tid, NULL, start, table->philo[i]))
			hdl_err(ERR_PHILO_TRHD, table);
		i++;
	}
}
