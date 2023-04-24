/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:05:16 by vpac              #+#    #+#             */
/*   Updated: 2023/04/17 13:19:28 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	a;
	int	tmp;

	i = 0;
	a = 1;
	tmp = 0;
	while (str[i] == ' ' || (str[i] <= '\r' && str[i] >= '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			a *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = tmp * 10 + str[i] - 48;
		i++;
	}
	return (tmp * a);

}

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&(data->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->philo);
	free(data->fork);
}
