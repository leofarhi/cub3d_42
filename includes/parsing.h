/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:27:00 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/12 14:37:06 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define TEST_MAP	"map.cub"

# include <limits.h>
# include <fcntl.h>

# include <libft.h>
# include <mlxe.h>
# include <mlxe_structs.h>

# define ERROR			-1
# define SIZE_EXT		4
# define MIN_RGB_COLOR	0
# define MAX_RGB_COLOR	255
# define MIN_RGB_LENGTH	1
# define MAX_RGB_LENGTH	3

# define COMMA_CHAR	','
# define NL_CHAR	'\n'

# define CUB_EXT	".cub"

# define COLOR_FLOOR	"F"
# define COLOR_CEILING	"C"

# define TEXTURE_NORTH	"NO"
# define TEXTURE_SOUTH	"SO"
# define TEXTURE_WEST	"WE"
# define TEXTURE_EAST	"EA"

typedef enum e_state
{
	PARSING_MAP,
	PARSING_OTHER,
}	t_state;

/*
in map: replace player direction by empty tile
*/
typedef enum e_tile_id
{
	EMPTY	= 0,
	WALL	= 1,
	DOOR	= 2,
	VOID	= INT_MAX,
}	t_tile_id;

typedef struct s_tile
{
	t_tile_id	id;
	t_list		*entities;
}	t_tile;


/*
for textures: from path relative to the map to path relative to the program
for t_colors: mlx_color(r, g, b)
*/
typedef struct s_map
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	t_color		f;
	t_color		c;
	t_tile		**grid;
	size_t		width;
	size_t		height;
	t_vector2	start_coords;
	char		start_direction;
}	t_map;

typedef struct s_parsing
{
	char	*line;
	t_list	*cub;
	t_map	*map;
	t_state	state;
}	t_parsing;

t_map	*parsing(char *path);

void	get_cub(t_parsing *parsing, char *path);
void	init_parsing(t_parsing *parsing);

void	*free_map(t_map *map);
void	*free_parsing(t_parsing *parsing);
void	*parsing_error(char *error);

#endif
