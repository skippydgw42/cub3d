/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_contact.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 13:50:35 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/09/22 17:08:40 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

static int map[MAP_HEIGHT][MAP_WIDHT] = {
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
	{1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
	{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int	ft_angle(double angle)
{
	if (angle > 0 && angle < PI / 2)
		return (1);
	else if (angle > PI / 2 && angle < PI)
		return (2);
	else if (angle > PI && angle < 3 * PI / 2)
		return (3);
	else if (angle > 3 * PI / 2 && angle < 2 * PI)
		return (4);
	return (0);
}

int	ft_check_around(int x, int y, double angle)
{
	int	val;

	val = ft_angle(angle);
	if (val == 1)
	{
		if (map[y][x] == 1 || map[y - 1][x] == 1 || map[y][x - 1] == 1)
			return (1);
	}
	if (val == 2)
	{
		if (map[y][x] == 1 || map[y - 1][x] == 1 || map[y][x + 1] == 1)
			return (1);
	}
	if (val == 3)
	{
		if (map[y - 1][x] == 1 || map[y][x] == 1 || map[y - 1][x + 1] == 1)
			return (1);
	}
	if (val == 4)
	{
		if (map[y - 1][x - 1] == 1 || map[y - 1][x] == 1 || map[y][x] == 1)
			return (1);
	}
	return (0);
}

int ft_check_wall(int x, int y, double angle, int rev)
{
	if (y / SIZE_CUBE > MAP_HEIGHT || x / SIZE_CUBE > MAP_WIDHT || y < 0 || x < 0)
		return (0);
	if (y % 32 == 0 && x % 32 == 0 && rev)
	{
		if (ft_check_around(x / SIZE_CUBE, y / SIZE_CUBE, angle))
			return (1);
	}
	return (map[y / SIZE_CUBE][x / SIZE_CUBE]);
}
