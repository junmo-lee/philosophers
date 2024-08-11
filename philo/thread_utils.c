/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:11:35 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/11 22:10:14 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_is_finish(t_vars *vars)
{
	pthread_mutex_lock(&(vars->check_end));
	if (vars->is_finish == 1)
	{
		pthread_mutex_unlock(&(vars->check_end));
		return (1);
	}
	pthread_mutex_unlock(&(vars->check_end));
	return (0);
}

int	check_philo_eat(t_vars *vars, t_philo *philo)
{
	pthread_mutex_lock(&(vars->check_eat));
	if (vars->num_req_eat == philo->cnt_eat)
	{
		vars->finished_eat += 1;
		pthread_mutex_unlock(&(vars->check_eat));
		philo_print(vars->start_time, philo->id, "is sleeping");
		return (1);
	}
	pthread_mutex_unlock(&(vars->check_eat));
	return (0);
}
