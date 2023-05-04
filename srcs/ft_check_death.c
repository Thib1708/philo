/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_death.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaultgiraudon <thibaultgiraudon@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:47:36 by thibaultgir       #+#    #+#             */
/*   Updated: 2023/05/04 10:29:21 by thibaultgir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_death(t_philo **philo, t_args *args)
{
	int	i;
	
	while (1)
	{
		i = -1;
		args->n_eat = 0;
		while (++i < args->nb_philo)
		{
			if (args->must_eat > -1 && philo[i]->nb_eat >= args->must_eat)
				args->n_eat++;
			if (ft_current_time(args->time) - philo[i]->t_last_eat > args->t_die)
			{
				ft_print(philo[i], "\033[0;31mdied\033[0m");
				args->is_dead = 1;
				return (1);
			}
		}
		if (args->nb_philo == args->n_eat)
		{
			args->is_dead = 1;
			return (1);
		}
	}
	return (0);
}