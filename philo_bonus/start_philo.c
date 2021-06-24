/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhumfrey <mhumfrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 20:32:31 by mhumfrey          #+#    #+#             */
/*   Updated: 2021/06/23 04:56:36 by mhumfrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleep_fix(long wait_time)
{
	long	current_time;
	long	period;

	current_time = time_fix();
	period = current_time + wait_time;
	while (period > current_time)
	{
		usleep(1);
		current_time = time_fix();
	}
}

void	processes(t_philosophers *philosopher)
{
	int			i;
	pthread_t	death_check_thread;

	i = 0;
	pthread_create(&death_check_thread, NULL, check_death, (void *)philosopher);
	pthread_detach(death_check_thread);
	while (!philosopher->arguments->death_flag)
	{
		philosopher_eats(philosopher);
		if (philosopher_full(philosopher, &i))
			exit (0);
		philosopher_sleeps(philosopher);
		philosopher_thinks(philosopher);
	}
}

void	wait_loop(t_matrix *matrix)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	while (i < matrix->arguments->number_of_philosophers)
	{
		waitpid(-1, &status, 0);
		if (status == 0)
		{
			j = 0;
			while (j < matrix->arguments->number_of_philosophers)
			{
				kill(matrix->philosophers->pid[j], SIGTERM);
				j++;
			}
		}
		i++;
	}
}

int	start_philosopher(t_matrix *matrix)
{
	int	i;

	i = 0;
	while (i < matrix->arguments->number_of_philosophers)
	{
		matrix->philosophers->pid[i] = fork();
		if (matrix->philosophers->pid[i] == 0)
		{
			matrix->philosophers->philo_id = i + 1;
			processes(matrix->philosophers);
		}
		else if (matrix->philosophers->pid[i] == -1)
			return (out_error("can't create a new process."));
		i++;
	}
	wait_loop(matrix);
	return (0);
}

int	main(int ac, char **av)
{
	t_matrix	matrix;

	if (ac < 5)
		return (out_error("bad quantity of arguments - not enough."));
	if (ac > 6)
		return (out_error("bad quantity of arguments - too much."));
	if (validate_args(av))
		return (1);
	if (initialize_args(&matrix, av, ac))
		return (1);
	if (initialize_sems(&matrix))
		return (1);
	if (initialize_philos(&matrix))
		return (1);
	if (start_philosopher(&matrix))
		return (1);
	matrix.arguments->death_flag = 1;
	free_all(&matrix);
	return (0);
}
