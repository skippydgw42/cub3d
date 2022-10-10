/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setparams.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:30:14 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/10 17:11:22 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int	ft_setparams(t_map *map, char *flat_map)
{
	int	x;

	x = ft_to_map(flat_map, 0);
	ft_take_texture(map, flat_map, x);
	ft_take_rgb_floor(map, flat_map, x);
	ft_take_rgb_ceiling(map, flat_map, x);
	return (x);
}
