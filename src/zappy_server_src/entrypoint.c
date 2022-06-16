/*
** EPITECH PROJECT, 2022
** Project
** File description:
** entrypoint
*/

#include "entrypoint.h"
#include <string.h>
#include <stdio.h>

static const char* usage = "USAGE: %s -p port -x width -y height \
-n name1 name2 ... -c clientsNb -f freq\n \
\t-p port\t\tThe port number\n \
\t-x width\t\tThe width of the world\n \
\t-y height\tThe height of the world\n \
\t-n name1 name2 ...\tThe name of the teams\n \
\t-c clientsNb\tThe number of clients per team\n \
\t-f freq\t\tThe reciprocal of time unit for execution of actions\n";

int main(int ac, char **av)
{
    if (ac == 1
    || (ac == 2 && (strcmp(av[1], "-h") && strcmp(av[1], "--help")) == 0)) {
        dprintf(2, usage, av[0]);
        return 0;
    }
    server_run(ac, av);
    return 0;
}