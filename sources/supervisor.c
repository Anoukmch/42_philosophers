/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmechain <anoukmechain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 10:01:50 by anoukmechai       #+#    #+#             */
/*   Updated: 2023/01/04 10:37:40 by anoukmechai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	is_dead(t_pack *pack, t_philo *philos)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philos->last_meal) >= pack->table->time_to_die)
	{
		print_message(philos, philos->id, "died");
		pthread_mutex_unlock(&philos->lock_var);
		return (1);
	}
	return (0);
}

bool	check_philos(t_pack *pack)
{
	int		i;
	bool	must_stop;

	i = 0;
	must_stop = true;
	while (i < pack->table->nbr_philos)
	{
		pthread_mutex_lock(&pack->philos[i]->lock_var);
		if (is_dead(pack, pack->philos[i]))
			return (true);
		if (pack->table->meal_requirmt != -1)
		{
			if (pack->philos[i]->nbr_meal < pack->table->meal_requirmt)
				must_stop = false;
		}
		pthread_mutex_unlock(&pack->philos[i]->lock_var);
		i++;
	}
	if (pack->table->meal_requirmt != -1 && must_stop == true)
		return (true);
	return (false);
}

void	*supervisor_routine(void *data)
{
	t_pack	*pack;

	pack = (t_pack *)data;
	if (pack->table->time_to_die == 0)
		return (NULL);
	sync_thread(pack->table->start_time);
	while (true)
	{
		if (check_philos(pack))
		{
			pthread_mutex_lock(&pack->table->lock_sim);
			pack->table->sim_stop = true;
			pthread_mutex_unlock(&pack->table->lock_sim);
			return (NULL);
		}
		usleep(1000);
	}
}
