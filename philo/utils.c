#include "philo.h"

long	get_utime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * SEC_TO_USEC) + time.tv_usec);
}

int	spend_utime(long wait_utime, t_vars *vars)
{
	long	start_utime;

	start_utime = get_utime() - 50;
	while (get_utime() < start_utime + wait_utime)
	{
		pthread_mutex_lock(&(vars->check_end));
		if (vars->is_finish == 1)
		{
			pthread_mutex_unlock(&(vars->check_end));
			return (1);
		}
		pthread_mutex_unlock(&(vars->check_end));
		usleep(100);
	}
	return (0);
}

void	sleep_until_even_eat(t_vars *vars)
{
	long	start_time;

	start_time = get_utime();
	while (1)
	{
		if (get_utime() - start_time > vars->utime_eat)
			break ;
		usleep(vars->utime_eat);
	}
}

int	philo_print(long start_time, int id, const char *str)
{
	printf("%ld %d %s\n", ((get_utime() - start_time - SEC_TO_USEC) / MSEC_TO_USEC), id, str);
	// ft_putnbr_fd((int)(get_utime() / 1000), STDOUT_FILENO);
	// write(STDOUT_FILENO, " ", 1);
	// ft_putnbr_fd(id, STDOUT_FILENO);
	// write(STDOUT_FILENO, " ", 1);
	// write(STDOUT_FILENO, str, ft_strlen(str));
	return (0);
}