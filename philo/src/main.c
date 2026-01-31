/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:10:34 by maleca            #+#    #+#             */
/*   Updated: 2026/01/31 20:50:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	end_simulation(char *err_msg, t_table *table)
{
	free_philo(table);
	free_locks(table);
	free(table);
	if (err_msg)
		printf("%s\n", err_msg);
}

void	multi_thread(t_table *table)
{
	int	i;

	i = 0;
	table->start = get_current_time();
	if (pthread_create(&table->undertaker_tid, NULL, undertaker_routine, table))
		end_simulation(ERR_UNDERTAKER_TRHD, table);
	while (i < table->nb_philo)
	{
		if (pthread_create(&table->philo[i]->philo_tid,
				NULL, start, table->philo[i]))
			end_simulation(ERR_PHILO_TRHD, table);
		i++;
	}
	pthread_join(table->undertaker_tid, NULL);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->philo[i]->philo_tid, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	if (ac < 5 || ac > 6)
		msg_err(ERR_ARGS);
	if (!is_valid(ac, av))
		return (EXIT_FAILURE);
	table = init(ac, av, table);
	if (table->nb_philo == 1)
	{
		if (pthread_create(&table->philo[0]->philo_tid,
				NULL, mims_routine, table->philo[0]))
			end_simulation(ERR_PHILO_TRHD, table);
		pthread_join(table->philo[0]->philo_tid, NULL);
	}
	else
		multi_thread(table);
	end_simulation(NULL, table);
	return (EXIT_SUCCESS);
}
