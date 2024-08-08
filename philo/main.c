/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:03:12 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/08 19:21:35 by junmlee          ###   ########.fr       */
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



int	make_philo(t_vars *vars, t_philo *philo)
{
	int i = 0;
	vars->start_time = get_utime();
	while (i < vars->num_philo)
	{
		philo[i].utime_start = vars->start_time + SEC_TO_USEC;
		philo[i].utime_last_eat = vars->start_time + SEC_TO_USEC;
        if (pthread_create(&(philo[i].thread), NULL, thread_philo, &(philo[i])))
            return (EXIT_FAILURE);
		usleep(2);
		i++;
	}

	// 나중에 모니터링 구현
	while (1)
	{
		usleep(1000);
	}
	return (0);
}



int main(int argc, char **argv)
{
	t_vars	vars;
	t_philo	*philos;

	memset(&vars, 0, sizeof(t_vars));
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
	printf("%d %d %d %d %d\n", vars.num_philo, vars.utime_die, vars.utime_eat, vars.utime_sleep, vars.num_req_eat);

	init_philo(&vars, &philos);
	make_philo(&vars, philos);
	return (EXIT_SUCCESS);
}