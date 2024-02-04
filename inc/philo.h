/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:02:49 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/04 12:41:11 by lzipp            ###   ########.fr       */
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
	int		philo_cnt;
	int		fork_cnt;
	int		ms_to_die;
	int		ms_to_eat;
	int		ms_to_sleep;
	int		must_eat_cnt;
}				t_data;

typedef struct s_philo
{
	int		id;
	int		ms_to_die;
	int		ms_to_eat;
	int		ms_to_sleep;
	int		must_eat_cnt;
}				t_philo;

#endif
