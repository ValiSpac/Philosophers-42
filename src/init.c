/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:00:32 by vpac              #+#    #+#             */
/*   Updated: 2023/05/13 15:49:45 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	wait_death(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->nb_philo + 1)
	{
		if (i == data->nb_philo)
			i = 0;
		if (data->philo[i].data->death_check)
			{
				i = -1;
				while (++i < data->nb_philo)
					data->philo[i].data->death_check = 1;
				break;
			}
		i++;
	}
}

void	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		data->philo[i].num = i;
		data->philo[i].count = 0;
		data->philo[i].data = data;
		data->philo[i].last_eat = 0;
	}
	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_create(&data->philo[i].thread, NULL,
			philo_control, &data->philo[i]);
	}
	i = -1;
	wait_death(data);
	while (++i < data->nb_philo)
		pthread_join(data->philo[i].thread, NULL);
}

void	init_data(t_data *data, int ac, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_death = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->start_time = gettime();
	data->death_check = 0;
	data->count = 0;
	pthread_mutex_init(&(data->death_mutex), NULL);
	pthread_mutex_init(&(data->eat_mutex), NULL);
	pthread_mutex_init(&(data->print_mutex), NULL);
	if (ac == 6)
		data->nb_eat = ft_atoi(argv[5]);
	else
		data->nb_eat = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!(data->philo))
		return ;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!(data->fork))
		return ;
}
