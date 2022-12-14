/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:05:08 by tgiraudo          #+#    #+#             */
/*   Updated: 2022/12/14 18:16:31 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	*ft_philo(void *s)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)s;
	i = -1;
	while (1)
	{
		ft_eat(philo);
		usleep(philo->args->eat * 1000);
		ft_sleep(philo);
		usleep(philo->args->sleep * 1000);
		ft_think(philo);
	}
	return (NULL);
}

void	ft_eat(t_philo *philo)
{
	ft_print(philo, "is eating");
}

void	ft_sleep(t_philo *philo)
{
	ft_print(philo, "is sleeping");
}

void	ft_think(t_philo *philo)
{
	ft_print(philo, "is thinking");
}
