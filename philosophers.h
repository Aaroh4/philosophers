/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamalai <ahamalai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:52:04 by ahamalai          #+#    #+#             */
/*   Updated: 2024/03/28 15:16:34 by ahamalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_philos
{
	struct s_data				*data;
	int							id;
	int							fork;
	long long int				hunger;
	long long int				hunger2;
	int							eating;
	int							times_eaten;
	pthread_mutex_t				*l_fork;
	pthread_mutex_t				*r_fork;
	pthread_t					thread;
	pthread_mutex_t				lock;
}	t_philos;

typedef struct s_data
{
	t_philos		*philos;
	int				philo_num;
	pthread_mutex_t	*forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				dead;
	int				first;
	int				eaten;
	int				eat_number;
	pthread_t		monitor;
	pthread_mutex_t	lock;
	long long int	start_time;
}	t_data;

int				ft_atoi(const char *str);
int				ft_init_forks(t_data *data);
int				ft_initialize_philo(t_data *data);
int				ft_initialize_data(t_data *data, char **argv, int argc);
void			ft_messaging(int i, t_philos *philo);
long long int	ft_get_time(void);
void			ft_free(t_data *data, int i);
void			ft_monitor_thread(t_data *data);
void			*ft_living_philo(void *arg);

#endif