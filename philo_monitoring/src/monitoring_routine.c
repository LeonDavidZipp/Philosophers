/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_routine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:33:49 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/10 14:20:17 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*monitoring_routine(void *m_data_void)
{
	t_monitor_data	*m_data;

	m_data = (t_monitor_data *)m_data_void;
	while (!m_data->some_died)
	{
		if (m_data->activity == 0)
			printf("\033[0;33m%lld %d is thinking\033[0m\n",
				m_data->ms_time, m_data->id);
		else if (m_data->activity == 1)
			printf("\033[0;32m%lld %d is eating\033[0m\n",
				m_data->ms_time, m_data->id);
		else if (m_data->activity == 2)
			printf("\033[0;35m%lld %d is sleeping\033[0m\n",
				m_data->ms_time, m_data->id);
		else if (m_data->activity == 3)
			printf("\033[0;31m%lld %d died\033[0m\n",
				m_data->ms_time, m_data->id);
		else if (m_data->activity == 4)
			printf("\033[0;36m%lld %d has taken a fork\033[0m\n",
				m_data->ms_time, m_data->id);
	}
	return (NULL);
}
