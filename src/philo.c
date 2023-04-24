/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:13:24 by vpac              #+#    #+#             */
/*   Updated: 2023/04/24 13:11:25 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->secure_fork));
	pthread_mutex_lock(&(philo->data->fork[philo->num]));
	if (!print("has taken a fork", philo))
		return (0);
	if (philo->data->nb_philo == 1)
	{
		my_sleep(philo->data->time_death);
		pthread_mutex_unlock(&(philo->data->fork[philo->num]));
		print("died", philo);
		pthread_mutex_unlock(&(philo->data->secure_fork));
		return (0);
	}
	pthread_mutex_lock(&(philo->data->fork[(philo->num + 1)
			% philo->data->nb_philo]));
	if (!print("has taken a fork", philo))
	{
		pthread_mutex_unlock(&(philo->data->secure_fork));
		return (0);
	}
	return (1);
}

int	death_check(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->death_mutex));
	if (philo->data->death_check)
	{
		pthread_mutex_unlock(&(philo->data->death_mutex));
		return (0);
	}
	pthread_mutex_unlock(&(philo->data->death_mutex));
	if (((gettime() - philo->data->start_time) - philo->last_eat)
		>=	philo->data->time_death)
	{
		print("died", philo);
		return (0);
	}
	return (1);
}

int	eating(t_philo *philo)
{
	if (!print("is eating", philo))
		return (0);
	philo->last_eat = gettime() - philo->data->start_time;
	my_sleep(philo->data->time_eat);
	philo->count++;
	pthread_mutex_unlock(&(philo->data->fork[philo->num]));
	pthread_mutex_unlock(&(philo->data->fork[(philo->num + 1)
					% philo->data->nb_philo]));
	pthread_mutex_lock(&(philo->data->eat_mutex));
	if (philo->count == philo->data->nb_eat)
		philo->data->count++;
	if (philo->data->count == philo->data->nb_philo)
	{
		pthread_mutex_unlock(&(philo->data->eat_mutex));
		return (0);
	}
	pthread_mutex_unlock(&(philo->data->eat_mutex));
	if (!print("is sleeping", philo))
		return (0);
	my_sleep(philo->data->time_sleep);
	if (!print("is thinking", philo))
		return (0);
	return (1);
}

void	*philo_control(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->num % 2)
		usleep(1000);
	while (death_check(philo))
	{
		if (!take_fork(philo))
			break ;
		if (death_check(philo))
		{
			if (!eating(philo))
				break ;
		}
		else
			break ;
	}
	return (NULL);
}
