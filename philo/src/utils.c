/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:32:01 by root              #+#    #+#             */
/*   Updated: 2026/01/15 18:22:29 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_philo *philo, char *status)
{
	if (philo->table->stop == false)
	{
		pthread_mutex_lock(&philo->table->print_lock);
		printf("%ld ms %d %s\n", (get_current_time() - philo->table->start), (philo->idx + 1), status);
		pthread_mutex_unlock(&philo->table->print_lock);
	}
}
