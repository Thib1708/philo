/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:05:08 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/06/13 11:55:14 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	*ft_philo(void *s)
{
	t_philo		*philo;
	t_args		*args;

	philo = (t_philo *)s;
	args = (t_args *)philo->args;
	if (philo->index % 2)
		ft_usleep(1);
	if (args->nb_philo == 1)
	{
		ft_print(philo, "is thinking");
		ft_print(philo, "\033[0;34mhas taken a fork\033[0m");
		return (NULL);
	}
	while (!philo->is_dead)
	{
		ft_print(philo, "is thinking");
		if (ft_eat(philo, args))
			return (NULL);
		ft_print(philo, "\033[0;33mis sleeping\033[0m");
		ft_usleep(args->t_sleep);
	}
	return (NULL);
}

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

int	ft_take_fork(t_philo *philo, t_args *args)
{
	ft_swap_fork(philo);
	pthread_mutex_lock(&args->m_forks[philo->l_fork]);
	if (philo->is_dead)
	{
		pthread_mutex_unlock(&args->m_forks[philo->l_fork]);
		return (1);
	}
	ft_print(philo, "\033[0;34mhas taken a fork\033[0m");
	pthread_mutex_lock(&args->m_forks[philo->r_fork]);
	if (philo->is_dead)
	{
		pthread_mutex_unlock(&args->m_forks[philo->l_fork]);
		pthread_mutex_unlock(&args->m_forks[philo->r_fork]);
		return (1);
	}
	ft_print(philo, "\033[0;34mhas taken a fork\033[0m");
	return (0);
}

int	ft_eat(t_philo *philo, t_args *args)
{
	if (ft_take_fork(philo, args))
		return (1);
	ft_print(philo, "\033[0;35mis eating\033[0m");
	pthread_mutex_lock(&args->m_stop);
	philo->t_last_eat = ft_current_time(args->time);
	philo->nb_eat++;
	pthread_mutex_unlock(&args->m_stop);
	ft_usleep(args->t_eat);
	pthread_mutex_unlock(&args->m_forks[philo->l_fork]);
	pthread_mutex_unlock(&args->m_forks[philo->r_fork]);
	pthread_mutex_lock(&args->m_stop);
	if (philo->is_dead)
		return (pthread_mutex_unlock(&args->m_stop), 1);
	pthread_mutex_unlock(&args->m_stop);
	return (0);
}

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->args->m_print);
	if (!philo->is_dead)
	{
		printf("%lli %d %s\n",
			ft_time() - philo->args->time, philo->index, str);
	}
	pthread_mutex_unlock(&philo->args->m_print);
}
