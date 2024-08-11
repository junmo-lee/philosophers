#include "philo.h"


int	init_philo(t_vars *vars, t_philo **philo)
{
	int i;


	*philo = malloc(sizeof(t_philo) * (vars->num_philo));
	if (*philo == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (i < vars->num_philo)
	{
		(*philo + i)->vars = vars;
		(*philo + i)->id = i + 1;
		(*philo + i)->left = i;
		if (i + 1 != vars->num_philo)
			(*philo + i)->right = i + 1;
		else
			(*philo + i)->right = 0;
		(*philo + i)->cnt_eat = 0;
		(*philo + i)->utime_last_eat = 0;
		(*philo + i)->utime_start = 0;
		i++;
	}

	if (pthread_mutex_init(&(vars->check_eat), NULL))
		return (1);
	if (pthread_mutex_init(&(vars->check_end), NULL))
		return (1);

	vars->forks = malloc(sizeof(pthread_mutex_t) * vars->num_philo);
	if (vars->forks == NULL)
		return (1);
	vars->check_time = malloc(sizeof(pthread_mutex_t) * vars->num_philo);
	if (vars->check_time == NULL)
		return (1);
	i = 0;
	while (i < vars->num_philo)
	{
		if (pthread_mutex_init((vars->forks + i), NULL))
			return (1);
		if (pthread_mutex_init((vars->check_time + i), NULL))
			return (1);
		i++;
	}
	return (EXIT_SUCCESS);
}