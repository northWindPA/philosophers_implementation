/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhumfrey <mhumfrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 20:35:32 by mhumfrey          #+#    #+#             */
/*   Updated: 2021/06/23 05:54:14 by mhumfrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philosopher_full(t_philosophers *philo, int *i)
{
	if (philo->arguments->number_of_meals > 0)
	{
		(*i)++;
		if (*i == philo->arguments->number_of_meals)
		{
			if (philo->arguments->death_flag == 0)
			{
				pthread_mutex_lock(&philo->mutexes->write_mutex);
				printf("👍\x1B[93m %ld ms id %d philosopher is full \033[0m🤙\n", \
				time_fix() - philo->start, philo->philo_id);
				pthread_mutex_unlock(&philo->mutexes->write_mutex);
				return (1);
			}
		}
	}
	return (0);
}

void	philosopher_thinks(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->mutexes->write_mutex);
	if (philo->arguments->death_flag == 0)
		printf("💬\x1B[34m %ld ms id %d philosopher is thinking \033[0m💡\n", \
		time_fix() - philo->start, philo->philo_id);
	pthread_mutex_unlock(&philo->mutexes->write_mutex);
}

void	philosopher_sleeps(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->mutexes->write_mutex);
	if (philo->arguments->death_flag == 0)
		printf("💤\x1B[36m %ld ms id %d philosopher is sleeping \033[0m⏱\n", \
		time_fix() - philo->start, philo->philo_id);
	pthread_mutex_unlock(&philo->mutexes->write_mutex);
	sleep_fix(philo->arguments->sleep_time);
}

void	philosopher_eats(t_philosophers *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (philo->arguments->number_of_philosophers != 1)
		pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->mutexes->write_mutex);
	if (philo->arguments->death_flag == 0)
		printf("🍴\x1B[35m %ld ms id %d philosopher has taken the forks \033[0m 🥄\n", \
		time_fix() - philo->start, philo->philo_id);
	pthread_mutex_unlock(&philo->mutexes->write_mutex);
	philo->last = time_fix() - philo->start;
	pthread_mutex_lock(&philo->mutexes->write_mutex);
	if (philo->arguments->death_flag == 0)
		printf("🍽 \x1B[33m %ld ms id %d philosopher is eating \033[0m🍷\n", \
		time_fix() - philo->start, philo->philo_id);
	pthread_mutex_unlock(&philo->mutexes->write_mutex);
	sleep_fix(philo->arguments->eat_time);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	*check_death(void *philosopher)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)philosopher;
	while (!philo->arguments->death_flag)
	{
		if ((time_fix() - philo->start - \
		philo->last) > philo->arguments->life_time)
		{
			pthread_mutex_lock(&philo->mutexes->write_mutex);
			if (philo->arguments->death_flag == 0)
				printf("💀 %ld ms id %d philosopher is dead," \
				" everything will never be the same 👻\n", \
				time_fix() - philo->start, philo->philo_id);
			philo->arguments->death_flag = 1;
			if (philo->arguments->number_of_philosophers == 1)
				pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(&philo->mutexes->write_mutex);
		}
	}
	return (NULL);
}
