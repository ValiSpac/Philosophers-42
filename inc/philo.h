/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpac <vpac@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:50:42 by vpac              #+#    #+#             */
/*   Updated: 2023/05/24 17:00:11 by vpac             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				*fork_locked;
	long long int	start_time;
	long			nb_philo;
	long			time_death;
	long			time_eat;
	long			time_sleep;
	long			nb_eat;
	int				death_check;
	int				count;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	completion_mutex;
}			t_data;

typedef struct s_philo
{
	long			last_eat;
	int				num;
	int				count;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	eat_last;
}	t_philo;
//utils
int			ft_atoi(const char *str);
void		free_all(t_data *data);
int			is_num(char *str);
void		ft_swap(int a, int b);

//init
void		init_data(t_data *data, int ac, char **argv);
void		init_philo(t_data *data);

//main
long		gettime(void);
int			print(char *s, t_philo *philo);
void		my_sleep(long long time);

//philo
void		*philo_control(void *ptr);

#endif
