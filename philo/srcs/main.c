/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:27:17 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/06/13 16:47:05 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	ft_mutex_init(t_args *args)
{
	int	i;

	args->m_forks = malloc(sizeof(pthread_mutex_t) * args->nb_philo);
	if (!args->m_forks)
		return (1);
	i = -1;
	while (++i < args->nb_philo)
		if (pthread_mutex_init(&args->m_forks[i], NULL))
			return (1);
	if (pthread_mutex_init(&args->m_print, NULL))
		return (1);
	if (pthread_mutex_init(&args->m_stop, NULL))
		return (1);
	return (0);
}

t_args	*init_args(int argc, char **argv)
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
		return (NULL);
	if (argc == 6)
		args->must_eat = ft_atoi(argv[5]);
	else
		args->must_eat = -1;
	return (args);
}

void	ft_free(t_philo **philo, t_args *args)
{
	int	i;

	pthread_mutex_lock(&args->m_stop);
	args->is_dead = 1;
	pthread_mutex_unlock(&args->m_stop);
	i = -1;
	while (++i < args->nb_philo)
	{
		pthread_mutex_lock(&args->m_stop);
		philo[i]->is_dead = 1;
		pthread_mutex_unlock(&args->m_stop);
	}
	i = -1;
	while (++i < args->nb_philo)
		pthread_join(philo[i]->thread, NULL);
	i = -1;
	while (++i < args->nb_philo)
		pthread_mutex_destroy(&args->m_forks[i]);
	i = -1;
	pthread_mutex_destroy(&args->m_print);
	pthread_mutex_destroy(&args->m_stop);
	while (++i < args->nb_philo)
		free(philo[i]);
	free(args->m_forks);
	free(philo);
}

void	ft_create_philo(t_args *args)
{
	int		i;
	t_philo	**philo;

	philo = malloc(sizeof(t_philo) * args->nb_philo);
	i = -1;
	while (++i < args->nb_philo)
		philo[i] = malloc(sizeof(t_philo));
	i = -1;
	pthread_mutex_lock(&args->m_stop);
	while (++i < args->nb_philo)
	{
		philo[i]->args = args;
		philo[i]->index = i + 1;
		philo[i]->t_last_eat = 0;
		philo[i]->nb_eat = 0;
		philo[i]->is_dead = 0;
		philo[i]->l_fork = i;
		philo[i]->r_fork = (i + 1) % args->nb_philo;
		if (pthread_create(&philo[i]->thread, NULL, ft_philo, philo[i]))
			return (ft_free(philo, args));
	}
	args->time = ft_time();
	pthread_mutex_unlock(&args->m_stop);
	ft_check_philo(philo, args);
	ft_free(philo, args);
}

int	main(int argc, char **argv)
{
	t_args	*args;

	ft_check_args(argc, argv);
	args = init_args(argc, argv);
	if (!args)
		return (1);
	ft_create_philo(args);
	free(args);
	return (0);
}
