/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:02:49 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/04 22:51:25 by lzipp            ###   ########.fr       */
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
	int			philo_cnt;
	int			fork_cnt;
	int			ms_to_die;
	int			ms_to_sleep;
	int			ms_to_eat;
	int			must_eat_cnt;
	long long	start_time;
}				t_data;

typedef struct s_philo
{
	int			id;
	int			ms_to_die;
	int			ms_to_sleep;
	int			ms_to_eat;
	int			ms_since_last_eat;
	int			must_eat_cnt;
	int			left_fork;
	int			right_fork;
	pthread_t	*thread;
}				t_philo;

// input_parsing
t_data		*create_data(int argc, char **argv);

// time
long long	get_time(void);

// messages
void		fork_message(long long ms, int id);
void		eat_message(long long ms, int id);
void		sleep_message(long long ms, int id);
void		think_message(long long ms, int id);
void		death_message(long long ms, int id);

// helpers
void		*ft_calloc(size_t count, size_t size);


#endif
