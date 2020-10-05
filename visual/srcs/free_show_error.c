/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_show_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 17:29:47 by acarlett          #+#    #+#             */
/*   Updated: 2020/10/05 18:22:40 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

void		free_show_error(t_map_data *data)
{
	free_data(data);
	ft_putstr("Exit Code: ");
	ft_putnbr(MALLOC_ERROR);
	write (1, "\n", 1);
	exit(MALLOC_ERROR);
}