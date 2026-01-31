/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   utils.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: root <root@student.42.fr>				  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/12/18 18:32:01 by root			  #+#	#+#			 */
/*   Updated: 2026/01/31 19:16:06 by root			 ###   ########.fr	   */
/*																			*/
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
	pthread_mutex_lock(&philo->table->stop_lock);
	if (philo->table->stop == true)
	{
		pthread_mutex_unlock(&philo->table->stop_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->stop_lock);
	if (ft_strcmp(status, "died") == 0)
	{
		pthread_mutex_lock(&philo->table->stop_lock);
		philo->table->stop = true;
		pthread_mutex_unlock(&philo->table->stop_lock);
	}
	pthread_mutex_lock(&philo->table->print_lock);
	printf("%ld ms %d %s\n", sim_time(philo->table), philo->idx, status);
	pthread_mutex_unlock(&philo->table->print_lock);
}

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
	int		stop;

	wake_up = get_current_time() + sleep_time;
	while (get_current_time() < wake_up)
	{
		pthread_mutex_lock(&table->stop_lock);
		stop = table->stop;
		pthread_mutex_unlock(&table->stop_lock);
		if (stop)
			break;
		usleep(1000);
	}
}
