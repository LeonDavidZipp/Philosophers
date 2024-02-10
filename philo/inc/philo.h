/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:02:49 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/10 16:39:57 by lzipp            ###   ########.fr       */
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
	long long				ms_start_time;
}				t_data;

// typedef struct s_philo
// {
// 	int						id;
// 	long long				ms_to_die;
// 	long long				ms_to_sleep;
// 	long long				ms_to_eat;
// 	long long				ms_last_ate_at;
// 	long long				must_eat_cnt;
// 	pthread_mutex_t			*left_fork;
// 	pthread_mutex_t			*right_fork;
// 	pthread_t				*thread;
// }				t_philo;

typedef struct s_fork
{
	int						id;
	bool					is_taken;
	pthread_mutex_t			*mutex;
}				t_fork;

typedef struct s_philo
{
	int						id;
	bool					is_dead;
	long long				ms_start_time;
	long long				ms_to_die;
	long long				ms_to_sleep;
	long long				ms_to_eat;
	long long				ms_last_ate_at;
	long long				must_eat_cnt;
	t_fork					*left_fork;
	t_fork					*right_fork;
	pthread_t				*thread;
}				t_philo;

typedef struct s_routine
{
	long long				start_time;
	t_philo					*philo;
	pthread_mutex_t			*p_mut;
	pthread_mutex_t			*death_mut;
	bool					*some_died;
}				t_routine;

// creating data, forks, philos
t_data			*create_data(int argc, char **argv);
t_fork			**create_forks(t_data *data);
t_philo			**create_philos(t_data *data, t_fork **forks);

// philosophize
void			philosophize(t_philo **philos, t_fork **forks);

// philo_routine
void			*philo_routine(void *r_void);
// bool			check_alive(t_routine *r, long long time);

// messages
void			fork_message(long long ms, t_routine *r);
void			eat_message(long long ms, t_routine *r);
void			sleep_message(long long ms, t_routine *r);
void			think_message(long long ms, t_routine *r);
void			death_message(long long ms, t_routine *r);

// free functions
void			ft_free_2d_arr(void **arr);
void			free_forks(t_fork **forks);
void			free_philos(t_philo **philos);
void			free_resources(t_philo **philos, t_fork **forks);

// helpers
void			*ft_calloc(size_t count, size_t size);
int				ft_null_terminated_arr_len(void **arr);
int				ft_usleep(long long ms);
long long		get_time(void);

#endif
