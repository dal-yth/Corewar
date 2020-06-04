/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnovotny <jnovotny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:48:02 by jnovotny          #+#    #+#             */
/*   Updated: 2020/06/04 12:38:24 by jnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "libft.h"
# include "ft_error.h"

typedef struct	s_asm
{
	int		source_fd;
	int		core_fd;
}				t_asm;

/*
** ASM struct utilities
*/

void	clear_t_asm(t_asm *object);
char	*filename_pars(const char *source, const char *src_type,\
		const char *target_type);

#endif