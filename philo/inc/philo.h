/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:02:49 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/07 15:22:49 by lzipp            ###   ########.fr       */
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
	long long				ms_to_die;
	long long				ms_to_sleep;
	long long				ms_to_eat;
	int						must_eat_cnt;
	long long				start_time;
	bool					some_died;
}				t_data;

typedef struct s_philo
{
	int						id;
	long long				ms_to_die;
	long long				ms_to_sleep;
	long long				ms_to_eat;
	long long				ms_last_ate_at;
	long long				must_eat_cnt;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	pthread_t				*thread;
}				t_philo;

typedef struct s_routine
{
	t_philo					*philo;
	pthread_mutex_t			*p_mut;
	bool					*some_died;
	pthread_mutex_t			*death_mut;
}				t_routine;

// creating data, forks, philos
t_data			*create_data(int argc, char **argv);
pthread_mutex_t	**create_forks(t_data *data);
t_philo			**create_philos(t_data *data, pthread_mutex_t **forks);

// philosophize
void			philosophize(t_data *data, t_philo **philos,
					pthread_mutex_t **forks);

// philo_routine
void			*philo_routine(void *r_void);

// time
long long		get_time(void);
int				ft_usleep(long long ms);

// messages
void			fork_message(long long ms, int id, pthread_mutex_t *p_mut);
void			eat_message(long long ms, int id, pthread_mutex_t *p_mut);
void			sleep_message(long long ms, int id, pthread_mutex_t *p_mut);
void			think_message(long long ms, int id, pthread_mutex_t *p_mut);
void			death_message(long long ms, int id, pthread_mutex_t *p_mut);

// helpers
void			*ft_calloc(size_t count, size_t size);
void			ft_free_2d_arr(void **arr);
void			ft_free_2d_mutex_arr(pthread_mutex_t **arr);
void			free_resources(t_data *data, t_philo **philos,
					pthread_mutex_t **forks);

#endif
