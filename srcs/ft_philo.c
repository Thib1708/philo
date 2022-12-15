/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:05:08 by tgiraudo          #+#    #+#             */
/*   Updated: 2022/12/15 17:23:29 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	*ft_philo(void *s)
{
	t_philo		*philo;
	t_args		*args;
	pthread_t	died;

	philo = (t_philo *)s;
	args = (t_args *)philo->args;
	if (philo->index % 2 == 0)
		ft_usleep(args->t_eat / 10);
	if (pthread_create(&died, NULL, is_dead, philo))
		msg_error("Error thread");
	while (1)
	{
		ft_take_fork(philo, args);
		if (args->n_eat >= args->must_eat - 1 && args->must_eat > 0)
			exit(0);
		ft_sleep(philo);
		ft_usleep(args->t_sleep);
		ft_think(philo);
	}
	pthread_join(died, NULL);
	return (NULL);
}

void	ft_take_fork(t_philo *philo, t_args *args)
{
	pthread_mutex_lock(&philo->l_fork);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	ft_print(philo, "has taken a fork");
	ft_eat(philo, args);
}

void	ft_eat(t_philo *philo, t_args *args)
{
	ft_print(philo, "is eating");
	philo->t_last_eat = ft_current_time(args->time);
	ft_usleep(args->t_eat);
	pthread_mutex_lock(&philo->args->eat);
	args->n_eat++;
	pthread_mutex_unlock(&args->eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
}

void	ft_think(t_philo *philo)
{
	ft_print(philo, "is thinking");
}
