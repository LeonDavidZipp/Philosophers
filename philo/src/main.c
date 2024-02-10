/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:48:08 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/10 16:11:15 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	handle_one_philo(t_data *data);

int	main(int argc, char **argv)
{
	t_data				*data;
	t_philo				**philos;
	pthread_mutex_t		**forks;

	data = create_data(argc, argv);
	if (data->fork_cnt == 1)
		handle_one_philo(data);
	forks = create_forks(data);
	philos = create_philos(data, forks);
	free(data);
	philosophize(philos, forks);
	free_resources(philos, forks);
	return (0);
}

static void	handle_one_philo(t_data *data)
{
	ft_usleep(data->ms_to_die);
	printf("\033[0;31m%lld 1 died", data->ms_to_die);
	printf("\033[0m\n");
	free(data);
	exit(0);
}
