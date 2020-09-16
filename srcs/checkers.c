/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmittie <lmittie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 18:34:59 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/15 18:34:59 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int 			size_of_matrix_rows(char **matrix)
{
	int counter;

	counter = 0;
	while (matrix[counter] != NULL)
	{
		if (!matrix[counter][0])
			return (10);
		counter++;
	}
	return (counter);
}

t_room_type		check_if_comment(char **line, t_data *data)
{
	t_room_type type;

	type = DEFAULT;
	if (!ft_strncmp(*line, "#", 1))
	{
		if (!ft_strcmp(*line, "##start"))
		{
			type = (data->start == -1) ? START : PARSE_ERROR;
		}
		if (!ft_strcmp(*line, "##end"))
		{
			type = (data->end == -1) ? END : PARSE_ERROR;
		}
		ft_strdel(line);
		get_next_line(0, line);
	}
	return type;
}