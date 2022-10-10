/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mini_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrinchi <ltrinchi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:02:20 by ltrinchi          #+#    #+#             */
/*   Updated: 2022/10/10 17:02:29 by ltrinchi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int	ft_check_map(t_data *data, int x, int y)
{
	if (x < 0 || y < 0)
		return (EXIT_FAILURE);
	if (x >= data->data_map.width || y >= data->data_map.height)
		return (EXIT_FAILURE);
	return (data->data_map.map[y][x]);
}
