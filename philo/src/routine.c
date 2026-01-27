/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:02:07 by maleca            #+#    #+#             */
/*   Updated: 2026/01/27 20:05:41 by root             ###   ########.fr       */
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

static bool	check_satiety_status(t_table *table)
{
	pthread_mutex_lock(&table->satiety_lock);
	if (table->satiety >= table->nb_philo)
	{
		pthread_mutex_unlock(&table->satiety_lock);
		return (true);
	}
	pthread_mutex_unlock(&table->satiety_lock);
	return (false);
}

void	*undertaker_routine(void *arg)
{
	int	i;
	t_table	*table;

	i = 0;
	table = (t_table *)arg;
	thread_sleep(table->time_to_eat, table);
	while (1)
	{
		if (i == table->nb_philo - 1)
			i = 0;
		pthread_mutex_lock(&table->last_ate_lock);
		if (sim_time(table) - table->philo[i]->last_ate >= table->time_to_die)
		{
			print_status(table->philo[i], "died");
			pthread_mutex_unlock(&table->last_ate_lock);
			break ;
		}
		pthread_mutex_unlock(&table->last_ate_lock);
		if (table->min_to_eat != -1 && check_satiety_status(table) == true)
			break ;
		thread_sleep(60, table);
		i++;
	}
	pthread_mutex_lock(&table->stop_lock);
	table->stop = true;
	pthread_mutex_unlock(&table->stop_lock);
	return (0);
}

static void	think_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->stop_lock);
	if (philo->table->stop == true)
	{
		pthread_mutex_unlock(&philo->table->stop_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->stop_lock);
	print_status(philo, "is sleeping");
	thread_sleep(philo->table->time_to_sleep, philo->table);
	pthread_mutex_lock(&philo->table->stop_lock);
	if (philo->table->stop == true)
	{
		pthread_mutex_unlock(&philo->table->stop_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->stop_lock);
	print_status(philo, "is thinking");
		// if (philo->idx % 2 == 0)
		// 	thread_sleep((philo->table->time_to_eat / 2), philo->table);
		// else
		// 	thread_sleep((philo->table->time_to_eat / 2), philo->table);
}

static void	grail_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[0]]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->stop_lock);
	if (philo->table->stop == true)
	{
		pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[0]]);
		pthread_mutex_unlock(&philo->table->stop_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->stop_lock);
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[1]]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->stop_lock);
	if (philo->table->stop == true)
	{
		pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[0]]);
		pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[1]]);
		pthread_mutex_unlock(&philo->table->stop_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->stop_lock);
	print_status(philo, "is eating");
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[0]]);
	pthread_mutex_lock(&philo->table->last_ate_lock);
	philo->last_ate = sim_time(philo->table);
	pthread_mutex_unlock(&philo->table->last_ate_lock);
	thread_sleep(philo->table->time_to_eat, philo->table);
	philo->times_ate++;
	if (philo->times_ate == philo->table->min_to_eat && philo->table->min_to_eat != -1)
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
	if (philo->idx % 2 != 0)
		thread_sleep(philo->table->time_to_eat, philo->table);
	stop = false;
	while (stop == false)
	{
		grail_routine(philo);
		think_sleep_routine(philo);
		pthread_mutex_lock(&philo->table->stop_lock);
		stop = philo->table->stop;
		pthread_mutex_unlock(&philo->table->stop_lock);
	}
	return (NULL);
}
