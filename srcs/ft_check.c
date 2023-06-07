/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thibaultgiraudon <thibaultgiraudon@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:10:10 by tgiraudo          #+#    #+#             */
/*   Updated: 2023/06/07 12:39:49 by thibaultgir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	ft_check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (argc < 5 || argc > 6)
		ft_error("number of argument different of 4 or 5");
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] > '9' || argv[i][j] < '0')
			{
				if (argv[i][j] == '-')
					ft_error("negative integer");
				ft_error("non digit character");
			}
		}
	}
}
