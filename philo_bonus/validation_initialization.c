/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_initialization.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhumfrey <mhumfrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 22:32:21 by mhumfrey          #+#    #+#             */
/*   Updated: 2021/06/23 04:55:06 by mhumfrey         ###   ########.fr       */
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

int	initialize_sems(t_matrix *matrix)
{
	matrix->semaphore = (t_semaphores *)malloc(sizeof(t_semaphores));
	if (!matrix->semaphore)
		return (out_error("can't allocate memory for sem-struct."));
	sem_unlink("write");
	sem_unlink("checkd");
	matrix->semaphore->write_semaphore = sem_open("write", O_CREAT, 0644, 1);
	matrix->semaphore->checkd = sem_open("checkd", O_CREAT, 0644, 1);
	if (matrix->semaphore->write_semaphore == SEM_FAILED)
		return (out_error("write-semaphore opening is failed."));
	sem_unlink("forks");
	matrix->semaphore->forks = sem_open("forks", \
	O_CREAT, 0644, matrix->arguments->number_of_philosophers / 2);
	if (matrix->semaphore->forks == SEM_FAILED)
		return (out_error("forks semaphore opening is failed."));
	return (0);
}

int	initialize_philos(t_matrix *matrix)
{
	long	start_time;

	start_time = time_fix();
	matrix->philosophers = (t_philosophers *)malloc(sizeof(t_philosophers));
	if (!matrix->philosophers)
		return (out_error("can't allocate memory for philo-struct."));
	matrix->pid = (pid_t *)malloc(sizeof(pid_t) \
	* matrix->arguments->number_of_philosophers);
	if (!matrix->pid)
		return (out_error("can't allocate memory for pid"));
	matrix->philosophers->start = start_time;
	matrix->philosophers->pid = matrix->pid;
	matrix->philosophers->arguments = matrix->arguments;
	matrix->philosophers->semaphore = matrix->semaphore;
	matrix->philosophers->last = 0;
	return (0);
}
