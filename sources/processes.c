/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:36:40 by amechain          #+#    #+#             */
/*   Updated: 2022/11/02 18:38:36 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

time_t	get_time_in_ms(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) < 0)
		error("Get time of the day fail");
	return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	think(t_pack *pack, int id)
{
	int get_current_time;
	int	time_to_think;

	time_to_think = (int)(pack->table->time_to_die -
		(get_time_in_ms() - pack->philos[id]->last_meal) - pack->table->time_to_eat) / 2;
	get_current_time = (int)get_time_in_ms();
	ft_printf("%d %d is thinking\n", get_current_time, id);
	if (usleep(pack->table->time_to_think * 1000) < 0)
		error ("Usleep function fail");
}

void	sleep(t_pack *pack, int id)
{
	int get_current_time;

	get_current_time = (int)get_time_in_ms();
	ft_printf("%d %d is sleeping\n", get_current_time, id);
	if (usleep(pack->table->time_to_sleep * 1000) < 0)
		error ("Usleep function fail");
}

void	eat(t_pack *pack, int id)
{
	int get_current_time;

	get_current_time = (int)get_time_in_ms();
	ft_printf("%d %d is eating\n", get_current_time, id);
	if (usleep(pack->table->time_to_eat * 1000) < 0)
		error ();
}

void	thread_routine(t_pack *pack)
{
	if (pack->philos[pack->count]->id % 2 == 1)
		usleep(1000);
	pthread_mutex_lock(&pack->philos[pack->count]->mutex);
	ft_printf("%d has taken a fork\n", pack->philos[pack->count]->id);
	pthread_mutex_lock(&pack->philos[(pack->count + 1) % 5]->mutex);
	ft_printf("%d has taken a second fork\n", pack->philos[pack->count]->id);
	if (/* supervisor validation */)
		eat(pack, pack->philos[pack->count]->id);
	pthread_mutex_unlock(&pack->philos[pack->count]->mutex);
	pthread_mutex_unlock(&pack->philos[(pack->count + 1) % 5]->mutex);
	if (/* supervisor validation */)
	{
		sleep(pack, pack->philos[pack->count]->id);
		think(pack, pack->philos[pack->count]->id);
	}
}

void	thread_init(t_pack *pack, t_philo **philos)
{
	int	i;

	i = 0;
	while (i < pack->table->nbr_philos)
	{
		if (pthread_create(philos[pack->count]->thread, NULL, thread_routine, pack) != 0)
			error ();
		pack->count++;
		i++;
	}
	if (pthread_create(&pack->table->supervisor, NULL, supervisor_routine, pack) != 0)
		error ();
}

void	mutex_init(t_pack *pack)
{
	int	i;

	i = 0;
	while (i < pack->table->nbr_philos)
	{
		if (pthread_mutex_init(&pack->philos[i]->mutex, NULL) != 0)
			error ();
		i++;
	}
	if (pthread_mutex_init(&pack->table->sim_status_protect, NULL) != 0)
		error ();
}

void	processes(t_pack *pack)
{
	mutex_init(pack);
	thread_init(pack, philos);
}
