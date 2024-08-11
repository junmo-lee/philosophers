/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:03:12 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/11 17:22:02 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main_parsing(t_vars *vars, int argc, char **argv)
{
	memset(vars, 0, sizeof(t_vars));
	if (atoi_check_num(argv[1], &(vars->num_philo)) == 0)
		return (EXIT_FAILURE);
	else if (atoi_check_num(argv[2], &(vars->utime_die)) == 0)
		return (EXIT_FAILURE);
	else if (atoi_check_num(argv[3], &(vars->utime_eat)) == 0)
		return (EXIT_FAILURE);
	else if (atoi_check_num(argv[4], &(vars->utime_sleep)) == 0)
		return (EXIT_FAILURE);
	if (vars->num_philo <= 0 || vars->utime_die < 0 || vars->utime_eat < 0 || vars->utime_sleep < 0)
		return (EXIT_FAILURE);
	if (vars->utime_die > USLEEP_MAX || vars->utime_eat > USLEEP_MAX || vars->utime_sleep > USLEEP_MAX)
		return (EXIT_FAILURE);
	if (argc == 6)
	{
		if (atoi_check_num(argv[5], &(vars->num_req_eat)) == 0)
			return (EXIT_FAILURE);
		if (vars->num_req_eat <= 0)
			return (EXIT_FAILURE);
	}
	else
		vars->num_req_eat = 0;
	vars->utime_die *= MSEC_TO_USEC;
	vars->utime_eat *= MSEC_TO_USEC;
	vars->utime_sleep *= MSEC_TO_USEC;
	return (EXIT_SUCCESS);
}

int	monitoring(t_vars *vars, t_philo *philo)
{
	int		i;
	int		is_end;
	long	utime;

	is_end = 0;
	while (is_end == 0)
	{
		utime = get_utime();
		if (vars->num_req_eat != 0)
		{
			pthread_mutex_lock(&(vars->check_eat));
			if (vars->num_philo == vars->finished_eat)
			{
				is_end = 1;
				pthread_mutex_unlock(&(vars->check_eat));
				break ;
			}
			pthread_mutex_unlock(&(vars->check_eat));
		}
		
		if (is_end == 0)
		{
			i = 0;
			while (i < vars->num_philo)
			{
				t_philo *temp = philo + i;
				pthread_mutex_lock(vars->check_time + i);
				if ((utime - temp->utime_last_eat) > vars->utime_die)
				{
					philo_print(vars->start_time, i + 1, "died");
					is_end = 1;
					pthread_mutex_unlock(vars->check_time + i);
					break ;
				}
				pthread_mutex_unlock(vars->check_time + i);
				i++;
			}
		}
		usleep(100);
	}
	pthread_mutex_lock(&(vars->check_end));
	vars->is_finish = 1;
	pthread_mutex_unlock(&(vars->check_end));
	return (0);
}

int	wait_philo(t_vars *vars, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < vars->num_philo)
	{
		pthread_join((philo + i)->thread, NULL);
		i++;
	}
	usleep(10);
	return (0);
}

int	make_philo(t_vars *vars, t_philo *philo)
{
	int i = 0;
	vars->start_time = get_utime();
	if (vars->num_philo == 1)
	{
		philo->utime_start = vars->start_time + SEC_TO_USEC;
		philo->utime_last_eat = vars->start_time + SEC_TO_USEC;
		if (pthread_create(&(philo->thread), NULL, thread_solo_philo, philo))
            return (EXIT_FAILURE);
		return (0);
	}
	while (i < vars->num_philo)
	{
		(philo + i)->utime_start = vars->start_time + SEC_TO_USEC;
		(philo + i)->utime_last_eat = vars->start_time + SEC_TO_USEC;
		if (i % 2 == 0)
		{
	        if (pthread_create(&((philo + i)->thread), NULL, thread_odd_philo, philo + i))
	            return (EXIT_FAILURE);
		}
		else
		{
	        if (pthread_create(&((philo + i)->thread), NULL, thread_even_philo, philo + i))
	            return (EXIT_FAILURE);
		}
		usleep(2);
		i++;
	}
	return (0);
}

int	main_free(t_vars *vars, t_philo *philos)
{
	if (vars->forks != NULL)
	{
		// memset(vars->forks, 0, sizeof(vars->forks) * vars->num_philo);
		free(vars->forks);
	}
	if (philos != NULL)
	{
		// memset(vars->forks, 0, sizeof(vars->forks) * vars->num_philo);
		free(philos);
	}
	return (0);
}

void	f(void)
{
	system("leaks philo");
}

int main(int argc, char **argv)
{
	t_vars	vars;
	t_philo	*philos;

	// atexit(f);
	if (argc != 5 && argc != 6)
	{
		printf("only 4 or 5 arg\n");
		return (EXIT_FAILURE);
	}
	if (main_parsing(&vars, argc, argv) == EXIT_FAILURE)
	{
		printf("invalid argument\n");
		return (EXIT_FAILURE);
	}
	// printf("%d %d %d %d %d\n", vars.num_philo, vars.utime_die, vars.utime_eat, vars.utime_sleep, vars.num_req_eat);

	init_philo(&vars, &philos);
	make_philo(&vars, philos);
	monitoring(&vars, philos);
	wait_philo(&vars, philos);
	main_free(&vars, philos);
	return (EXIT_SUCCESS);
}