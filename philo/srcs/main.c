/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:27:17 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/08/22 16:10:22 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free_tab(t_philo **philo, int i)
{
	while (--i >= 0)
		free(philo[i]);
	free(philo);
}

static t_philo	*ft_init_philo(t_args *args, t_philo **philo, int i)
{
	(*philo)->args = args;
	(*philo)->index = i + 1;
	(*philo)->t_last_eat = 0;
	(*philo)->nb_eat = 0;
	(*philo)->is_dead = 0;
	(*philo)->l_fork = i;
	(*philo)->r_fork = (i + 1) % args->nb_philo;
	(*philo)->args->time = ft_time();
	return (*philo);
}

void	ft_create_philo(t_args *args)
{
	int		i;
	t_philo	**philo;

	philo = malloc(sizeof(t_philo) * args->nb_philo);
	if (!philo)
		return (ft_error("malloc"));
	i = -1;
	while (++i < args->nb_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (ft_destroy_mutex(args), ft_free_tab(philo, i), \
				ft_error("malloc"));
	}
	i = -1;
	pthread_mutex_lock(&args->m_stop);
	while (++i < args->nb_philo)
	{
		ft_init_philo(args, &philo[i], i);
		if (pthread_create(&philo[i]->thread, NULL, ft_philo, philo[i]))
			return (ft_free(philo, args));
	}
	pthread_mutex_unlock(&args->m_stop);
	ft_check_philo(philo, args);
	ft_free(philo, args);
}

int	main(int argc, char **argv)
{
	t_args	*args;

	ft_check_args(argc, argv);
	args = ft_init_args(argc, argv);
	if (!args)
		return (1);
	ft_create_philo(args);
	free(args);
	return (0);
}
