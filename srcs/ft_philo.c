/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:05:08 by tgiraudo          #+#    #+#             */
/*   Updated: 2022/12/16 15:22:43 by tgiraudo         ###   ########.fr       */
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
		ft_eat(philo, args);
		if (philo->nb_eat == args->must_eat)
		{
			pthread_mutex_lock(&philo->args->eat);
			if (++args->n_eat == args->nb_philo)
				exit(0);
			pthread_mutex_unlock(&args->eat);
			return (NULL);
		}
	}
	pthread_join(died, NULL);
	return (NULL);
}

void	ft_take_fork(t_philo *philo, t_args *args)
{
	(void)args;
	pthread_mutex_lock(&philo->l_fork);
	ft_print(philo, "has taken a fork");
	if (args->nb_philo == 1)
		return (ft_usleep(args->t_die + 1));
	pthread_mutex_lock(philo->r_fork);
	ft_print(philo, "has taken a fork");
}

void	ft_eat(t_philo *philo, t_args *args)
{
	ft_print(philo, "is eating");
	pthread_mutex_lock(&philo->args->eat);
	philo->t_last_eat = ft_current_time(args->time);
	philo->nb_eat++;
	pthread_mutex_unlock(&args->eat);
	ft_usleep(args->t_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	ft_print(philo, "is sleeping");
	ft_usleep(args->t_sleep);
	ft_print(philo, "is thinking");
}

void	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
}

void	ft_think(t_philo *philo)
{
	ft_print(philo, "is thinking");
}
