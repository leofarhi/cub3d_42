/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfischof <pfischof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:27:00 by pfischof          #+#    #+#             */
/*   Updated: 2024/12/15 11:33:56 by pfischof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* --------------------------------- HEADERS -------------------------------- */

# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

# include <libft.h>
# include <mlxe.h>
# include <mlxe_structs.h>

/* --------------------------------- MACROS --------------------------------- */

# define ERROR			-1
# define UNSET			-1
# define SUFFIX			4
# define MIN_RGB_COLOR	0
# define MAX_RGB_COLOR	255
# define MIN_RGB_LENGTH	1
# define MAX_RGB_LENGTH	3

# define COMMA_CHAR	','
# define NL_CHAR	'\n'
# define SLASH_CHAR	'/'
# define SPACE_CHAR	' '
# define EMPTY_CHAR	'0'
# define WALL_CHAR	'1'
# define DOOR_CHAR	'2'

# define CUB_SUFFIX	".cub"

# define COLOR_FLOOR	"F"
# define COLOR_CEILING	"C"

# define TEXTURE_NORTH	"NO"
# define TEXTURE_SOUTH	"SO"
# define TEXTURE_WEST	"WE"
# define TEXTURE_EAST	"EA"

# define VALID_MAP_CHARS	"012NSWE "
# define PLAYER_MAP_CHARS	"NSWE"
# define VALID_SURR_EMPTY	"\0\1"

# define ERR_MALLOC_TMAP	"Failed to allocate memory [t_map *]"
# define ERR_MALLOC_TLIST	"Failed to allocate memory [t_list *]"
# define ERR_MALLOC_TTILES	"Failed to allocate memory [t_tile **]"
# define ERR_MALLOC_TTILE	"Failed to allocate memory [t_tile *]"
# define ERR_MALLOC_STRING	"Failed to allocate memory [char *]"
# define ERR_CUB_SUFFIX		"Invalid [.cub] file extension"
# define ERR_CUB_FORMAT		"Invalid [.cub] file format"
# define ERR_CUB_OPEN		"Cannot open [.cub] file"
# define ERR_TEXTURE_PATH	"Missing texture path"
# define ERR_COLOR			"Invalid color format"
# define ERR_INVALID_CHAR	"Map can only contain valid tiles [0/1/2/N/S/W/E/ ]"
# define ERR_PLAYERS		"Map can only contain one player tile [N/S/W/E]"
# define ERR_NO_PLAYER		"Map must contain a player tile [N/S/W/E]"
# define ERR_NOT_SURROUNDED	"Map must be surrounded by wall tiles [1]"
# define ERR_DOOR_NO_ENDS	"Doors [2] must terminate both ends of map rows"
# define ERR_DOOR_NO_ACCESS	"Doors [2] must be accessible"
# define ERR_DOORS			"Map can only contain two door tiles [2]"
# define ERR_NO_EMPTY		"Map must contain at least one empty tile [0]"

/* ---------------------------------- ENUMS --------------------------------- */

typedef enum e_parsing_state
{
	PARSING_MAP,
	PARSING_METADATA,
}	t_parsing_state;

typedef enum e_tile_id
{
	EMPTY	= 0,
	WALL	= 1,
	DOOR	= 2,
	VOID	= INT_MAX,
}	t_tile_id;

/* ------------------------------- STRUCTURES ------------------------------- */

typedef struct s_tile
{
	t_tile_id	id;
	t_list		*entities;
}	t_tile;

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
	t_vector2	door_coords[2];
}	t_map;

typedef struct s_parsing
{
	char			*line;
	t_list			*cub;
	t_map			*map;
	t_parsing_state	state;
}	t_parsing;

/* -------------------------------- FUNCTIONS ------------------------------- */

char	*ft_strndup(const char *string, size_t size);

t_bool	get_cub(t_parsing *parsing, char *path);
t_bool	get_grid(t_parsing *parsing);
t_bool	init_parsing(t_parsing *parsing);
t_bool	map_is_valid(t_map *map);
t_bool	parse_color(t_color *color, char *line);
t_bool	parse_map_line(t_parsing *parsing, size_t index);
t_bool	parse_texture(char **texture, char *path);
t_bool	parsing_error(char *error);

t_map	*parsing(char *path);

void	*free_map(t_map *map);
void	*free_parsing(t_parsing *parsing);

#endif
