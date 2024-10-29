/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:03:17 by bryaloo           #+#    #+#             */
/*   Updated: 2024/10/29 23:03:23 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Load the map from a .ber file
char **load_map(char *filename) {
    int fd;
    char **map;
    int i;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (print_error("Error\nCould not open map file.\n"));
    map = malloc(sizeof(char *) * MAX_MAP_HEIGHT);
    if (!map)
        return (print_error("Error\nMemory allocation failed.\n"));
    i = 0;
    while (i < MAX_MAP_HEIGHT && (map[i] = get_next_line(fd))) {
        i++;
    }
    close(fd);
    return (validate_map(map) ? map : NULL);
}

// Validate map structure, boundaries, and required elements
int validate_map(char **map) {
    int width;
    int height;

    if (!map || !check_rectangular(map) || !check_boundary_walls(map))
        return (0);
    width = ft_strlen(map[0]);
    height = map_height(map);
    if (!has_required_elements(map, width, height))
        return (0);
    return (check_path(map, width, height));
}

// Check if the map is rectangular
int check_rectangular(char **map) {
    int i;
    int width;

    i = 0;
    width = ft_strlen(map[0]);
    while (map[i]) {
        if (ft_strlen(map[i]) != width)
            return (0);
        i++;
    }
    return (1);
}

// Ensure the map is surrounded by walls (boundary check)
int check_boundary_walls(char **map) {
    int i;
    int width;
    int height;

    width = ft_strlen(map[0]);
    height = map_height(map);
    i = 0;
    while (i < width) {
        if (map[0][i] != '1' || map[height - 1][i] != '1')
            return (0);
        i++;
    }
    i = 1;
    while (i < height - 1) {
        if (map[i][0] != '1' || map[i][width - 1] != '1')
            return (0);
        i++;
    }
    return (1);
}

