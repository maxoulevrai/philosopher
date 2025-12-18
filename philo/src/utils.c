/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:32:01 by root              #+#    #+#             */
/*   Updated: 2025/12/18 19:09:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%d %d %s", get_current_time(), philo->idx, status);
	pthread_mutex_unlock(&philo->table->print_lock);
}
