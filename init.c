/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:42:26 by ahamalai          #+#    #+#             */
/*   Updated: 2024/04/01 11:49:49 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
	if (!data->forks)
	{
		ft_free(data, 2);
		write(2, "Error: Malloc failed\n", 21);
		return (1);
	}
	while (i < data->philo_num)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 1;
	data->philos[0].l_fork = &data->forks[data->philo_num - 1];
	data->philos[0].r_fork = &data->forks[0];
	while (i < data->philo_num)
	{
		data->philos[i].l_fork = &data->forks[i - 1];
		data->philos[i].r_fork = &data->forks[i];
		i++;
	}
	return (0);
}

int	ft_initialize_data(t_data *data, char **argv, int argc)
{
	data->philo_num = ft_atoi(argv[1]);
	if (data->philo_num <= 0)
		return (1);
	data->time_to_die = ft_atoi(argv[2]);
	if (data->time_to_die <= 0)
		return (1);
	data->time_to_eat = ft_atoi(argv[3]);
	if (data->time_to_eat <= 0)
		return (1);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_sleep <= 0)
		return (1);
	if (argc == 6)
	{
		data->eat_number = ft_atoi(argv[5]);
		if (data->eat_number <= 0)
			return (1);
	}
	else
		data->eat_number = -1;
	data->dead = 1;
	data->first = 1;
	data->eaten = 0;
	pthread_mutex_init(&data->lock, NULL);
	return (0);
}

int	ft_initialize_philo(t_data *data)
{
	int	i;

	i = -1;
	data->philos = malloc(sizeof(t_philos) * data->philo_num);
	if (!data->philos)
	{
		pthread_mutex_destroy(&data->lock);
		write(2, "Error: Malloc failed\n", 21);
		return (1);
	}
	while (++i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		data->philos[i].fork = 1;
		data->philos[i].eating = 0;
		data->philos[i].hunger = 1;
		data->philos[i].hunger2 = -1;
		data->philos[i].thread = NULL;
		data->philos[i].times_eaten = 0;
		pthread_mutex_init(&data->philos[i].lock, NULL);
	}
	if (ft_init_forks(data) == 1)
		return (1);
	return (0);
}
