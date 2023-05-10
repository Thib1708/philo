/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaultgiraudon <thibaultgiraudon@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:27:17 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/05/10 16:35:24 by thibaultgir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_args	*init_args(int argc, char **argv)
{
	t_args				*args;
	int					nb_philo;

	nb_philo = ft_atoi(argv[1]);
	args = malloc(sizeof(t_args));
	if (!args)
		msg_error("Error malloc");
	args->nb_philo = nb_philo;
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	args->n_eat = 0;
	args->is_dead = 0;
	pthread_mutex_init(&args->m_eat, NULL);
	pthread_mutex_init(&args->m_n_eat, NULL);
	if (argc == 6)
		args->must_eat = ft_atoi(argv[5]);
	else
		args->must_eat = -1;
	return (args);
}

void	ft_free(t_philo **philo, t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->nb_philo)
	{
		pthread_join(philo[i]->thread, NULL);
		free(philo[i]);
	}
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
	args->time = ft_time();
	while (++i < args->nb_philo)
	{
		philo[i]->args = args;
		philo[i]->index = i + 1;
		philo[i]->t_last_eat = 0;
		philo[i]->nb_eat = 0;
		pthread_mutex_init(&philo[i]->l_fork, NULL);
		pthread_mutex_init(philo[i]->r_fork, NULL);
		if (i != args->nb_philo - 1)
			philo[i]->r_fork = &philo[i + 1]->l_fork;
		else
			philo[i]->r_fork = &philo[0]->l_fork;
		if (pthread_create(&philo[i]->thread, NULL, ft_philo, philo[i]))
			msg_error("Error thread");
	}
	ft_check_death(philo, args);
	ft_free(philo, args);
}

int	main(int argc, char **argv)
{
	t_args	*args;

	ft_check_args(argc, argv);
	args = init_args(argc, argv);
	ft_create_philo(args);
	free(args);
	return (0);
}
