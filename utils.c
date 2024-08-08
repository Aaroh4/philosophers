/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:40:29 by ahamalai          #+#    #+#             */
/*   Updated: 2024/03/28 14:40:57 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	overflowfix(int neg)
{
	if (neg == 1)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long int	ret;
	long int	old_ret;
	int			neg;

	neg = 1;
	ret = 0;
	while (*str == ' ' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f' || *str == '\t')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str <= '9' && *str >= '0')
	{
		old_ret = ret;
		ret = ret * 10 + (*str - 48);
		if (old_ret > ret)
			return (overflowfix(neg));
		str++;
	}
	return ((int)ret * neg);
}

long long int	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		printf("CHANGE ME!!!!!!!");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_messaging(int i, t_philos *philo)
{
	long long int	milliseconds;
	long long int	start;

	start = philo->data->start_time;
	pthread_mutex_lock(&(philo->data->lock));
	milliseconds = ft_get_time() - start;
	if (i == 1 && philo->data->dead == 1)
		printf("%lld %d has taken a fork\n", milliseconds, philo->id);
	else if (i == 2 && philo->data->dead == 1)
		printf("%lld %d is eating\n", milliseconds, philo->id);
	else if (i == 3 && philo->data->dead == 1)
		printf("%lld %d is sleeping\n", milliseconds, philo->id);
	else if (i == 4 && philo->data->dead == 1)
		printf("%lld %d is thinking\n", milliseconds, philo->id);
	else if (i == 5 && philo->data->dead == 1)
	{
		if (!philo->data->dead)
		{
			pthread_mutex_unlock(&(philo->data->lock));
			return ;
		}
		philo->data->dead = 0;
		printf("%lld %d died\n", milliseconds, philo->id);
	}
	pthread_mutex_unlock(&(philo->data->lock));
}
