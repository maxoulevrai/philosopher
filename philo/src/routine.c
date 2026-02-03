/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:14:18 by root              #+#    #+#             */
/*   Updated: 2026/02/03 15:28:04 by root             ###   ########.fr       */
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
	thread_sleep(philo->table->time_to_die, philo->table);
	print_status(philo, "died");
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[0]]);
	return (0);
}

static void	think_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->stop_lock);
	if (philo->table->stop == TRUE)
	{
		pthread_mutex_unlock(&philo->table->stop_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->stop_lock);
	print_status(philo, "is sleeping");
	thread_sleep(philo->table->time_to_sleep, philo->table);
	print_status(philo, "is thinking");
	usleep(100);
}

static void	grail_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[0]]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[1]]);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->table->last_ate_lock);
	philo->last_ate = sim_time(philo->table);
	pthread_mutex_unlock(&philo->table->last_ate_lock);
	thread_sleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[0]]);
	philo->times_ate++;
	if (philo->times_ate == philo->table->min_to_eat)
	{
		pthread_mutex_lock(&philo->table->satiety_lock);
		philo->table->satiety++;
		pthread_mutex_unlock(&philo->table->satiety_lock);
	}
}

void	*start(void *arg)
{
	t_philo	*philo;
	int		stop;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->table->last_ate_lock);
	philo->last_ate = philo->table->start;
	pthread_mutex_unlock(&philo->table->last_ate_lock);
	if (philo->table->nb_philo % 2 == 0 && philo->idx % 2 == 0)
		usleep(1000);
	else if (philo->table->nb_philo % 2 != 0
		&& philo->idx == philo->table->nb_philo - 1)
		usleep(1000);
	stop = FALSE;
	while (stop == FALSE)
	{
		grail_routine(philo);
		think_sleep_routine(philo);
		pthread_mutex_lock(&philo->table->stop_lock);
		stop = philo->table->stop;
		pthread_mutex_unlock(&philo->table->stop_lock);
	}
	return (NULL);
}
