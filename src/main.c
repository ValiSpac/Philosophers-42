/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:49:20 by vpac              #+#    #+#             */
/*   Updated: 2023/05/13 15:12:09 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	my_sleep(long long time)
{
	long long	init_time;

	init_time = gettime();
	while (gettime() - init_time < time)
		usleep(100);
}

static int	check_format(int argc, char **argv)
{
	int	i;

	if ((argc != 5) && (argc != 6))
	{
		printf("wrong format!\n");
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) == 0 || !is_num(argv[i]))
		{
			printf("wrong format!\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	print(char *s, t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->death_mutex));
	pthread_mutex_lock(&(philo->data->print_mutex));
	if (philo->data->death_check)
	{
		pthread_mutex_unlock(&(philo->data->print_mutex));
		pthread_mutex_unlock(&(philo->data->death_mutex));
		return (0);
	}
	printf("%llu %d %s\n", gettime() - philo->data->start_time,
		philo->num + 1, s);
	pthread_mutex_unlock(&(philo->data->print_mutex));
	pthread_mutex_unlock(&(philo->data->death_mutex));
	if (s[0] == 'd')
	{
		pthread_mutex_lock(&(philo->data->death_mutex));
		philo->data->death_check = 1;
		pthread_mutex_unlock(&(philo->data->death_mutex));
	}
	return (1);
}

long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (check_format(argc, argv))
		return (1);
	init_data(&data, argc, argv);
	init_philo(&data);
	free_all(&data);
}
