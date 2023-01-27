/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:05:08 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/01/27 15:47:47 by tgiraudo         ###   ########.fr       */
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
	while (1)
	{
		pthread_create(&died, NULL, is_dead, philo);
		ft_take_fork(philo, args);
		ft_eat(philo, args);
		pthread_detach(died);
		if (philo->nb_eat == args->must_eat)
		{
			pthread_mutex_lock(&args->m_n_eat);
			if (++args->n_eat == args->nb_philo)
			{
				pthread_mutex_unlock(&args->m_n_eat);
				exit(0);
			}
			pthread_mutex_unlock(&args->m_n_eat);
			return (NULL);
		}
	}
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
	pthread_mutex_lock(&philo->args->m_eat);
	philo->t_last_eat = ft_current_time(args->time);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->args->m_eat);
	ft_usleep(args->t_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	ft_print(philo, "is sleeping");
	ft_usleep(args->t_sleep);
	ft_print(philo, "is thinking");
}

void	*is_dead(void *s)
{
	t_philo	*p;

	p = (t_philo *)s;
	ft_usleep(p->args->t_die + 1);
	pthread_mutex_lock(&p->args->m_eat);
	pthread_mutex_lock(&p->args->m_n_eat);
	if (ft_current_time(p->args->time) - p->t_last_eat > p->args->t_die)
	{
		pthread_mutex_unlock(&p->args->m_eat);
		pthread_mutex_unlock(&p->args->m_n_eat);
		ft_print(p, "died");
		exit(0);
	}
	pthread_mutex_unlock(&p->args->m_eat);
	pthread_mutex_unlock(&p->args->m_n_eat);
	return (NULL);
}

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->args->print);
	printf("%lli %d %s\n",
		ft_time() - philo->args->time, philo->index, str);
	pthread_mutex_unlock(&philo->args->print);
}
