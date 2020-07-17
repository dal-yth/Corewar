/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deasm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 12:42:40 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/14 15:16:46 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

int		main(int argc, char **argv)
{
	t_deasm *core;

	if (argc == 2)
	{
		core = initialize_deasm(argv[1]);
		read_file(core, core->source_fd);
		decode_exec(core, core->raw_code);
		clear_t_deasm(core);
	}
	else
		ft_printf("./deasm <filename.cor>");
}