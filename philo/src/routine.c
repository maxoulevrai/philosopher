/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 19:02:07 by maleca            #+#    #+#             */
/*   Updated: 2026/01/16 20:27:12 by maleca           ###   ########.fr       */
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
	thread_sleep(philo->table->time_to_sleep, philo->table);
	print_status(philo, "died");
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[0]]);
	return (0);
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
		if (sim_time(table) - table->philo[i]->last_ate > table->time_to_die)
			break ;
		if (table->min_to_eat != -1)
		{
			pthread_mutex_lock(&table->satiety_lock);
			if (table->satiety >= table->min_to_eat)
			{
				pthread_mutex_unlock(&table->satiety_lock);
				break ;
			}
			pthread_mutex_unlock(&table->satiety_lock);
		}
		i++;
	}
	printf("%ld\n", table->philo[i]->last_ate);
	print_status(table->philo[i], "died");
	table->stop = true;
	return (0);
}

static void	grail_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[0]]);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->fork_locks[philo->forks[1]]);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	thread_sleep(philo->table->time_to_eat, philo->table);
	philo->last_ate = sim_time(philo->table);
	if (philo->times_ate++ == philo->table->min_to_eat && philo->table->min_to_eat != -1)
	{
		pthread_mutex_lock(&philo->table->satiety_lock);
		philo->table->satiety++;
		pthread_mutex_unlock(&philo->table->satiety_lock);
	}
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[1]]);
	pthread_mutex_unlock(&philo->table->fork_locks[philo->forks[0]]);
	print_status(philo, "is sleeping");
	thread_sleep(philo->table->time_to_sleep, philo->table);
	print_status(philo, "is thinking");
	thread_sleep(60, philo->table);
}

static void	*start(void *arg)
{
	t_philo	*philo;
	int		stop;

	philo = (t_philo *)arg;
	if (philo->idx % 2 == 0)
		usleep(10);
	pthread_mutex_lock(&philo->table->stop_lock);
	stop = philo->table->stop;
	pthread_mutex_unlock(&philo->table->stop_lock);
	while (stop == false)
	{
		grail_routine(philo);
		pthread_mutex_lock(&philo->table->stop_lock);
		stop = philo->table->stop;
		pthread_mutex_unlock(&philo->table->stop_lock);
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
	pthread_join(table->undertaker_tid, NULL);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->philo[i]->philo_tid, NULL);
		i++;
	}
}
