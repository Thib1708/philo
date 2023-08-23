/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:05:08 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/08/23 08:41:05 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_swap_fork(t_philo *philo)
{
	int	swap;

	if (philo->l_fork < philo->r_fork)
	{
		swap = philo->l_fork;
		philo->l_fork = philo->r_fork;
		philo->r_fork = swap;
	}
}

static int	ft_take_one_fork(t_philo *philo, t_args *args, int fork)
{
	pthread_mutex_lock(&args->m_forks[fork]);
	pthread_mutex_lock(&args->m_stop);
	if (philo->is_dead)
	{
		pthread_mutex_unlock(&args->m_stop);
		pthread_mutex_unlock(&args->m_forks[fork]);
		return (1);
	}
	philo->nb_fork++;
	pthread_mutex_unlock(&args->m_stop);
	ft_print(philo, "has taken a fork");
	return (0);
}

static int	ft_take_forks(t_philo *philo, t_args *args)
{
	philo->nb_fork = 0;
	while (philo->nb_fork != 2)
	{
		usleep(10 * args->nb_philo);
		ft_swap_fork(philo);
		if (ft_take_one_fork(philo, args, philo->l_fork))
			return (1);
		if (ft_take_one_fork(philo, args, philo->r_fork))
			return (pthread_mutex_unlock(&args->m_forks[philo->l_fork]), 1);
	}
	return (0);
}

static int	ft_eat(t_philo *philo, t_args *args)
{
	if (ft_take_forks(philo, args))
		return (1);
	ft_print(philo, "is eating");
	pthread_mutex_lock(&args->m_stop);
	philo->t_last_eat = ft_current_time(args->time);
	philo->nb_eat++;
	pthread_mutex_unlock(&args->m_stop);
	ft_usleep(args->t_eat, philo);
	ft_print(philo, "is sleeping");
	pthread_mutex_unlock(&args->m_forks[philo->l_fork]);
	pthread_mutex_unlock(&args->m_forks[philo->r_fork]);
	ft_usleep(args->t_sleep, philo);
	pthread_mutex_lock(&args->m_stop);
	if (philo->is_dead)
		return (pthread_mutex_unlock(&args->m_stop), 1);
	pthread_mutex_unlock(&args->m_stop);
	return (0);
}

void	*ft_philo(void *s)
{
	t_philo		*philo;
	t_args		*args;

	philo = (t_philo *)s;
	args = (t_args *)philo->args;
	pthread_mutex_lock(&args->m_stop);
	pthread_mutex_unlock(&args->m_stop);
	if (philo->index % 2 == 0)
		ft_usleep(100, philo);
	if (args->nb_philo == 1)
	{
		ft_print(philo, "is thinking");
		return (ft_print(philo, "has taken a fork"), NULL);
	}
	while (1)
	{
		if (ft_check_is_dead(philo, args))
			break ;
		if (ft_eat(philo, args))
			return (NULL);
		ft_print(philo, "is thinking");
		if (ft_check_is_dead(philo, args))
			break ;
	}
	return (NULL);
}
