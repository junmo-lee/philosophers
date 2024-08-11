/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:02:00 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/09 18:52:42 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// 허용 함수
// memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_vars
{
	int				num_philo;
	int				utime_die;
	int				utime_eat;
	int				utime_sleep;
	int				num_req_eat;
	int				is_finish;
	int				finished_eat;
	long 			start_time;
	// int	monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*check_time;
	pthread_mutex_t	check_eat;
	pthread_mutex_t	check_end;
}	t_vars;

typedef struct s_philo
{
	t_vars		*vars;
	pthread_t	thread;
	int			id;
	int			left;
	int			right;
	int			cnt_eat;
	long		utime_last_eat;
	long		utime_start;
}	t_philo;

# define SEC_TO_USEC 1000000
# define MSEC_TO_USEC 1000
# define START_USEC 1000000

# define USLEEP_MAX (int)(UINT32_MAX/MSEC_TO_USEC)

int	atoi_check_num(const char *str, int *target);
void	ft_putnbr_fd(int n, int fd);
int	ft_strlen(const char *str);

long	get_utime(void);
int		spend_utime(long wait_utime, t_vars *arg);
int	init_philo(t_vars *vars, t_philo **philo);
int	philo_print(long start_time, int id, const char *str);

void	sleep_until_even_eat(t_vars *vars);

void    *thread_odd_philo(void *argv);
void    *thread_solo_philo(void *argv);
void    *thread_even_philo(void *argv);
int	philo_even_eat(t_philo *philo);
int	philo_odd_eat(t_philo *philo);
int	philo_solo_eat(t_philo *philo);

#endif