/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:49:20 by vpac              #+#    #+#             */
/*   Updated: 2023/04/25 16:11:02 by vpac             ###   ########.fr       */
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
		if (ft_atoi(argv[i]) == 0)
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
	if (philo->data->death_check)
		return (0);
	printf("%llu %d %s\n", gettime() - philo->data->start_time, philo->num + 1, s);
	if (s[0] == 'd')
		philo->data->death_check = 1;
	return (1);
}

long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	main(int argc, char **argv)
{
	t_data		data;

	if(check_format(argc, argv))
		return (1);
	init_data(&data, argc, argv);
	init_philo(&data);
	free_all(&data);
}
