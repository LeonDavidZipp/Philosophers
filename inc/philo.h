/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:02:49 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/04 12:26:47 by lzipp            ###   ########.fr       */
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
	int		t_to_die;
	int		t_to_eat;
	int		t_to_sleep;
	int		must_eat_cnt;
}				t_data;

typedef struct s_philo
{
	int		id;
	int		t_to_die;
	int		t_to_eat;
	int		t_to_sleep;
	int		must_eat_cnt;
}				t_philo;

#endif
