/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:42:40 by jibanez-          #+#    #+#             */
/*   Updated: 2023/03/13 08:53:16 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H
# include "cube3d.h"
# if defined(__linux__)
#  define ESC			65307	// ESQ
#  define MOVE_UP		119		// W
#  define MOVE_DOWN		115		// S
#  define MOVE_LEFT		97		// A
#  define MOVE_RIGHT	100		// D
#  define LOOK_UP		65362	// ↑
#  define LOOK_DOWN		65364	// ↓
#  define LOOK_LEFT		65361	// ←
#  define LOOK_RIGHT	65363	// →
#  define TOGGLE_MOUSE	113		// Q
#  define M_KEY			109		// M -> need to check the Key for Linux
# elif defined(__APPLE__)
#  define ESC			53		// ESQ
#  define MOVE_UP		13		// W
#  define MOVE_DOWN		1		// S
#  define MOVE_LEFT		0		// A
#  define MOVE_RIGHT	2		// D
#  define LOOK_UP		126		// ↑
#  define LOOK_DOWN		125		// ↓
#  define LOOK_LEFT		123		// ←
#  define LOOK_RIGHT	124		// →
#  define TOGGLE_MOUSE	12		// Q
#  define M_KEY			46		// M
# endif
#endif
