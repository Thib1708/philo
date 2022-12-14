/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:26:17 by tgiraudo          #+#    #+#             */
/*   Updated: 2022/12/14 18:39:32 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_args
{
	long long int	time;
	int				nb_philo;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	int				fork;
	int				index;
}	t_args;

typedef struct s_philo
{
	t_args		*args;
	int			index;
	pthread_t	thread;
}	t_philo;

void		msg_error(char *msg);
long long	ft_time(void);
void		*ft_philo(void *s);
void		ft_print(t_philo *philo, char *str);
void		ft_eat(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
int			ft_atoi(const char *str);

#endif