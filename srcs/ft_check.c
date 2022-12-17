/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgiraudo <tgiraudo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:10:10 by tgiraudo          #+#    #+#             */
/*   Updated: 2022/12/16 17:11:40 by tgiraudo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	ft_check_args(int argc, char **argv)
{
	int i;
	int j;

	i = 0;
	if (argc < 5 || argc > 6)
		msg_error("number of argument different of 4 or 5");
	while (argv[++i])
	{
		j = -1;
		while(argv[i][++j])
		{
			if(argv[i][j] > '9' || argv[i][j] < '0')
			{
				if (argv[i][j] == '-')
					msg_error("negative integer");
				msg_error("non digit character");
			}
		}
	}
}
