/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 17:51:25 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/08/22 16:03:49 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutex(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nb_philo)
		pthread_mutex_destroy(&args->m_forks[i]);
	pthread_mutex_destroy(&args->m_print);
	pthread_mutex_destroy(&args->m_stop);
}

void	ft_free(t_philo **philo, t_args *args)
{
	int	i;

	pthread_mutex_lock(&args->m_stop);
	args->is_dead = 1;
	pthread_mutex_unlock(&args->m_stop);
	i = -1;
	while (++i < args->nb_philo)
	{
		pthread_mutex_lock(&args->m_stop);
		pthread_mutex_lock(&args->m_print);
		philo[i]->is_dead = 1;
		pthread_mutex_unlock(&args->m_print);
		pthread_mutex_unlock(&args->m_stop);
	}
	i = -1;
	while (++i < args->nb_philo)
		pthread_join(philo[i]->thread, NULL);
	ft_destroy_mutex(args);
	i = -1;
	while (++i < args->nb_philo)
		free(philo[i]);
	free(args->m_forks);
	free(philo);
}
