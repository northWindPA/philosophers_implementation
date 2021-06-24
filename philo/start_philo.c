/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhumfrey <mhumfrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 20:32:31 by mhumfrey          #+#    #+#             */
/*   Updated: 2021/06/23 05:10:35 by mhumfrey         ###   ########.fr       */
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

void	*threads(void *philosopher)
{
	int				i;
	t_philosophers	*philo;
	pthread_t		death_check_thread;

	i = 0;
	philo = (t_philosophers *)philosopher;
	pthread_create(&death_check_thread, NULL, check_death, (void *)philo);
	pthread_detach(death_check_thread);
	while (philo->arguments->death_flag == 0)
	{
		philosopher_eats(philo);
		if (philosopher_full(philo, &i))
			break ;
		philosopher_sleeps(philo);
		philosopher_thinks(philo);
	}
	return (NULL);
}

int	join_loop(t_matrix *matrix)
{
	int	i;

	i = 0;
	while (++i < matrix->arguments->number_of_philosophers)
	{
		if (pthread_join(matrix->philosophers[i].philosopher, NULL))
			return (out_error("can't join a thread of philosopher."));
		i++;
	}
	return (0);
}

int	start_philosopher(t_matrix *matrix)
{
	int	i;

	i = 0;
	while (i < matrix->arguments->number_of_philosophers)
	{
		if (pthread_create(&matrix->philosophers[i].philosopher, \
		NULL, threads, &matrix->philosophers[i]))
			return (out_error("can't create a philosopher-thread."));
		sleep_fix(1);
		i++;
	}
	if (join_loop(matrix))
		return (1);
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
	if (initialize_muts(&matrix))
		return (1);
	if (initialize_philos(&matrix))
		return (1);
	if (start_philosopher(&matrix))
		return (1);
	matrix.arguments->death_flag = 1;
	free_all(&matrix);
	return (0);
}
