/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:08:58 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/12 16:44:00 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_odd_philo(void *argv)
{
	t_philo			*philo;
	t_vars			*vars;

	philo = argv;
	vars = philo->vars;
	while (get_utime() - vars->start_time < SEC_TO_USEC)
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

int	philo_odd_eat(t_philo *philo)
{
	t_vars	*vars;
	int		ret;

	vars = philo->vars;
	pthread_mutex_lock(&(vars->mutex_fork[philo->left]));
	vars->forks[philo->left] = 1;
	philo_print(vars->start_time, philo->id, "has taken a fork");
	pthread_mutex_lock(&(vars->mutex_fork[philo->right]));
	vars->forks[philo->right] = 1;
	philo_print(vars->start_time, philo->id, "has taken a fork");
	philo_print(vars->start_time, philo->id, "is eating");
	pthread_mutex_lock(vars->check_time + philo->id - 1);
	philo->utime_last_eat = get_utime();
	pthread_mutex_unlock(vars->check_time + philo->id - 1);
	ret = spend_utime(vars->utime_eat, vars);
	vars->forks[philo->right] = 0;
	pthread_mutex_unlock(&(vars->mutex_fork[philo->right]));
	vars->forks[philo->left] = 0;
	pthread_mutex_unlock(&(vars->mutex_fork[philo->left]));
	if (ret == 0)
		philo->cnt_eat++;
	return (ret);
}

void	*thread_even_philo(void *argv)
{
	t_philo			*philo;
	t_vars			*vars;

	philo = argv;
	vars = philo->vars;
	while (get_utime() - vars->start_time < SEC_TO_USEC)
		usleep(100);
	philo_print(vars->start_time, philo->id, "is thinking");
	if (spend_utime(vars->utime_eat, vars) == 1)
		return (0);
	while (1)
	{
		if (check_is_finish(vars) == 1)
			return (0);
		if (philo_even_eat(philo) == 1)
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

int	philo_even_eat(t_philo *philo)
{
	t_vars	*vars;
	int		ret;

	vars = philo->vars;
	pthread_mutex_lock(&(vars->mutex_fork[philo->left]));
	philo_print(vars->start_time, philo->id, "has taken a fork");
	vars->forks[philo->right] = 1;
	pthread_mutex_lock(&(vars->mutex_fork[philo->right]));
	vars->forks[philo->left] = 1;
	philo_print(vars->start_time, philo->id, "has taken a fork");
	philo_print(vars->start_time, philo->id, "is eating");
	pthread_mutex_lock(vars->check_time + philo->id - 1);
	philo->utime_last_eat = get_utime();
	pthread_mutex_unlock(vars->check_time + philo->id - 1);
	ret = spend_utime(vars->utime_eat, vars);
	pthread_mutex_unlock(&(vars->mutex_fork[philo->right]));
	vars->forks[philo->left] = 0;
	vars->forks[philo->right] = 0;
	pthread_mutex_unlock(&(vars->mutex_fork[philo->left]));
	if (ret == 0)
		philo->cnt_eat++;
	return (ret);
}
