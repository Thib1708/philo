/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:05:08 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/08/23 18:35:47 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_swap_fork(t_philo *philo)
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

	while(1)
	{
		pthread_mutex_lock(&args->m_stop);
		if (philo->is_dead)
		{
			pthread_mutex_unlock(&args->m_stop);
			return (1);
		}
		pthread_mutex_unlock(&args->m_stop);
		pthread_mutex_lock(&args->m_forks[fork]);
		if (args->all_forks[fork] == 0)
			break ;
		pthread_mutex_unlock(&args->m_forks[fork]);
		usleep(10);
	}
	args->all_forks[fork] = 1;
	pthread_mutex_unlock(&args->m_forks[fork]);
		pthread_mutex_lock(&args->m_stop);
	if (philo->is_dead)
		return (pthread_mutex_unlock(&args->m_stop), 1);
	pthread_mutex_unlock(&args->m_stop);
	ft_print(philo, "has taken a fork");
	return (0);
}

static int	ft_take_forks(t_philo *philo, t_args *args)
{
		// ft_swap_fork(philo);
	if (ft_take_one_fork(philo, args, philo->l_fork))
		return (1);
	if (ft_take_one_fork(philo, args, philo->r_fork))
		return (1);
	return (0);
}

static void	ft_free_fork(t_args *args, int fork)
{
	pthread_mutex_lock(&args->m_forks[fork]);
	args->all_forks[fork] = 0;
	pthread_mutex_unlock(&args->m_forks[fork]);
}

static int	ft_eat(t_philo *philo, t_args *args)
{
	if (ft_take_forks(philo, args))
		return (1);
	pthread_mutex_lock(&args->m_stop);
	if (philo->is_dead)
		return (pthread_mutex_unlock(&args->m_stop), 1);
	pthread_mutex_unlock(&args->m_stop);
	ft_print(philo, "is eating");
	pthread_mutex_lock(&args->m_stop);
	philo->t_last_eat = ft_current_time(args->time);
	philo->nb_eat++;
	pthread_mutex_unlock(&args->m_stop);
	ft_usleep(args->t_eat, philo);
	pthread_mutex_lock(&args->m_stop);
	if (philo->is_dead)
		return (pthread_mutex_unlock(&args->m_stop), 1);
	pthread_mutex_unlock(&args->m_stop);
	ft_print(philo, "is sleeping");
	ft_free_fork(args, philo->l_fork);
	ft_free_fork(args, philo->r_fork);
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
	ft_print(philo, "is thinking");
	if (args->nb_philo == 1)
		return (ft_print(philo, "has taken a fork"), NULL);
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
