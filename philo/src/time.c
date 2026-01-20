/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 17:07:15 by root              #+#    #+#             */
/*   Updated: 2026/01/20 17:18:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

time_t	sim_time(t_table *table)
{
	return (get_current_time() - table->start);
}

void	thread_sleep(time_t sleep_time, t_table *table)
{
	time_t	wake_up;

	wake_up = get_current_time() + sleep_time;
	while (get_current_time() < wake_up && table->stop == false)
		usleep(100);
	
}
