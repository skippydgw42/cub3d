/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:56:31 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/11 12:09:22 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int	ft_char_val(char c, int ct)
{
	if (ct == 0)
	{
		if (c == 'N' || c == 'S')
			return (1);
		else if (c == 'W')
			return (2);
		else if (c == 'E')
			return (3);
	}
	else if (ct == 1 && c == 'O')
		return (4);
	else if (ct == 2 && c == 'E')
		return (4);
	else if (ct == 3 && c == 'A')
		return (4);
	return (0);
}

int	ft_go_to_path(char *str)
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	while (str[i] && ct != 4)
	{
		if (str[i])
		{
			ct = ft_char_val(str[i], ct);
			i++;
		}
		if (ct == -1)
			return (0);
		while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
			i++;
	}
	return (i);
}

char	*ft_get_path(char *str)
{
	int		i;
	int		j;
	char	*dst;

	dst = malloc(sizeof(char) * (ft_length_path(str) + 1));
	if (!dst)
		return (NULL);
	j = 0;
	i = ft_go_to_path(str);
	while (str[i] && i > 0)
	{
		if (str[i] != 32 && (str[i] < 9 || str[i] > 13))
		{
			dst[j] = str[i];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
	free(str);
	return (dst);
}
