/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:00:00 by tgiraudo          #+#    #+#             */
/*   Updated: 2022/12/15 17:24:07 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	msg_error(char *msg)
{
	printf("%s\n", msg);
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

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->args->print);
	printf("\033[1;32m[%lli ms] \033[0m%d %s\n",
		ft_current_time(philo->args->time), philo->index, str);
	pthread_mutex_unlock(&philo->args->print);
}

void	*is_dead(void *s)
{
	t_philo	*p;

	p = (t_philo *)s;
	while(1)
	{
		if (ft_current_time(p->args->time) - p->t_last_eat > p->args->t_die)
		{
			ft_print(p, "died");
			exit(0);
		}
	}
	return (NULL);
}

void	ft_usleep(int ms)
{
	long int	time;

	time = ft_time();
	while (ft_time() - time < ms)
		usleep(ms / 10);
}
