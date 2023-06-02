/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 18:13:24 by vpac              #+#    #+#             */
/*   Updated: 2023/05/29 14:27:54 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	take_fork(t_philo *philo)
{
	int	lower_fork;
	int	higher_fork;

	lower_fork = philo->num;
	higher_fork = (philo->num + 1) % philo->data->nb_philo;
	if (lower_fork > higher_fork)
		ft_swap(lower_fork, higher_fork);
	pthread_mutex_lock(&(philo->data->fork[lower_fork]));
	pthread_mutex_lock(&(philo->data->fork[higher_fork]));
	if (!print("has taken a fork", philo))
		return (pthread_mutex_unlock(&(philo->data->fork[higher_fork])),
			pthread_mutex_unlock(&(philo->data->fork[lower_fork])), 0);
	if (!print("has taken a fork", philo))
		return (pthread_mutex_unlock(&(philo->data->fork[higher_fork])),
			pthread_mutex_unlock(&(philo->data->fork[lower_fork])), 0);
	return (1);
}

void	put_down_forks(t_philo *philo)
{
	int	lower_fork;
	int	higher_fork;

	lower_fork = philo->num;
	higher_fork = (philo->num + 1) % philo->data->nb_philo;
	if (lower_fork > higher_fork)
		ft_swap(lower_fork, higher_fork);
	pthread_mutex_unlock(&(philo->data->fork[higher_fork]));
	pthread_mutex_unlock(&(philo->data->fork[lower_fork]));
}

int	eating(t_philo *philo)
{
	if (!print("is eating", philo))
		return (0);
	pthread_mutex_lock(&(philo->eat_last));
	philo->last_eat = gettime() - philo->data->start_time;
	pthread_mutex_unlock(&(philo->eat_last));
	my_sleep(philo->data->time_eat);
	put_down_forks(philo);
	pthread_mutex_lock(&(philo->data->eat_mutex));
	philo->count++;
	if (philo->count == philo->data->nb_eat - 1)
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

void	*control_one_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->fork[0]));
	my_sleep(philo->data->time_death);
	pthread_mutex_unlock(&(philo->data->fork[0]));
	print("died", philo);
	return (0);
}

void	*philo_control(void *ptr)
{
	t_philo		*philo;
	long long	last_eat;

	philo = (t_philo *)ptr;
	if (philo->num % 2)
		usleep(100);
	if (philo->data->nb_philo == 1)
		control_one_philo(philo);
	else
	{
		while (1)
		{
			if (!take_fork(philo))
				break ;
			pthread_mutex_lock(&philo->eat_last);
			last_eat = philo->last_eat;
			pthread_mutex_unlock(&philo->eat_last);
			if (((gettime() - philo->data->start_time) - last_eat)
				>= philo->data->time_death)
				return (print("died", philo), NULL);
			if (!eating(philo))
				break ;
		}
	}
	return (NULL);
}
