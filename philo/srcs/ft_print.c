/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:34:12 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/08/23 18:52:28 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->args->m_stop);
	if (philo->args->is_dead)
	{
		pthread_mutex_unlock(&philo->args->m_stop);
		return ;
	}
	pthread_mutex_lock(&philo->args->m_print);
	if (!philo->args->is_dead)
	{
		printf("%lli %d %s\n",
			ft_time() - philo->args->time, philo->index, str);
	}
	pthread_mutex_unlock(&philo->args->m_print);
	pthread_mutex_unlock(&philo->args->m_stop);
}
