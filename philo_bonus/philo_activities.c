/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhumfrey <mhumfrey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 20:35:32 by mhumfrey          #+#    #+#             */
/*   Updated: 2021/06/23 04:51:13 by mhumfrey         ###   ########.fr       */
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
			sem_wait(philo->semaphore->write_semaphore);
			printf("👍\x1B[93m %ld ms id %d philosopher is full \033[0m🤙\n", \
				time_fix() - philo->start, philo->philo_id);
			sem_post(philo->semaphore->write_semaphore);
			exit (1);
		}
	}
	return (0);
}

void	philosopher_thinks(t_philosophers *philo)
{
	sem_wait(philo->semaphore->write_semaphore);
	if (philo->arguments->death_flag == 0)
		printf("💬\x1B[34m %ld ms id %d philosopher is thinking \033[0m💡\n", \
		time_fix() - philo->start, philo->philo_id);
	sem_post(philo->semaphore->write_semaphore);
}

void	philosopher_sleeps(t_philosophers *philo)
{
	sem_wait(philo->semaphore->write_semaphore);
	if (philo->arguments->death_flag == 0)
		printf("💤\x1B[36m %ld ms id %d philosopher is sleeping \033[0m⏱\n", \
		time_fix() - philo->start, philo->philo_id);
	sem_post(philo->semaphore->write_semaphore);
	sleep_fix(philo->arguments->sleep_time);
}

void	philosopher_eats(t_philosophers *philo)
{
	sem_wait(philo->semaphore->forks);
	sem_wait(philo->semaphore->write_semaphore);
	if (philo->arguments->death_flag == 0)
		printf("🍴\x1B[35m %ld ms id %d philosopher has taken the forks \033[0m 🥄\n", \
		time_fix() - philo->start, philo->philo_id);
	sem_post(philo->semaphore->write_semaphore);
	sem_wait(philo->semaphore->write_semaphore);
	if (philo->arguments->death_flag == 0)
		printf("🍽 \x1B[33m %ld ms id %d philosopher is eating \033[0m🍷\n", \
		time_fix() - philo->start, philo->philo_id);
	sem_post(philo->semaphore->write_semaphore);
	philo->last = time_fix() - philo->start;
	sleep_fix(philo->arguments->eat_time);
	sem_post(philo->semaphore->forks);
}

void	*check_death(void *philosopher)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)philosopher;
	while (!philo->arguments->death_flag)
	{
		sem_wait(philo->semaphore->checkd);
		if (time_fix() - philo->start - philo->last \
		> philo->arguments->life_time)
		{
			sem_wait(philo->semaphore->write_semaphore);
			printf("💀 %ld ms id %d philosopher is dead," \
			" everything will never be the same 👻\n", \
			time_fix() - philo->start, philo->philo_id);
			philo->arguments->death_flag = 1;
			exit (0);
		}
		sem_post(philo->semaphore->checkd);
	}
	return (NULL);
}
