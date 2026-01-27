/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:32:01 by root              #+#    #+#             */
/*   Updated: 2026/01/27 20:03:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int		ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	print_status(t_philo *philo, char *status)
{
	int stop;
	
	pthread_mutex_lock(&philo->table->stop_lock);
	stop = philo->table->stop;
	pthread_mutex_unlock(&philo->table->stop_lock);
	if (!ft_strcmp(status, "died"))
		stop = true;
	if (stop == false)
	{
		pthread_mutex_lock(&philo->table->print_lock);
		printf("%ld ms %d %s\n", sim_time(philo->table), (philo->idx), status);
		pthread_mutex_unlock(&philo->table->print_lock);
	}
	else
		return ;
}
