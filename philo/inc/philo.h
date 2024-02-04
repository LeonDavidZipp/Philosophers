/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:02:49 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/05 00:46:30 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_data
{
	int						philo_cnt;
	int						fork_cnt;
	int						ms_to_die;
	int						ms_to_sleep;
	int						ms_to_eat;
	int						must_eat_cnt;
	long long				start_time;
}				t_data;

typedef struct s_philo
{
	int						id;
	int						ms_to_die;
	int						ms_to_sleep;
	int						ms_to_eat;
	int						ms_last_ate_at;
	int						must_eat_cnt;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	pthread_t				*thread;
}				t_philo;

// creating data, forks, philos
t_data			*create_data(int argc, char **argv);
pthread_mutex_t	**create_forks(t_data *data);
t_philo			**create_philos(t_data *data, pthread_mutex_t **forks);

// philo_routine
void			philo_routine(t_philo *philo);

// time
long long		get_time(void);

// messages
void			fork_message(long long ms, int id);
void			eat_message(long long ms, int id);
void			sleep_message(long long ms, int id);
void			think_message(long long ms, int id);
void			death_message(long long ms, int id);

// helpers
void			*ft_calloc(size_t count, size_t size);
void			ft_free_2d_arr(void **arr);
void			ft_free_2d_mutex_arr(pthread_mutex_t **arr);

#endif
