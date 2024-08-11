/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:08:58 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/11 17:23:32 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void    *thread_odd_philo(void *argv)
{
    t_philo       	*philo;
	t_vars			*vars;

    philo = argv;
	vars = philo->vars;
	while (get_utime() - vars->start_time < SEC_TO_USEC)
	{
		usleep(100);
	}
    while (1)
    {
		pthread_mutex_lock(&(vars->check_end));
		if (vars->is_finish == 1)
		{
			pthread_mutex_unlock(&(vars->check_end));
			return (0);
		}
		pthread_mutex_unlock(&(vars->check_end));

		philo_odd_eat(philo);
		
		if (vars->num_req_eat != 0)
		{
			pthread_mutex_lock(&(vars->check_eat));
	        if (vars->num_req_eat == philo->cnt_eat)
	        {
	            vars->finished_eat += 1;
				pthread_mutex_unlock(&(vars->check_eat));
				philo_print(vars->start_time, philo->id, "is sleeping");
	            break ;
	        }
			pthread_mutex_unlock(&(vars->check_eat));
		}
		
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

	vars = philo->vars;
	pthread_mutex_lock(&(vars->forks[philo->left]));

	philo_print(vars->start_time, philo->id, "has taken a fork");

	pthread_mutex_lock(&(vars->forks[philo->right]));

	philo_print(vars->start_time, philo->id, "has taken a fork");
	philo_print(vars->start_time, philo->id, "is eating");
	pthread_mutex_lock(vars->check_time + philo->id - 1);

	philo->utime_last_eat = get_utime();

	pthread_mutex_unlock(vars->check_time + philo->id - 1);

	if (spend_utime(vars->utime_eat, vars) == 1)
	{
		pthread_mutex_unlock(&(vars->forks[philo->left]));
		pthread_mutex_unlock(&(vars->forks[philo->right]));
		return (0);
	}
	pthread_mutex_unlock(&(vars->forks[philo->left]));
	pthread_mutex_unlock(&(vars->forks[philo->right]));
	philo->cnt_eat++;

	return (0);
}
void    *thread_even_philo(void *argv)
{
    t_philo       	*philo;
	t_vars			*vars;

    philo = argv;
	vars = philo->vars;
	while (get_utime() - vars->start_time < SEC_TO_USEC)
	{
		usleep(100);
	}
	if (spend_utime(vars->utime_eat, vars) == 1)
		return (0);
    while (1)
    {
		pthread_mutex_lock(&(vars->check_end));
		if (vars->is_finish == 1)
		{
			pthread_mutex_unlock(&(vars->check_end));
			return (0);
		}
		pthread_mutex_unlock(&(vars->check_end));

		philo_even_eat(philo);
		if (vars->num_req_eat != 0)
		{
			pthread_mutex_lock(&(vars->check_eat));
	        if (vars->num_req_eat == philo->cnt_eat)
	        {
	            vars->finished_eat += 1;
				pthread_mutex_unlock(&(vars->check_eat));
				philo_print(vars->start_time, philo->id, "is sleeping");
	            break ;
	        }
			pthread_mutex_unlock(&(vars->check_eat));
		}
		
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

	vars = philo->vars;

	pthread_mutex_lock(&(vars->forks[philo->left]));
	philo_print(vars->start_time, philo->id, "has taken a fork");

	pthread_mutex_lock(&(vars->forks[philo->right]));

	philo_print(vars->start_time, philo->id, "has taken a fork");
	philo_print(vars->start_time, philo->id, "is eating");
	pthread_mutex_lock(vars->check_time + philo->id - 1);

	philo->utime_last_eat = get_utime();

	pthread_mutex_unlock(vars->check_time + philo->id - 1);
	if (spend_utime(vars->utime_eat, vars) == 1)
	{
		pthread_mutex_unlock(&(vars->forks[philo->right]));
		pthread_mutex_unlock(&(vars->forks[philo->left]));
		return (0);
	}
	pthread_mutex_unlock(&(vars->forks[philo->right]));
	pthread_mutex_unlock(&(vars->forks[philo->left]));
	philo->cnt_eat++;

	return (0);
}

void    *thread_solo_philo(void *argv)
{
    t_philo       	*philo;
	t_vars			*vars;

    philo = argv;
	vars = philo->vars;
	while (get_utime() - vars->start_time < SEC_TO_USEC)
	{
		usleep(100);
	}
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
	pthread_mutex_lock(&(vars->forks[philo->left]));
	philo_print(vars->start_time, philo->id, "has taken a fork");
	pthread_mutex_unlock(&(vars->forks[philo->left]));
	return (0);
}