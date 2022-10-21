/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anoukmechain <anoukmechain@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 11:28:37 by anoukmechai       #+#    #+#             */
/*   Updated: 2022/10/21 13:53:08 by anoukmechai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* gcc -pthread main.c */

#include <pthread.h>
#include <sys/time.h>

typedef struct s_arg
{
	int				nbr_philos;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				meal_requirmt;
    t_philo			**dinner;
	pthread_t		supervisor;
	bool			sim_status;
	pthread_mutex_t	sim_status_protect;
	
}               t_arg;

typedef struct s_philo
{
	pthread_t	thread;
	time_t		last_meal;
	int			nbr_meal;
    int			id;
	
}               t_philo;

typedef struct s_fork
{
	pthread_mutex_t	*mutex;
    int	msgs;
	
}               t_fork;

void	error_msg(char *err)
{
	perror(err);
	freeing();
	exit (1);
}

char	**split_arg(char **ag)
{
	char	**array;
	int		nbr_string;

	array = ft_split(ag, &nbr_string); /* Modifier split */
	if (!array)
		return (error("Allocation failed"));
	if (nbr_string - 1 != 4 || nbr_string - 1 != 5)
		return (error("Wrong number input"));
	return (array);
}

void ft_atoi_bis ()
/* Atoi renvoie les nombres même négatif */

void	is_negative(int i, int nb, int ac)
{
	if (i == 1 && nb <= 0)
		error("Wrong input : not enough philosophers");
	else if (ac - 1 == 4 && i != 1 && nb < 0)
		error("Wrong input : time data cannot be negative");
	else if (ac - 1 == 5)	
	{
		if (i != 1 && i != ac - 1 && nb < 0)
			error("Wrong input : time data cannot be negative");
		else if (i == ac - 1 && nb <= 0)
			error("Wrong input : wrong meal requirement");
	}
}

int	*check_parsing(int ac, char **ag)
{
	int nb;
	int i;
	int j;
	int	*stash;

	i = 1;
	j = 0;
	stash = ft_calloc(ac - 1, sizeof(int));
	while (++i < ac)
	{	
		if (!check_digit || ag[i])
			error();
		nb = ft_atoi(ag[i]); /* Long long atoi */
		if (nb > INT_MAX)
			error("Wrong input : not an integer");
		is_negative(i, nb, ac);
		stash[j++] = nb;
	}
	return (stash);
}

int main(int ac, char **ag)
{
	char	**array;
	int		*stash;
	
	if (ac - 1 == 1)
		array = split_arg(ag);
	else if (ac - 1 != 4 || ac - 1 != 5)
		error("Wrong number input");
	if (array)
		stash = check_parsing(ac, array);
	else
		stash = check_parsing(ac, ag);
	initialize(stash, ac);
}

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