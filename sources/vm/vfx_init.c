/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vfx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 08:34:02 by jnovotny          #+#    #+#             */
/*   Updated: 2020/08/07 07:09:13 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		get_term_size(int *height, int *width)
{
	struct winsize	ws;

	ws.ws_col = 0;
	ws.ws_row = 0;
	ws.ws_xpixel = 0;
	ws.ws_ypixel = 0;
	if (ioctl(0, TIOCGWINSZ, &ws) < 0)
		vm_error("Failed to retrieve terminal size");
	*height = ws.ws_row;
	*width = ws.ws_col;
}

static t_win	*init_window(int height, int width, int x, int y)
{
	t_win	*window;

	window = (t_win *)ft_memalloc(sizeof(t_win));
	if (!window)
		vm_error("Malloc at init_window");
	window->win = newwin(height, width, y, x);
	window->height = height;
	window->width = width;
	window->x = x;
	window->y = y;
	return (window);
}

static void		vfx_config(t_vs *settings)
{
	settings->freq = VFX_INIT_SPEED;
	initscr();
	keypad(stdscr, true);
	nodelay(stdscr, true);
	curs_set(0);
	cbreak();
	noecho();
	if (!(settings->car_map = \
		(uint8_t *)ft_memalloc(sizeof(uint8_t) * MEM_SIZE)))
		vm_error("Malloc at vfx_config [car_map]");
}

static void		init_visual_settings(t_vs *settings)
{
	int		height;
	int		width;

	get_term_size(&height, &width);
	vfx_config(settings);
	settings->arena = init_window(MEM_SIZE / VFX_WIDTH + 2,\
		VFX_WIDTH * 2 + 2, 0, 0);
	if (width > settings->arena->width)
		settings->info = init_window(VFX_INFO_H,\
			width - settings->arena->width + 1, settings->arena->x +\
				settings->arena->width - 1, settings->arena->y);
	else
		settings->info = init_window(settings->arena->height, VFX_INFO_STD,\
		settings->arena->x + settings->arena->width - 1, settings->arena->y);
	if (height > settings->arena->height + VFX_LEGEND_STD)
		settings->legend = init_window(height - settings->arena->height + 1,\
			width, 0, settings->arena->height - 1);
	else
		settings->legend = init_window(VFX_LEGEND_STD, width, 0,\
			settings->arena->height - 1);
	settings->log = init_window(settings->arena->height - VFX_INFO_H + 1,\
		settings->info->width, settings->info->x, VFX_INFO_H - 1);
	scrollok(settings->log->win, true);
	wprintw(settings->log->win, "\n");
	refresh();
}

void			init_vfx_arena(t_vm *core)
{
	if (!(core->vfx = (t_vs *)ft_memalloc(sizeof(t_vs))))
		vm_error("Malloc at init_vfx_arena");
	init_visual_settings(core->vfx);
	vfx_colors();
}
