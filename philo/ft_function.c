/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junmlee <junmlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:25:15 by junmlee           #+#    #+#             */
/*   Updated: 2024/08/11 22:17:13 by junmlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_nbr(int n, int fd)
{
	const char	*base = "0123456789";

	if (n >= 10)
		put_nbr(n / 10, fd);
	write(fd, base + (n % 10), 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	put_nbr(n, fd);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	atoi_check_num(const char *str, int *target)
{
	long long	ret;
	int			sign;

	sign = 1;
	ret = 0;
	while (*str != '\0' && *str == ' ')
		str++;
	if (*str == '-' && ('0' <= *(str + 1) && *(str + 1) <= '9'))
	{
		sign = -1;
		str++;
	}
	else if (*str == '+' && ('0' <= *(str + 1) && *(str + 1) <= '9'))
		str++;
	while (*str != '\0' && *str != ' ')
	{
		if (*str < '0' || *str > '9')
			return (0);
		ret *= 10;
		ret += *str - '0';
		str++;
	}
	*target = sign * ret;
	return (1);
}
