/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:27:17 by tgiraudo          #+#    #+#             */
/*   Updated: 2022/12/13 18:44:51 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

t_args	*init_args(int argc, char **argv)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	args->nb_philo = ft_atoi(argv[1]);
	args->die = ft_atoi(argv[2]);
	args->eat = ft_atoi(argv[3]);
	args->sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->must_eat = ft_atoi(argv[5]);
	return (args);
}

void	ft_create_philo(t_args *args)
{
	
}

int	main(int argc, char **argv)
{
	t_args	*args;

	(void)argv;
	if (argc < 5 || argc > 6)
		msg_error("Pleaser enter 4 or 5 argument");
	args = init_args(argc, argv);
	ft_create_philo(args);
	return (0);
}
