/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:19:27 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/09/29 18:29:13 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

void	ft_free_2D_array(int heigth, int width, int **tab)
{
	(void)width;
	(void)tab;
	int	y;

	y = 0;
	while (y < heigth)
	{
		free(tab[y]);
		y++;
	}
	free(tab);
}
