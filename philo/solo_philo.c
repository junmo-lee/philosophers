/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:58:51 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/11 22:11:36 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	num_philo_is_one(t_vars *vars, t_philo *philo)
{
	philo->utime_start = vars->start_time + SEC_TO_USEC;
	philo->utime_last_eat = vars->start_time + SEC_TO_USEC;
	if (pthread_create(&(philo->thread), NULL, thread_solo_philo, philo))
		return (EXIT_FAILURE);
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
