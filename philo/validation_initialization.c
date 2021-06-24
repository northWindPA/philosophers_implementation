/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_initialization.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhumfrey <mhumfrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 15:44:15 by mhumfrey          #+#    #+#             */
/*   Updated: 2021/06/23 05:00:44 by mhumfrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	time_fix(void)
{
	long			ret_time;
	struct timeval	time;

	gettimeofday(&time, NULL);
	ret_time = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (ret_time);
}

int	validate_args(char **args)
{
	int	i;
	int	j;

	j = 0;
	while (args[++j])
	{
		i = -1;
		while (args[j][++i])
		{
			if (!is_digit(args[j][i]))
				return (out_error("wrong argument - non-digital symbol."));
		}
	}
	if (long_atoi(args[1]) == LONG_MAX || long_atoi(args[1]) == LONG_MIN \
	|| long_atoi(args[2]) == LONG_MAX || long_atoi(args[2]) == LONG_MIN \
	|| long_atoi(args[3]) == LONG_MAX || long_atoi(args[3]) == LONG_MIN \
	|| long_atoi(args[4]) == LONG_MAX || long_atoi(args[4]) == LONG_MIN)
		return (out_error("argument overflowed."));
	if (long_atoi(args[1]) > 200)
		return (out_error("number of philosophers is more than needed."));
	if (long_atoi(args[1]) < 1)
		return (out_error("number of philosophers is less than needed."));
	return (0);
}

int	initialize_args(t_matrix *matrix, char **av, int ac)
{
	matrix->arguments = (t_arguments *)malloc(sizeof(t_arguments));
	if (!matrix->arguments)
		return (out_error("can't allocate memory for arg-struct."));
	matrix->arguments->number_of_philosophers = long_atoi(av[1]);
	matrix->arguments->life_time = long_atoi(av[2]);
	matrix->arguments->eat_time = long_atoi(av[3]);
	matrix->arguments->sleep_time = long_atoi(av[4]);
	if (ac == 5)
		matrix->arguments->number_of_meals = 0;
	else if (ac == 6)
	{
		if (long_atoi(av[5]) == LONG_MAX || long_atoi(av[5]) == LONG_MIN)
			return (out_error("argument overflowed."));
		else
			matrix->arguments->number_of_meals = long_atoi(av[5]);
	}
	matrix->arguments->death_flag = 0;
	return (0);
}

int	initialize_muts(t_matrix *matrix)
{
	int	i;

	i = 0;
	matrix->mutexes = (t_mutexes *)malloc(sizeof(t_mutexes));
	if (!matrix->mutexes)
		return (out_error("can't allocate memory for mut-struct."));
	matrix->mutexes->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* matrix->arguments->number_of_philosophers);
	if (!matrix->mutexes->forks)
		return (out_error("can't allocate memory for forks."));
	if (pthread_mutex_init(&matrix->mutexes->write_mutex, NULL))
		return (out_error("write pthread initialization error."));
	while (i < matrix->arguments->number_of_philosophers)
	{
		if (pthread_mutex_init(&matrix->mutexes->forks[i], NULL))
			return (out_error("pthread-forks initialization error."));
		i++;
	}
	return (0);
}

int	initialize_philos(t_matrix *matrix)
{
	int		i;
	long	start_time;

	i = 0;
	start_time = time_fix();
	matrix->philosophers = (t_philosophers *)malloc(sizeof(t_philosophers) \
	* matrix->arguments->number_of_philosophers);
	if (!matrix->philosophers)
		return (out_error("can't allocate memory for philo-struct."));
	while (i < matrix->arguments->number_of_philosophers)
	{
		matrix->philosophers[i].start = start_time;
		matrix->philosophers[i].l_fork = &matrix->mutexes->forks[i];
		matrix->philosophers[i].r_fork = &matrix->mutexes->forks[(i + 1) \
		% matrix->arguments->number_of_philosophers];
		matrix->philosophers[i].philo_id = i + 1;
		matrix->philosophers[i].arguments = matrix->arguments;
		matrix->philosophers[i].mutexes = matrix->mutexes;
		matrix->philosophers[i].last = 0;
		i++;
	}
	return (0);
}
