/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfarhi <lfarhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:15:55 by lfarhi            #+#    #+#             */
/*   Updated: 2024/12/17 14:58:33 by lfarhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H
# include <cube3d.h>

void player_update(t_entity *entity);
void player_minimap(t_entity *entity);

void orbe_update(t_entity *entity);
void orbe_minimap(t_entity *entity);

void ghost_update(t_entity *entity);
void ghost_minimap(t_entity *entity);

#endif