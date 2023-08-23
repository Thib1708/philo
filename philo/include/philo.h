/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:26:17 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/08/23 08:40:37 by tgiraudo         ###   ########.fr       */
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

# define INT_MAX 2147483647

typedef struct s_args
{
	long long int	time;
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				fork;
	int				n_eat;
	int				is_dead;
	pthread_mutex_t	*m_forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_stop;
}	t_args;

typedef struct s_philo
{
	t_args			*args;
	int				index;
	long long		t_last_eat;
	int				nb_eat;
	int				l_fork;
	int				r_fork;
	int				nb_fork;
	int				is_dead;
	pthread_t		thread;
}	t_philo;

t_args		*ft_init_args(int argc, char **argv);
void		ft_create_philo(t_args *args);
void		ft_check_args(int argc, char **argv);
void		*ft_philo(void *s);
void		ft_print(t_philo *philo, char *str);
void		ft_error(char *msg);
long long	ft_time(void);
int			ft_atoi(const char *str);
long long	ft_current_time(long long int time);
void		ft_usleep(int ms, t_philo *philo);

int			ft_check_philo(t_philo **philo, t_args *args);
void		ft_free(t_philo **philo, t_args *args);
void		ft_destroy_mutex(t_args *args);
int			ft_check_is_dead(t_philo *philo, t_args *args);

#endif