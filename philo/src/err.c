/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:05:52 by maleca            #+#    #+#             */
/*   Updated: 2026/01/02 18:28:34 by maleca           ###   ########.fr       */
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
	if (&table->print_lock)
		pthread_mutex_destroy(&table->print_lock);
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
	free_locks(table);
	// if (table->undertaker_tid)
	// 	free(table->undertaker_tid);
	printf("%s", err_msg); 
}
