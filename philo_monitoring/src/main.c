/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:48:08 by lzipp             #+#    #+#             */
/*   Updated: 2024/02/10 12:21:22 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	handle_one_philo(t_data *data);
static void	check_valid(int argc, char **argv);

int	main(int argc, char **argv)
{
	t_data				*data;
	t_philo				**philos;
	pthread_mutex_t		**forks;

	check_valid(argc, argv);
	data = create_data(argc, argv);
	if (data->fork_cnt == 1)
		handle_one_philo(data);
	forks = create_forks(data);
	philos = create_philos(data, forks);
	philosophize(data, philos, forks);
	free_resources(data, philos, forks);
	return (0);
}

static void	check_valid(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
	{
		printf("\033[0;31mUsage: ./philo nr_of_philos t_to_die t_to_eat");
		printf(" t_to_sleep [nr_must_eat]\033[0m\n");
		exit(1);
	}
	i = 0;
	while (++i < argc)
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
			{
				printf("\033[0;31mError: invalid arguments\033[0m\n");
				exit(1);
			}
		}
	}
}

static void	handle_one_philo(t_data *data)
{
	ft_usleep(data->ms_to_die);
	printf("\033[0;31m%lld 1 died", data->ms_to_die);
	printf("\033[0m\n");
	free(data);
	exit(0);
}
