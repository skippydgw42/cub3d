/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegraeu <mdegraeu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 15:04:46 by mdegraeu          #+#    #+#             */
/*   Updated: 2022/10/11 13:23:42 by mdegraeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inclds/cube.h"

int	ft_return(char *str)
{
	printf("%s\n", str);
	return (0);
}

int	ft_close_fd(int fd, int ret)
{
	if (fd > 1 && fd < 1024)
		close(fd);
	return (ret);
}