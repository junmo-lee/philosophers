/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:58:51 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/12 15:01:19 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	last_odd_philo_front(t_vars *vars, t_philo *philo)
{
	while (get_utime() - vars->start_time < SEC_TO_USEC)
		usleep(100);
	philo_print(vars->start_time, philo->id, "is thinking");
	if (spend_utime(vars->utime_eat + vars->utime_sleep - 100, vars) == 1)
		return (1);
	return (0);
}

void	*thread_last_odd_philo(void *argv)
{
	t_philo			*philo;
	t_vars			*vars;

	philo = argv;
	vars = philo->vars;
	if (last_odd_philo_front(vars, philo) == 1)
		return (0);
	while (1)
	{
		if (check_is_finish(vars) == 1)
			return (0);
		if (philo_odd_eat(philo) == 1)
			return (0);
		if (vars->num_req_eat != 0 && check_philo_eat(vars, philo) == 1)
			return (0);
		philo_print(vars->start_time, philo->id, "is sleeping");
		if (spend_utime(vars->utime_sleep + 50, vars) == 1)
			return (0);
		philo_print(vars->start_time, philo->id, "is thinking");
		if (spend_utime(vars->utime_eat - 50, vars) == 1)
			return (0);
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
	pthread_mutex_lock(&(vars->forks[philo->left].mutex));
	philo_print(vars->start_time, philo->id, "has taken a fork");
	pthread_mutex_unlock(&(vars->forks[philo->left].mutex));
	return (0);
}
