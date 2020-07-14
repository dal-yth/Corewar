/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolopov <asolopov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 12:21:48 by asolopov          #+#    #+#             */
/*   Updated: 2020/07/14 15:26:24 by asolopov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

/*
** inits operation struct
*/

t_operation	*init_op(t_operation *op)
{
	t_operation *new;
	int			cnt;

	cnt = 0;
	new = (t_operation *)malloc(sizeof(t_operation));
	new->arg_type_code = 0;
	new->opname = NULL;
	new->t_dir_size = 0;
	while (cnt < 5)
	{
		new->arg[cnt] = NULL;
		new->argtypes[cnt] = 0;
		cnt += 1;
	}
	return (new);
}

/*
** inits core struct
*/

t_deasm		*initialize_deasm(char *filename)
{
	t_deasm	*core;
	char	*target_file;

	core = (t_deasm *)ft_memalloc(sizeof(t_deasm));
	if (!core)
		ft_error_exit("DeAsm malloc error", 0, 0);
	target_file = filename_pars(filename, SRC_TYPE, TRGT_TYPE);
	if (!target_file)
		ft_error_exit("Incorrect file type", (void *)core, clear_t_deasm);
	core->source_fd = open(filename, O_RDONLY);
	if (core->source_fd < 0)
		ft_error_exit("Couldn't open source", (void *)core, clear_t_deasm);
	core->target_fd = open(target_file, O_RDWR | O_CREAT, 0600);
	if (core->target_fd < 0)
		ft_error_exit("Couldn't open target", (void *)core, clear_t_deasm);
	free(target_file);
	return (core);
}

/*
** clears core struct
*/

void	clear_t_deasm(void *object)
{
	free(((t_deasm*)object)->champ_name);
	free(((t_deasm*)object)->champ_comment);
	free(((t_deasm*)object)->raw_code);
	free(object);
}
