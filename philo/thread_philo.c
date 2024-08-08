/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 18:08:58 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/08 22:14:53 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void    *thread_philo(void *argv)
{
    t_philo       	*philo;
	t_vars			*vars;

    philo = argv;
	vars = philo->vars;
	while (get_utime() - vars->start_time < SEC_TO_USEC)
	{
		usleep(100);
	}
    if (philo->id % 2 == 0)
        spend_utime(vars->utime_eat, vars);
    while (vars->is_finish == 0)
    {
        if (vars->num_philo == philo->id + 1 && philo->cnt_eat == 0)
            usleep(10);
		philo_eat(philo);
		
        // if (vars->num_philo == 1)
        //     spend_utime((long)vars->utime_sleep, vars);
        if (vars->num_req_eat == philo->cnt_eat)
        {
            vars->finished_eat++;
            break ;
        }
        philo_print(vars, philo->id, "is sleeping");
        spend_utime(vars->utime_sleep, vars);
        philo_print(vars, philo->id, "is thinking");
    }
    return (0);
}

int	philo_eat(t_philo *philo)
{
	t_vars	*vars;

	vars = philo->vars;
	pthread_mutex_lock(&(vars->forks[philo->left]));

	philo_print(vars, philo->id, "has taken a fork");
	// if (vars->num_philo != 1)
	// {
		pthread_mutex_lock(&(vars->forks[philo->right]));

		philo_print(vars, philo->id, "has taken a fork");
		philo_print(vars, philo->id, "is eating");
		pthread_mutex_lock(&(vars->time));

		philo->utime_last_eat = get_utime();

		pthread_mutex_unlock(&(vars->time));
		philo->cnt_eat++;
		spend_utime(vars->utime_eat, vars);

		pthread_mutex_unlock(&(vars->forks[philo->right]));
	// }

	pthread_mutex_unlock(&(vars->forks[philo->left]));
	return (0);
}