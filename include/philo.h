/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:26:17 by tgiraudo          #+#    #+#             */
/*   Updated: 2022/12/13 18:49:24 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/headers/ft_printf.h"
# include "../libft/headers/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
	int fork;
	pthread_t thread;
}

typedef struct s_args
{
	int	nb_philo;
	int	die;
	int	eat;
	int	sleep;
	int	must_eat;
}	t_args;

void	msg_error(char *msg);

#endif