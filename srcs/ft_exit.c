/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaultgiraudon <thibaultgiraudon@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:38:31 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/05/02 16:14:50 by thibaultgir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_exit(t_philo *philo)
{
    // free(philo->args);
    // free(philo);
    (void)philo;
    exit(0);
}