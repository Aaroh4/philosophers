/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:11:04 by ahamalai          #+#    #+#             */
/*   Updated: 2024/04/01 11:47:43 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_take_forks(t_philos *philo)
{
	if (philo->data->philo_num % 2 == 0)
	{
		if (philo->id % 2 == 0)
			pthread_mutex_lock(philo->l_fork);
		else
			pthread_mutex_lock(philo->r_fork);
		ft_messaging(1, philo);
		if (philo->id % 2 == 0)
			pthread_mutex_lock(philo->r_fork);
		else
			pthread_mutex_lock(philo->l_fork);
		ft_messaging(1, philo);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		ft_messaging(1, philo);
		pthread_mutex_lock(philo->r_fork);
		ft_messaging(1, philo);
	}
}

void	ft_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->hunger2 += philo->data->time_to_die
		+ (ft_get_time() - philo->data->start_time);
	philo->hunger = philo->hunger2 + ft_get_time();
	ft_messaging(2, philo);
	usleep(philo->data->time_to_eat * 1000);
	philo->times_eaten++;
	if (philo->times_eaten == philo->data->eat_number)
		philo->data->eaten++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	ft_sleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->lock);
	ft_messaging(3, philo);
	usleep(philo->data->time_to_sleep * 1000);
	pthread_mutex_unlock(&philo->lock);
}

void	*ft_living_philo(void *arg)
{
	t_philos		*philo;

	philo = (t_philos *) arg;
	philo->hunger = philo->data->time_to_die + ft_get_time();
	while (philo->data->dead == 1)
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_sleep(philo);
		ft_messaging(4, philo);
	}
	pthread_exit(NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;

	if (argc < 5 || argc > 6)
		return (1);
	if (ft_initialize_data(&data, argv, argc) == 1)
		return (1);
	if (ft_initialize_philo(&data) == 1)
		return (1);
	data.start_time = ft_get_time();
	i = 0;
	while (i < data.philo_num)
	{
		if (pthread_create(&data.philos[i].thread, NULL
				, ft_living_philo, &data.philos[i]) != 0)
		{
			ft_free(&data, 1);
			write(2, "Error creating thread\n", 22);
			return (1);
		}
		usleep(100);
		i++;
	}
	ft_monitor_thread(&data);
	return (0);
}
