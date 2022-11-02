/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:06:12 by anoukmechai       #+#    #+#             */
/*   Updated: 2022/10/21 17:07:16 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main()
{
	t_counter	counter;

	pthread_mutex_init(&counter.count_mutex, NULL); 		- OK
	pthread_create(&tid1, NULL, thread_routine, NULL);		- OK
	pthread_join(tid1, NULL);								- OK
	pthread_mutex_destroy(&counter.count_mutex);
}

/*******************/
/* Thread creation */
/*******************/

void	*thread_routine(void *data);

int main()
{
	pthread_t	tid1;

	pthread_create(&tid1, NULL, thread_routine, NULL);
	pthread_join(tid1, NULL);
}

/*******************/
/* Mutex creation  */
/*******************/

/* The mutex and the variable it protects */

typedef	struct s_counter
{
	pthread_mutex_t	count_mutex;
	unsigned int	count;
} t_counter;

void	*thread_routine(void *data)
{
	pthread_mutex_lock(&counter->count_mutex);
	/* Instructions */
	pthread_mutex_unlock(&counter->count_mutex);
}

int main()
{
	t_counter	counter;

	pthread_mutex_init(&counter.count_mutex, NULL);
	/* Thread creation */
	pthread_mutex_destroy(&counter.count_mutex);
}

/*******************/
/* Time management */
/*******************/

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
