/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:03:12 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/12 17:10:38 by junmlee          ###   ########.fr       */
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
	if (vars->num_philo <= 0 || vars->utime_die < 0 \
		|| vars->utime_eat < 0 || vars->utime_sleep < 0)
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

int	main_free(t_vars *vars, t_philo *philos)
{
	if (vars->forks != NULL)
	{
		memset(vars->forks, 0, sizeof(int) * vars->num_philo);
		free(vars->forks);
	}
	if (vars->mutex_fork != NULL)
	{
		memset(vars->mutex_fork, 0, sizeof(pthread_mutex_t) * vars->num_philo);
		free(vars->mutex_fork);
	}
	if (vars->check_time != NULL)
	{
		memset(vars->check_time, 0, sizeof(pthread_mutex_t) * vars->num_philo);
		free(vars->check_time);
	}
	if (philos != NULL)
	{
		memset(philos, 0, sizeof(t_philo) * vars->num_philo);
		free(philos);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_philo	*philos;

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
	init_philo(&vars, &philos);
	if (vars.num_philo == 1)
		solo_init(&vars, philos);
	else
		make_other_philo(&vars, philos);
	monitoring(&vars, philos);
	wait_philo(&vars, philos);
	main_free(&vars, philos);
	return (EXIT_SUCCESS);
}
