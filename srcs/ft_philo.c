/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaultgiraudon <thibaultgiraudon@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:05:08 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/05/04 10:22:19 by thibaultgir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	*ft_philo(void *s)
{
	t_philo		*philo;
	t_args		*args;

	philo = (t_philo *)s;
	args = (t_args *)philo->args;
	if (philo->index % 2 == 0)
		ft_usleep(1);
	while (!args->is_dead)
	{
		ft_print(philo, "is thinking");
		if (ft_take_fork(philo, args))
			return (NULL);
		if (ft_eat(philo, args))
			return (NULL);
	}
	return (NULL);
}

int	ft_take_fork(t_philo *philo, t_args *args)
{
	if (args->is_dead)
		return (1);
	pthread_mutex_lock(&philo->l_fork);
	ft_print(philo, "\033[0;34mhas taken a fork\033[0m");
	if (args->is_dead)
	{
		pthread_mutex_unlock(&philo->l_fork);
		return (1);
	}
	pthread_mutex_lock(philo->r_fork);
	ft_print(philo, "\033[0;34mhas taken a fork\033[0m");
	if (args->is_dead)
	{
		pthread_mutex_unlock(&philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	return (0);
}

int ft_eat(t_philo *philo, t_args *args)
{
	ft_print(philo, "\033[0;35mis eating\033[0m");
	philo->t_last_eat = ft_current_time(args->time);
	philo->nb_eat++;
	ft_usleep(args->t_eat);
	ft_print(philo, "\033[0;33mis sleeping\033[0m");
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (args->is_dead)
		return (1);
	ft_usleep(args->t_sleep);
	return (0);
}

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->args->print);
	if (!philo->args->is_dead)
	{
		printf("%lli %d %s\n",
			ft_time() - philo->args->time, philo->index, str);
	}
	pthread_mutex_unlock(&philo->args->print);
}
