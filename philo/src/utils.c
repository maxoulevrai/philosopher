/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:32:01 by root              #+#    #+#             */
/*   Updated: 2026/01/18 18:50:08 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->table->stop_lock);
	if (philo->table->stop == false)
	{
		pthread_mutex_lock(&philo->table->print_lock);
		printf("%ld ms %d %s\n", sim_time(philo->table), (philo->idx), status);
		pthread_mutex_unlock(&philo->table->print_lock);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->stop_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->stop_lock);
}
