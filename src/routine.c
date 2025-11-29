/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:09:35 by maleca            #+#    #+#             */
/*   Updated: 2025/11/29 18:33:20 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(void *arg)
{
	(void)arg;
	printf("philo\n");
	return (0);
}

void	*undertaker_routine(void *arg)
{
	(void)arg;
	pthread_mutex_t	print_lock;

	pthread_mutex_init(&print_lock, NULL);
	pthread_mutex_lock(&print_lock);
	printf("undertaker\n");
	pthread_mutex_unlock(&print_lock);
	return (0);
}
