/*
** EPITECH PROJECT, 2022
** Project
** File description:
** argument_handling
*/

/// \file src/zappy_server_src/core/include/argument_handling.h

#ifndef ARGUMENT_HANDLING_H_
    #define ARGUMENT_HANDLING_H_

///
/// \brief Hold the argument identification process
///
/// \param ac Number of argument
/// \param av List of arguments
/// \return argument_t* Newly created argument struct
///
argument_t *argument_handling(int ac, char **av);

#endif /* !ARGUMENT_HANDLING_H_ */
