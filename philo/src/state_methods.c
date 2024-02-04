/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:17:28 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/04 21:18:50 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void 	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	fork_message(get_time() - philo->data->start_time, philo->id);
	pthread_mutex_lock(&philo->right_fork);
	fork_message(get_time() - philo->data->start_time, philo->id);
}
