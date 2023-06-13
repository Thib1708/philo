/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:00:00 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/06/13 16:29:38 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	ft_error(char *msg)
{
	printf("\033[1;31m[Error]\033[0m : %s\n", msg);
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

void	ft_usleep(int ms)
{
	long int	time;

	time = ft_time();
	while (ft_time() - time < ms)
		usleep(ms / 10);
}
