***
<p align=center>
    <img src=docs/assets/logo/logo_303_289.png />
</p>

[![Build](https://github.com/LucasTesnier/ZAAAAAAAAAAAAppy/actions/workflows/cmake.yml/badge.svg)](https://github.com/LucasTesnier/ZAAAAAAAAAAAAppy/actions/workflows/cmake.yml)
***

The Zappy project consists of the realization of a simulation of a "Spore Like".

Composed of three parts, namely the server, developed in C, the GUI, developed in C++/SFML and the ClientIA, developed in C/Python.

## Before continuing...

This project is an EPITECH Project. If you are an EPITECH student, move out the way! Nothing to see here... The groups don't want to be involved to your -42.

If you're not, no worries! You're welcome here!

### Prerequisites

To use this project, you'll need Cmake 3.17.0 Compiler, SFML-devel library, python 3.0 and C11.

### Building program

```bash
    cmake -B ./build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
    cmake --build ./build
```

### Testing program
```bash
    rm -rf ./build 
    cmake -B ./build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DTESTING=ON
    cmake --build ./build
    cd ./build
    ctest --oupu-on-failure
```

### Coding Style

Zappy is developed with C. EPITECH impose the Epitech Coding Style. [Check it right here.](https://intra.epitech.eu/file/Public/technical-documentations/epitech_c_coding_style.pdf)

## Thank for reading

Feel free to read the CONTRIBUTING.md

Do not hesitate to contact me for any questions or remarks.

* Mail -> lucas.tesnier@epitech.eu

* Discord -> Waroth#4623

## Authors

* **Lucas Tesnier, Guillaume Terriere, Thomas Prudhomme, Julien Hourcadette, Nathan Rousseau, Constant Vigneron**
