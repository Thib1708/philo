/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:00:00 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/08/22 16:16:51 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *msg)
{
	printf("\033[1;31m[Error]\033[0m : %s\n", msg);
	exit (0);
}

long long int	ft_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

long long int	ft_current_time(long long int time)
{
	return (ft_time() - time);
}

void	ft_usleep(int ms, t_philo *philo)
{
	long int	time;

	time = ft_time();
	pthread_mutex_lock(&philo->args->m_stop);
	while (ft_time() - time < ms && !philo->is_dead)
	{
		pthread_mutex_unlock(&philo->args->m_stop);
		usleep(ms / 10);
		pthread_mutex_lock(&philo->args->m_stop);
	}
	pthread_mutex_unlock(&philo->args->m_stop);
}
