/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaultgiraudon <thibaultgiraudon@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:26:17 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/04/12 10:42:09 by thibaultgir      ###   ########.fr       */
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
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				fork;
	int				n_eat;
	int				is_dead;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_n_eat;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
}	t_args;

typedef struct s_philo
{
	t_args			*args;
	int				index;
	long long		t_last_eat;
	int				nb_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;
	pthread_t		thread;
}	t_philo;

/**************************MAIN**************************/
t_args		*init_args(int argc, char **argv);
void		ft_create_philo(t_args *args);

/**************************CHECK*************************/
void		ft_check_args(int argc, char **argv);

/**************************PHILO*************************/
void		*ft_philo(void *s);
void		ft_eat(t_philo *philo, t_args *args);
void		ft_take_fork(t_philo *philo, t_args *args);
void		*is_dead(void *s);
void		ft_print(t_philo *philo, char *str);

/**************************UTILS*************************/
void		msg_error(char *msg);
long long	ft_time(void);
int			ft_atoi(const char *str);
long long	ft_current_time(long long int time);
void		ft_usleep(int ms);

#endif