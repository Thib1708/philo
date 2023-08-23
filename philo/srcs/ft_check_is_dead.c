/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_death.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 08:38:40 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/08/23 08:40:48 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_is_dead(t_philo *philo, t_args *args)
{
	pthread_mutex_lock(&args->m_stop);
	if (philo->is_dead)
	{
		pthread_mutex_unlock(&args->m_stop);
		return (1);
	}
	pthread_mutex_unlock(&args->m_stop);
	return (0);
}
