/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:12:47 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/12 17:18:27 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_philo(t_vars *vars, t_philo *philo)
{
	int	i;

	vars->start_time = get_utime();
	i = 0;
	while (i < vars->num_philo)
	{
		(philo + i)->utime_start = vars->start_time + SEC_TO_USEC;
		(philo + i)->utime_last_eat = vars->start_time + SEC_TO_USEC;
		if (i % 2 == 0)
		{
			if (pthread_create(&((philo + i)->thread), \
				NULL, thread_odd_philo, philo + i))
				return (EXIT_FAILURE);
		}
		else
		{
			if (pthread_create(&((philo + i)->thread), \
				NULL, thread_even_philo, philo + i))
				return (EXIT_FAILURE);
		}
		usleep(2);
		i++;
	}
	return (0);
}
