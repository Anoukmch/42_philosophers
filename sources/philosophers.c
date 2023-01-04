/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmechain <anoukmechain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:00:48 by anoukmechai       #+#    #+#             */
/*   Updated: 2023/01/04 09:44:51 by anoukmechai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	think_routine(t_philo *philos, int print)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philos->lock_var);
	time_to_think = (philos->table->time_to_die
			- (get_time_in_ms() - philos->last_meal)
			- philos->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philos->lock_var);
	if (time_to_think < 0)
		time_to_think = 0;
	else if (time_to_think > 600)
		time_to_think = 300;
	if (print)
		print_message(philos, philos->id, "is thinking");
	sleep_time(time_to_think, philos);
}

void	sleep_routine(t_philo *philos)
{
	print_message(philos, philos->id, "is sleeping");
	sleep_time(philos->table->time_to_sleep, philos);
}

void	eat_routine(t_philo *philos)
{
	print_message(philos, philos->id, "is eating");
	pthread_mutex_lock(&philos->lock_var);
	philos->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philos->lock_var);
	sleep_time(philos->table->time_to_eat, philos);
	if (!simulation_must_stop(philos))
	{
		pthread_mutex_lock(&philos->lock_var);
		philos->nbr_meal++;
		pthread_mutex_unlock(&philos->lock_var);
	}
}

int	simulation(t_philo	*philos)
{
	pthread_mutex_lock(&philos->table->mutex[philos->fork[0]]);
	print_message(philos, philos->id, "has taken a fork");
	pthread_mutex_lock(&philos->table->mutex[philos->fork[1]]);
	print_message(philos, philos->id, "has taken a fork");
	eat_routine(philos);
	pthread_mutex_unlock(&philos->table->mutex[philos->fork[0]]);
	pthread_mutex_unlock(&philos->table->mutex[philos->fork[1]]);
	if (simulation_must_stop(philos))
		return (1);
	sleep_routine(philos);
	if (simulation_must_stop(philos))
		return (1);
	think_routine(philos, 1);
	return (0);
}

void	*philos_routine(void *data)
{
	t_philo	*philos;

	philos = (t_philo *)data;
	pthread_mutex_lock(&philos->lock_var);
	philos->last_meal = philos->table->start_time;
	pthread_mutex_unlock(&philos->lock_var);
	sync_thread(philos->table->start_time);
	if (philos->table->time_to_die == 0)
		return (NULL);
	if (philos->table->nbr_philos == 1)
		return (one_philosopher(philos));
	if (philos->id % 2)
		think_routine(philos, 0);
	while (!simulation_must_stop(philos))
	{
		if (simulation(philos))
			return (NULL);
	}
	return (NULL);
}
