/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmechain <anoukmechain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 17:35:47 by anoukmechai       #+#    #+#             */
/*   Updated: 2023/01/03 17:37:43 by anoukmechai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*one_philosopher(t_philo *philos)
{
	pthread_mutex_lock(&philos->table->mutex[philos->fork[0]]);
	print_message(philos, philos->id, "has taken a fork");
	sleep_time(philos->table->time_to_die, philos);
	print_message(philos, philos->id, "died");
	pthread_mutex_unlock(&philos->table->mutex[philos->fork[0]]);
	return (NULL);
}
