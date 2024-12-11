/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:33:01 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/11 15:59:34 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <libft.h>
# include <mlxe.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>

# include "parsing.h"
# include "engine.h"

typedef struct s_game
{
	t_window	*window;
	t_engine	engine;
	char		error_msg[256];
}	t_game;

int			print_error(char *msg);
t_bool		set_error(t_game *game, char *msg);

void		main_loop(t_window *window, void *data);

#endif
