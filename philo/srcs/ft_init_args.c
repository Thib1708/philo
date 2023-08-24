/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:04:44 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/08/24 08:13:27 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_mutex_init(t_args *args)
{
	int	i;

	args->m_forks = malloc(sizeof(pthread_mutex_t) * args->nb_philo);
	if (!args->m_forks)
		return (1);
	args->all_forks = malloc(sizeof(int) * args->nb_philo);
	if (!args->all_forks)
		return (free(args->m_forks), 1);
	i = -1;
	while (++i < args->nb_philo)
	{
		if (pthread_mutex_init(&args->m_forks[i], NULL))
			return (free(args->m_forks), free(args->all_forks), 1);
		args->all_forks[i] = 0;
	}
	if (pthread_mutex_init(&args->m_print, NULL))
		return (free(args->m_forks), free(args->all_forks), 1);
	if (pthread_mutex_init(&args->m_stop, NULL))
		return (free(args->m_forks), free(args->all_forks), 1);
	return (0);
}

t_args	*ft_init_args(int argc, char **argv)
{
	t_args				*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) < 1 || \
		ft_atoi(argv[2]) > INT_MAX || ft_atoi(argv[3]) < 60 || \
		ft_atoi(argv[3]) > INT_MAX || ft_atoi(argv[3]) < 60 || \
		ft_atoi(argv[4]) > INT_MAX || ft_atoi(argv[4]) < 60)
		return (printf("Error argv"), NULL);
	args->nb_philo = ft_atoi(argv[1]);
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	args->n_eat = 0;
	args->is_dead = 0;
	if (ft_mutex_init(args))
		return (free(args), NULL);
	if (argc == 6)
		args->must_eat = ft_atoi(argv[5]);
	else
		args->must_eat = -1;
	return (args);
}
