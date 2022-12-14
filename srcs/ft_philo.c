/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:05:08 by tgiraudo          #+#    #+#             */
/*   Updated: 2022/12/14 15:41:51 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	*ft_philo(void *s)
{
	int		i;
	t_args	*args;

	args = (t_args *)s;
	i = -1;
	while (1)
	{
		ft_eat(args);
		usleep(args->eat * 1000);
	}
	return (NULL);
}

void	ft_eat(t_args *args)
{
	ft_print(args, "is eating");
}