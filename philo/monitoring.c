/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:05:52 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/12 13:47:11 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_die(t_vars *vars, t_philo *philo, long utime)
{
	int		i;
	t_philo	*temp;

	i = 0;
	while (i < vars->num_philo)
	{
		temp = philo + i;
		pthread_mutex_lock(vars->check_time + i);
		if ((utime - temp->utime_last_eat) > vars->utime_die)
		{
			philo_print(vars->start_time, i + 1, "died");
			pthread_mutex_unlock(vars->check_time + i);
			return (1);
		}
		pthread_mutex_unlock(vars->check_time + i);
		i++;
	}
	return (0);
}

int	monitoring(t_vars *vars, t_philo *philo)
{
	long	utime;

	while (1)
	{
		utime = get_utime();
		if (vars->num_req_eat != 0)
		{
			pthread_mutex_lock(&(vars->check_eat));
			if (vars->num_philo == vars->finished_eat)
			{
				pthread_mutex_unlock(&(vars->check_eat));
				break ;
			}
			pthread_mutex_unlock(&(vars->check_eat));
		}
		if (check_philo_die(vars, philo, utime) == 1)
			break ;
		usleep(100);
	}
	pthread_mutex_lock(&(vars->check_end));
	vars->is_finish = 1;
	pthread_mutex_unlock(&(vars->check_end));
	return (0);
}
