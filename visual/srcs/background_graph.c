/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_graph.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlett <acarlett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 15:02:00 by acarlett          #+#    #+#             */
/*   Updated: 2020/10/01 21:54:29 by acarlett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visualizer.h"

void		draw_and_move_ant(t_visual *vis, t_map_data *data, t_paths **paths)
{
	t_paths		*tmp1;
	t_room_list	*buff;

	buff = data->rooms;
	tmp1 = (*paths);
	while ((*paths) != NULL)
	{
		if ((*paths)->start)
		{
			draw_ant_on_start(paths, vis, data, buff);
		}
		else if ((*(*paths)->id_list) == -1)
		{
			draw_ant_on_finish(paths, vis, data, buff);
		}
		else
		{
			while (buff->next != NULL && buff->room_data->id != (*(*paths)->id_list))
				buff = buff->next;
			(*paths)->id_list++;
			
			just_draw_ant_on_graph(paths, vis, buff);

			buff = data->rooms;
			(*paths) = (*paths)->prev;
		}
	}
	(*paths) = tmp1;
}

void		reload_solution_display(t_map_data *data, t_visual *vis)
{
	while (vis->paths->prev != NULL)
	{
		vis->paths->id_list = vis->paths->id_list_root;
		vis->paths->start = 1;
		vis->paths = vis->paths->prev;
		if (vis->paths->prev == NULL)
		{
			vis->paths->start = 1;
			vis->paths->id_list = vis->paths->id_list_root;
		}
		SDL_RenderPresent(vis->rend);
	}
}

bool		keys_managment(t_visual *vis, t_map_data *data)
{
	if (vis->event.type == SDL_QUIT)
		vis->run = false;
	if (vis->event.type == SDL_MOUSEBUTTONDOWN)
		vis->run = false;
	if (vis->event.type == SDL_KEYDOWN)
	{
		if (vis->event.key.keysym.sym == SDLK_x)
			vis->loop = !(vis->loop);
		if (vis->event.key.keysym.sym == SDLK_z)
			reload_solution_display(data, vis);
	}
	return (vis->run);
}

void		draw_background(t_visual *vis, t_map_data *data)
{
	vis->pos.w = WIDTH;
	vis->pos.h = HEIGHT;
	vis->pos.x = 0;
	vis->pos.y = 0;
	SDL_RenderCopy(vis->rend, vis->back, NULL, &(vis->pos));
	vis->pos.w = 180;
	vis->pos.h = 130;
	vis->pos.x = 20;
	vis->pos.y = 1050;
	SDL_RenderCopy(vis->rend, vis->logo_21, NULL, &(vis->pos));
}

void		background_graph(t_visual *vis, t_map_data *data)
{
	int			tmp_id;

	while (vis->run)
	{
		while (SDL_PollEvent(&(vis->event)))
		{
			vis->run = keys_managment(vis, data);
		}
		if (vis->loop)
			continue ;
		tmp_id = vis->paths->id_list[0];
		while (vis->paths->next != NULL && vis->paths->next->id_list[0] != tmp_id)
			vis->paths = vis->paths->next;
		draw_background(vis, data);
		draw_links(vis, data);
		draw_node(vis, data);
		draw_and_move_ant(vis, data, &(vis->paths));
		
		if (vis->paths->next != NULL)
			vis->paths = vis->paths->next;

		SDL_RenderPresent(vis->rend);

	}
}

void		destroy_all_quit(t_visual *vis)
{
	SDL_DestroyRenderer(vis->rend);
	SDL_DestroyWindow(vis->win);
	SDL_Quit();
}