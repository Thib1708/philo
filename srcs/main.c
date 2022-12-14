/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:27:17 by tgiraudo          #+#    #+#             */
/*   Updated: 2022/12/14 16:12:41 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_args	*init_args(int argc, char **argv)
{
	t_args				*args;
	int					nb_philo;

	nb_philo = ft_atoi(argv[1]);
	args = malloc(sizeof(t_args));
	args->philo = malloc(sizeof(t_philo) * nb_philo);
	if (!args)
		msg_error("Error malloc");
	args->time = ft_time();
	args->nb_philo = nb_philo;
	args->die = ft_atoi(argv[2]);
	args->eat = ft_atoi(argv[3]);
	args->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->must_eat = ft_atoi(argv[5]);
	else
		args->must_eat = 0;
	return (args);
}

void	ft_create_philo(t_args *args)
{
	int	ret;
	int	i;

	i = -1;
	while (++i < args->nb_philo)
	{
		args->philo[i].index = i;
		ret = pthread_create(&args->philo[i].thread, NULL, ft_philo, (void *)args);
		if (ret)
		{
			free(args->philo);
			msg_error("Error thread");
		}
	}
	i = -1;
	while (++i < args->nb_philo)
	{
		pthread_join (args->philo[i].thread, NULL);
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
