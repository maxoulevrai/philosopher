/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:10:34 by maleca            #+#    #+#             */
/*   Updated: 2026/01/15 18:17:46 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	end_simulation(char *err_msg, t_table *table)
{
	free_philo(table);
	free_locks(table);
	free(table);
	if (err_msg)
		printf("%s\n", err_msg);
}


int	main(int ac, char **av)
{
	t_table *table = NULL;
	int		i;
	
	if (ac < 5 || ac > 6)
		msg_err(ERR_ARGS);
	if (!is_valid(ac, av))
		return (EXIT_FAILURE);
	table = init(ac, av, table);
	if (table->nb_philo == 1)
	{
		if (pthread_create(&table->philo[0]->philo_tid, NULL, mims_routine, table->philo[0]))
			end_simulation(ERR_PHILO_TRHD, table);
		pthread_join(table->philo[0]->philo_tid, NULL);
	}
	else
		multi_thread(table);
	i = 0;
	end_simulation(NULL, table);
	return (EXIT_SUCCESS);
}
