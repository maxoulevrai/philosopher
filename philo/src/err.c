/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 15:05:52 by maleca            #+#    #+#             */
/*   Updated: 2025/12/16 12:26:33 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	msg_err(char *err_msg)
{
	printf("%s", err_msg);
	exit (1);
}

void	hdl_err(char *err_msg, t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->philo_tid)
		free(philo->philo_tid);
	if (table->undertaker_tid)
		free(table->undertaker_tid);
	if (table->fork)
	{
		while (&table->fork[i])
		{
			pthread_mutex_destroy(&table->fork[i]);
			i++;
		}
		free(table->fork);
	}
	printf("%s", err_msg);
	exit(1);
}
