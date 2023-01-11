/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:57:45 by anoukmechai       #+#    #+#             */
/*   Updated: 2023/01/08 15:27:36 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_struct(t_pack *pack)
{
	int	i;

	i = 0;
	if (pack)
	{
		if (pack->philos)
		{
			while (i < pack->table->nbr_philos)
				free(pack->philos[i++]);
		}
		if (pack->table)
			free(pack->table->mutex);
		free(pack->philos);
		free(pack->table);
		free(pack);
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_pars(t_pars *pars)
{
	if (pars)
	{
		free_array(pars->array);
		free(pars->stash);
		free(pars);
	}
}

void	error_exit(char *str, t_pack *pack)
{
	printf("%s\n", str);
	free_struct(pack);
	exit(1);
}

void	error_parsing(char *str, t_pars *pars)
{
	printf("%s\n", str);
	free_pars(pars);
	exit(1);
}
