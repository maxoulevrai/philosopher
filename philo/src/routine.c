/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:09:35 by maleca            #+#    #+#             */
/*   Updated: 2025/12/18 19:07:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*mims_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(philo->forks[1]);
	print_status(philo, "TOOK FORK 1");
	philo_sleep(philo->table->time_to_sleep);
	print_status(philo, "HAS DIED");
	pthread_mutex_unlock(philo->forks[0]);
	return (0);
}

void	*undertaker_routine(void *arg)
{
	return (0);
	
}
