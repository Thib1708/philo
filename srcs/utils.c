/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:00:00 by tgiraudo          #+#    #+#             */
/*   Updated: 2022/12/14 16:14:57 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	msg_error(char *msg)
{
	ft_printf("%s\n", msg);
	exit (0);
}

long long int	ft_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

long long int	ft_current_time(long long int time)
{
	return (ft_time() - time);
}

void	ft_print(t_args *args, char *str)
{
	printf("\033[1;32m%lli \033[0m%d %s\n", ft_current_time(args->time), args->philo->index, str);
}
