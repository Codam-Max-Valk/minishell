/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/27 17:58:41 by cbijman       #+#    #+#                 */
/*   Updated: 2023/06/27 18:10:14 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

// Regular colors
# define BLACK   "\x1B[0;30m"
# define RED     "\x1B[0;31m"
# define GREEN   "\x1B[0;32m"
# define YELLOW  "\x1B[0;33m"
# define BLUE    "\x1B[0;34m"
# define MAGENTA "\x1B[0;35m"
# define CYAN    "\x1B[0;36m"
# define WHITE   "\x1B[0;37m"

// Bold colors
# define BOLD_BLACK   "\x1B[1;30m"
# define BOLD_RED     "\x1B[1;31m"
# define BOLD_GREEN   "\x1B[1;32m"
# define BOLD_YELLOW  "\x1B[1;33m"
# define BOLD_BLUE    "\x1B[1;34m"
# define BOLD_MAGENTA "\x1B[1;35m"
# define BOLD_CYAN    "\x1B[1;36m"
# define BOLD_WHITE   "\x1B[1;37m"

//Italic colors
# define ITALIC_BLACK   "\x1B[3;30m"
# define ITALIC_RED     "\x1B[3;31m"
# define ITALIC_GREEN   "\x1B[3;32m"
# define ITALIC_YELLOW  "\x1B[3;33m"
# define ITALIC_BLUE    "\x1B[3;34m"
# define ITALIC_MAGENTA "\x1B[3;35m"
# define ITALIC_CYAN    "\x1B[3;36m"
# define ITALIC_WHITE   "\x1B[3;37m"

// Reset color
# define RESET "\x1B[0m"

#endif