/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:27:17 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/06/13 18:04:55 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

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
		philo[i]->args->time = ft_time();
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
