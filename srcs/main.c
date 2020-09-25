/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:39:05 by lmittie           #+#    #+#             */
/*   Updated: 2020/09/25 20:21:23 by lmittie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_structure(t_data *data) {
	(data)->ants_num = -1;
	(data)->adjacency_matrix = NULL;
	(data)->rooms = NULL;
	(data)->rooms_number = 0;
	(data)->id_counter = 0;
	(data)->start = -1;
	(data)->end = -1;
}

void 	print_rooms_info(t_data data);

int		main(void)
{
	t_data data;

	init_structure(&data);
	parse_map(&data);
	dinic(&data);
//	print_ants(&data);

//	print_rooms_info(data);
	return (0);
}

void 	print_rooms_info(t_data data)
{
	printf("ants number: %d\n", data.ants_num);
	printf("rooms number: %d\n", data.rooms_number);
	while (data.rooms != NULL)
	{
			printf("room name: %s, room id: %lu, room input: %lu, room output: %lu, room coords: %d, %d, ",
				   data.rooms->room_data->name,
				   data.rooms->room_data->id,
				   data.rooms->room_data->input_id,
					data.rooms->room_data->output_id,
				   data.rooms->room_data->coords.x, data.rooms->room_data->coords.y);

			if (data.rooms->room_data->type == START)
				printf("room type: START\n");
			else if (data.rooms->room_data->type == END)
				printf("room type: END\n");
			else printf("room type: DEFAULT\n");
		data.rooms = data.rooms->next;
	}

	printf("matrix:\n");
	printf("   ");
	for (int i = 0; i < data.id_counter; ++i) {
		printf("%2d ", i);
	}
	printf(":\n");

	for (int i = 0; i < data.id_counter; ++i) {
		printf("%d: ", i);
		for (int j = 0; j < data.id_counter; ++j)
			printf("%2d ", data.adjacency_matrix[i][j]);
		printf("\n");
	}
	printf("\n");

	while (data.paths)
	{
		printf("path info: len = %d, ants_num = %d, dist to end = %d\n",
		 data.paths->path_data->length, data.paths->path_data->last_ant_id, data.paths->path_data->dist_from_end);
		for (int i = 0; i < data.paths->path_data->length; ++i)
			printf("%d ", data.paths->path_data->path[i]);
		printf("\n");
		data.paths = data.paths->next;
	}
}
