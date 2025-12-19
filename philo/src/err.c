/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:05:52 by maleca            #+#    #+#             */
/*   Updated: 2025/12/19 20:20:35 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	msg_err(char *err_msg)
{
	printf("%s", err_msg);
	exit (1);
}

void	hdl_err(char *err_msg, t_table *table)
{
	int	i;

	i = 0;
	if (table->philo)
	{
		while (table->philo[i])
		{
			free(table->philo[i]->philo_tid);
			i++;
		}
		free(table->philo);
	}
	// if (table->undertaker_tid)
	// 	free(table->undertaker_tid);
	if (table->fork_locks)
	{
		while (&table->fork_locks[i])
		{
			pthread_mutex_destroy(&table->fork_locks[i]);
			i++;
		}
		free(table->fork_locks);
	}
	if (&table->print_lock)
		pthread_mutex_destroy(&table->print_lock);
	printf("%s", err_msg);
	exit(1);
}
