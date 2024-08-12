/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:58:51 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/12 16:41:12 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_last_odd_philo(void *argv)
{
	t_philo			*philo;
	t_vars			*vars;

	philo = argv;
	vars = philo->vars;
	while (get_utime() - vars->start_time < SEC_TO_USEC)
		usleep(100);
	usleep(100);
	while (1)
	{
		if (check_is_finish(vars) == 1)
			return (0);
		if (philo_odd_eat(philo) == 1)
			return (0);
		if (vars->num_req_eat != 0 && check_philo_eat(vars, philo) == 1)
			return (0);
		philo_print(vars->start_time, philo->id, "is sleeping");
		if (spend_utime(vars->utime_sleep, vars) == 1)
			return (0);
		usleep(philo->id * 10);
		philo_print(vars->start_time, philo->id, "is thinking");
	}
	return (0);
}

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
		if (spend_utime(100, vars) == 1)
			return (0);
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
