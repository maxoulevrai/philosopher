/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undertaker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:53:31 by root              #+#    #+#             */
/*   Updated: 2026/01/31 20:19:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static bool	check_vital_status(t_table *table, time_t current_time, time_t *last_ate_copy)
{
	int i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (current_time - last_ate_copy[i] >= table->time_to_die)
		{
			print_status(table->philo[i], "died");
			return (true);
		}
		i++;
	}
	return (false);
}

static bool	check_satiety_status(t_table *table)
{
	pthread_mutex_lock(&table->satiety_lock);
	if (table->satiety >= table->nb_philo)
	{
		pthread_mutex_unlock(&table->satiety_lock);
		pthread_mutex_lock(&table->stop_lock);
		table->stop = true;
		pthread_mutex_unlock(&table->stop_lock);
		return (true);
	}
	pthread_mutex_unlock(&table->satiety_lock);
	return (false);
}

void	*undertaker_routine(void *arg)
{
	int		i;
	t_table	*table;
	time_t	current_time;
	time_t	last_ate_copy[MAX_PHILO];

	table = (t_table *)arg;
	while (1)
	{
		current_time = sim_time(table);
		pthread_mutex_lock(&table->last_ate_lock);
		i = 0;
		while (i < table->nb_philo)
		{
			last_ate_copy[i] = table->philo[i]->last_ate;
			i++;
		}
		pthread_mutex_unlock(&table->last_ate_lock);
		if (check_vital_status(table, current_time, last_ate_copy) == true)
			break ;
		if (table->min_to_eat != -1 && check_satiety_status(table) == true)
			break ;
		usleep(1000);
	}
	return (NULL);
}
