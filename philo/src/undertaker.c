/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undertaker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 18:53:31 by root              #+#    #+#             */
/*   Updated: 2026/02/03 17:19:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static t_bool	check_vital_status(t_table *table,
		time_t current_time, time_t *last_ate_copy)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (current_time - last_ate_copy[i] >= table->time_to_die)
		{
			print_status(table->philo[i], "died");
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static t_bool	check_satiety_status(t_table *table)
{
	pthread_mutex_lock(&table->satiety_lock);
	if (table->satiety >= table->nb_philo)
	{
		pthread_mutex_unlock(&table->satiety_lock);
		pthread_mutex_lock(&table->stop_lock);
		table->stop = TRUE;
		pthread_mutex_unlock(&table->stop_lock);
		return (TRUE);
	}
	pthread_mutex_unlock(&table->satiety_lock);
	return (FALSE);
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
		if (check_vital_status(table, current_time, last_ate_copy) == TRUE)
			break ;
		if (table->min_to_eat != -1 && check_satiety_status(table) == TRUE)
			break ;
		usleep(200);
	}
	return (NULL);
}
