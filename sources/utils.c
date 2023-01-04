/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmechain <anoukmechain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:54:24 by anoukmechai       #+#    #+#             */
/*   Updated: 2023/01/03 21:44:36 by anoukmechai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	sync_thread(time_t start_time)
{
	while (get_time_in_ms() < start_time)
		continue ;
}

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_message(t_philo *philos, int id, char *message)
{
	pthread_mutex_lock(&philos->table->lock_msg);
	if (simulation_must_stop(philos))
	{
		pthread_mutex_unlock(&philos->table->lock_msg);
		return ;
	}
	printf("%ld %d %s\n", (get_time_in_ms()
			- philos->table->start_time), id, message);
	pthread_mutex_unlock(&philos->table->lock_msg);
}

void	sleep_time(time_t sleep_time, t_philo *philos)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < wake_up)
	{
		if (simulation_must_stop(philos))
			break ;
		usleep(100);
	}
}

void	assign_forks(t_philo *philos)
{
	philos->fork[0] = philos->id;
	philos->fork[1] = (philos->id + 1) % philos->table->nbr_philos;
	if (philos->id % 2)
	{
		philos->fork[0] = (philos->id + 1) % philos->table->nbr_philos;
		philos->fork[1] = philos->id;
	}
}
