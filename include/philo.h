/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:26:17 by tgiraudo          #+#    #+#             */
/*   Updated: 2022/12/14 15:53:16 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/headers/ft_printf.h"
# include "../libft/headers/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
#include <sys/time.h>
#include <stdio.h>

typedef struct s_philo
{
	int			index;
	pthread_t	thread;
}	t_philo;

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
	t_philo			*philo;
}	t_args;

void				msg_error(char *msg);
long long int		ft_time(void);
void				*ft_philo(void *s);
void				ft_print(t_args *args, char *str);
void				ft_eat(t_args *args);

#endif