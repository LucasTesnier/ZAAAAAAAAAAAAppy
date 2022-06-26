/*
** EPITECH PROJECT, 2022
** ZAAAAAAAAAAAAppy
** File description:
** wrapper_tests
*/

#include <criterion/criterion.h>
#include <sys/queue.h>
#include <stdio.h>
#include "entity/entity.h"
#include "map.h"

Test(wrapper_tests, create_entity_wrapper_test)
{
    entity_wrapper_t *wrapper = create_entity_wrapper();

    cr_assert_eq(TAILQ_EMPTY(&wrapper->players), true);
    cr_assert_eq(TAILQ_EMPTY(&wrapper->eggs), true);
    cr_assert_eq(TAILQ_EMPTY(&wrapper->tiles), true);
    delete_entity_wrapper(wrapper);
}

Test(wrapper_tests, entity_wrapper_create_map)
{
    map_t *map = create_new_map(10, 10);
    entity_wrapper_t *wrapper = create_entity_wrapper();

    cr_assert_eq(map->width, 10);
    cr_assert_eq(map->height, 10);
    for (int i = 0; i < map->width * map->height; i++) {
        cr_assert_eq(map->tiles[i]->type, ENTITY_TILE_TYPE);
        printf("{x: %d; y:", map->tiles[i]->position.x);
        printf("%d}\n", map->tiles[i]->position.y);
        entity_wrapper_create_tile(wrapper, map->tiles[i]->position);
    }
    delete_entity_wrapper(wrapper);
}
