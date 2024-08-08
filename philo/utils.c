#include "philo.h"

long	get_utime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	return ((time.tv_sec * SEC_TO_USEC) + time.tv_usec);
}

void	spend_utime(long wait_utime, t_vars *arg)
{
	long	u_time;
	long	target_utime;

	u_time = get_utime();
	target_utime = u_time + wait_utime;
	while (arg->is_finish != 0 && u_time > target_utime)
	{
		u_time += get_utime();
		usleep(100);
	}
}

void	sleep_until_even_eat(t_vars *vars)
{
	long	start_time;

	start_time = get_utime() - 100;
	while (1)
	{
		if (get_utime() - start_time > vars->utime_eat)
			break ;
		usleep(vars->utime_eat);
	}
}

int	philo_print(t_vars *vars, int id, const char *str)
{
	printf("%d %d %s\n", (int)((get_utime() - vars->start_time) / MSEC_TO_USEC), id, str);
	// ft_putnbr_fd((int)(get_utime() / 1000), STDOUT_FILENO);
	// write(STDOUT_FILENO, " ", 1);
	// ft_putnbr_fd(id, STDOUT_FILENO);
	// write(STDOUT_FILENO, " ", 1);
	// write(STDOUT_FILENO, str, ft_strlen(str));
	return (0);
}