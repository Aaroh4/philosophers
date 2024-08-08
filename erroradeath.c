/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erroradeath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:52:14 by ahamalai          #+#    #+#             */
/*   Updated: 2024/03/28 15:42:35 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_monitoring(void *pointer)
{
	t_data	*data;
	int		i;

	data = (t_data *) pointer;
	i = 0;
	while (data->dead == 1)
	{
		while (i < data->philo_num)
		{
			if (data->eaten == data->philo_num)
			{
				pthread_mutex_lock(&data->lock);
				data->dead = 0;
				pthread_mutex_unlock(&data->lock);
			}
			if (ft_get_time() > data->philos[i].hunger
				&& data->philos[i].eating == 0)
				ft_messaging(5, &data->philos[i]);
			i++;
		}
		i = 0;
	}
	pthread_exit(NULL);
}

void	ft_monitor_thread(t_data *data)
{
	int	i;

	pthread_create(&data->monitor, NULL, ft_monitoring, (void *)data);
	i = 0;
	while (i++ < data->philo_num)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(data->monitor, NULL);
	ft_free(data, 1);
}

void	ft_free(t_data *data, int i)
{
	int	j;

	j = 0;
	if (i == 1)
	{
		free(data->philos);
		free(data->forks);
	}
	if (i == 2)
		free(data->philos);
	pthread_mutex_destroy(&data->lock);
	while (j < data->philo_num)
	{
		pthread_mutex_destroy(&data->philos[i].lock);
		j++;
	}
}
