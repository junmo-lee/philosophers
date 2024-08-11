/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:02:00 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/11 22:10:50 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_fork
{
	int				is_take;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_vars
{
	int				num_philo;
	int				utime_die;
	int				utime_eat;
	int				utime_sleep;
	int				num_req_eat;
	int				is_finish;
	int				finished_eat;
	long			start_time;
	t_fork			*forks;
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

int		atoi_check_num(const char *str, int *target);
void	ft_putnbr_fd(int n, int fd);
int		ft_strlen(const char *str);

long	get_utime(void);
int		spend_utime(long wait_utime, t_vars *arg);
int		init_philo(t_vars *vars, t_philo **philo);
int		make_philo(t_vars *vars, t_philo *philo);
int		philo_print(long start_time, int id, const char *str);

void	sleep_until_even_eat(t_vars *vars);

void	*thread_odd_philo(void *argv);
void	*thread_solo_philo(void *argv);
void	*thread_even_philo(void *argv);
int		philo_even_eat(t_philo *philo);
int		philo_odd_eat(t_philo *philo);
int		philo_solo_eat(t_philo *philo);

int		num_philo_is_one(t_vars *vars, t_philo *philo);

int		monitoring(t_vars *vars, t_philo *philo);

int		check_is_finish(t_vars *vars);
int		check_philo_eat(t_vars *vars, t_philo *philo);

#endif