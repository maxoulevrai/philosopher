/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:05:52 by maleca            #+#    #+#             */
/*   Updated: 2026/01/16 18:04:32 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	msg_err(char *err_msg)
{
	printf("%s", err_msg);
	exit (1);
}

void	free_locks(t_table *table)
{
	int	i;

	i = 0;
	if (table->fork_locks)
	{
		while (i < table->nb_philo)
		{
			pthread_mutex_destroy(&table->fork_locks[i]);
			i++;
		}
		free(table->fork_locks);
	}
	pthread_mutex_destroy(&table->print_lock);
}

void	free_philo(t_table *table)
{
	int	i;

	if (table->philo)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			free(table->philo[i]);
			i++;
		}
		free(table->philo);
	}
}
