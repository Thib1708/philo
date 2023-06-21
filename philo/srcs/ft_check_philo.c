/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:47:36 by thibaultgir       #+#    #+#             */
/*   Updated: 2023/06/21 12:42:23 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_death(t_philo **philo, t_args *args, int *n_eat)
{
	int	i;

	i = -1;
	while (++i < args->nb_philo)
	{
		if (ft_current_time(args->time) - philo[i]->t_last_eat > args->t_die)
		{
			printf("%lli %d %s\n",
				ft_time() - philo[i]->args->time, philo[i]->index, \
				"\033[0;31mdied\033[0m");
			pthread_mutex_lock(&args->m_print);
			args->is_dead = 1;
			pthread_mutex_unlock(&args->m_print);
			return (1);
		}
		if (args->must_eat > -1 && philo[i]->nb_eat >= args->must_eat)
			*n_eat += 1;
	}
	return (0);
}

int	ft_check_philo(t_philo **philo, t_args *args)
{
	int	n_eat;

	while (1)
	{
		n_eat = 0;
		ft_usleep(1);
		pthread_mutex_lock(&args->m_stop);
		if (ft_check_death(philo, args, &n_eat))
		{
			pthread_mutex_unlock(&args->m_stop);
			return (1);
		}
		pthread_mutex_unlock(&args->m_stop);
		if (args->nb_philo == n_eat)
		{
			return (1);
		}
	}
	return (0);
}
