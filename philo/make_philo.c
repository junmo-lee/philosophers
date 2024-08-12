/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:12:47 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/12 14:54:25 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	make_philo(t_vars *vars, t_philo *philo)
{
	vars->start_time = get_utime();
	if (vars->num_philo == 1)
		return (solo_init(vars, philo));
	return (make_other_philo(vars, philo));
}

int	make_other_philo(t_vars *vars, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < vars->num_philo - 1)
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
		usleep(100);
		i++;
	}
	return (make_last_philo(vars, philo));
}

int	make_last_philo(t_vars *vars, t_philo *philo)
{
	int	i;

	i = vars->num_philo - 1;
	(philo + i)->utime_start = vars->start_time + SEC_TO_USEC;
	(philo + i)->utime_last_eat = vars->start_time + SEC_TO_USEC;
	if (i % 2 == 0)
	{
		if (pthread_create(&((philo + i)->thread), \
			NULL, thread_last_odd_philo, philo + i))
			return (EXIT_FAILURE);
	}
	else
	{
		if (pthread_create(&((philo + i)->thread), \
			NULL, thread_even_philo, philo + i))
			return (EXIT_FAILURE);
	}
	return (0);
}
