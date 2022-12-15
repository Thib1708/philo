/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:27:17 by tgiraudo          #+#    #+#             */
/*   Updated: 2022/12/15 13:25:44 by tgiraudo         ###   ########.fr       */
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
	args->time = ft_time();
	args->nb_philo = nb_philo;
	args->t_die = ft_atoi(argv[2]);
	args->t_eat = ft_atoi(argv[3]);
	args->t_sleep = ft_atoi(argv[4]);
	args->n_eat = 0;
	pthread_mutex_init(&args->eat, NULL);
	if (argc == 6)
		args->must_eat = ft_atoi(argv[5]) * nb_philo;
	else
		args->must_eat = -1;
	return (args);
}

void	ft_create_philo(t_args *args)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * args->nb_philo);
	i = 0;
	while (++i <= args->nb_philo)
	{
		philo[i].args = args;
		philo[i].index = i;
		philo[i].t_last_eat = 0;
		pthread_mutex_init(&philo[i].l_fork, NULL);
		if (i != args->nb_philo)
			philo[i].r_fork = &philo[i + 1].l_fork;
		else
			philo[i].r_fork = &philo[1].l_fork;
		if (pthread_create(&philo[i].thread, NULL, ft_philo, &philo[i]))
		{
			free(philo);
			msg_error("Error thread");
		}
	}
	i = -1;
	while (++i < args->nb_philo)
	{
		pthread_join (philo[i].thread, NULL);
	}
}

int	main(int argc, char **argv)
{
	t_args	*args;

	(void)argv;
	if (argc < 5 || argc > 6)
		msg_error("Pleaser enter 4 or 5 argument");
	ft_time();
	args = init_args(argc, argv);
	ft_create_philo(args);
	return (0);
}
