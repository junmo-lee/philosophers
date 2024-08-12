/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 22:27:38 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/12 16:31:26 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_philo(t_vars *vars, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < vars->num_philo)
	{
		(philo + i)->vars = vars;
		(philo + i)->id = i + 1;
		(philo + i)->left = i;
		if (i + 1 != vars->num_philo)
			(philo + i)->right = i + 1;
		else
			(philo + i)->right = 0;
		(philo + i)->cnt_eat = 0;
		(philo + i)->utime_last_eat = 0;
		(philo + i)->utime_start = 0;
		i++;
	}
}

int	set_mutex(t_vars *vars)
{
	int	i;

	if (pthread_mutex_init(&(vars->check_eat), NULL))
		return (1);
	if (pthread_mutex_init(&(vars->check_end), NULL))
		return (1);
	i = 0;
	while (i < vars->num_philo)
	{
		if (pthread_mutex_init(&(vars->mutex_fork[i]), NULL))
			return (1);
		if (pthread_mutex_init((vars->check_time + i), NULL))
			return (1);
		i++;
	}
	return (0);
}

int	i_sqrt(int num)
{
	int	ret;

	ret = 0;
	while (ret * ret < num)
		ret++;
	return (ret);
}

int	init_philo(t_vars *vars, t_philo **philo)
{
	*philo = malloc(sizeof(t_philo) * (vars->num_philo));
	if (*philo == NULL)
		return (EXIT_FAILURE);
	set_philo(vars, *philo);
	vars->forks = malloc(sizeof(int) * vars->num_philo);
	if (vars->forks == NULL)
		return (1);
	memset(vars->forks, 0, sizeof(int) * vars->num_philo);
	vars->mutex_fork = malloc(sizeof(pthread_mutex_t) * vars->num_philo);
	if (vars->mutex_fork == NULL)
		return (1);
	vars->check_time = malloc(sizeof(pthread_mutex_t) * vars->num_philo);
	if (vars->check_time == NULL)
		return (1);
	if (set_mutex(vars) == 1)
		return (1);
	vars->bias = 5 * (i_sqrt(vars->num_philo)) + 50;
	return (EXIT_SUCCESS);
}

int	solo_init(t_vars *vars, t_philo *philo)
{
	philo->utime_start = vars->start_time + SEC_TO_USEC;
	philo->utime_last_eat = vars->start_time + SEC_TO_USEC;
	if (pthread_create(&(philo->thread), NULL, thread_solo_philo, philo))
		return (EXIT_FAILURE);
	return (0);
}
