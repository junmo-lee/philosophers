/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:58:51 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/12 17:17:39 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_solo_philo(void *argv)
{
	t_philo			*philo;
	t_vars			*vars;

	philo = argv;
	vars = philo->vars;
	while (get_utime() - vars->start_time < SEC_TO_USEC)
		usleep(100);
	philo_solo_eat(philo);
	while (1)
	{
		pthread_mutex_lock(&(vars->check_end));
		if (vars->is_finish == 1)
		{
			pthread_mutex_unlock(&(vars->check_end));
			return (0);
		}
		pthread_mutex_unlock(&(vars->check_end));
		usleep(100);
	}
	return (0);
}

int	philo_solo_eat(t_philo *philo)
{
	t_vars	*vars;

	vars = philo->vars;
	pthread_mutex_lock(&(vars->mutex_fork[philo->left]));
	vars->forks[philo->left] = 1;
	philo_print(vars->start_time, philo->id, "has taken a fork");
	vars->forks[philo->left] = 0;
	pthread_mutex_unlock(&(vars->mutex_fork[philo->left]));
	return (0);
}
