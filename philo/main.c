/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:10:34 by maleca            #+#    #+#             */
/*   Updated: 2026/01/02 18:06:50 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int ac, char **av)
{
	t_table table;
	
	if (ac < 5 || ac > 6)
		msg_err(ERR_ARGS);
	if (!is_valid(ac, av))
		return (EXIT_FAILURE);
	init(ac, av, &table);
	if (table.nb_philo == 1)
	{
		if (pthread_create(&(&table)->philo[0]->philo_tid, NULL, mims_routine, NULL))
			hdl_err(ERR_PHILO_TRHD, &table);
	}
	else
		multi_thread(&table);
	return (EXIT_SUCCESS);
}
