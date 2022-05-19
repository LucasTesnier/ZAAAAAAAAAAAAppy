# Zaaaaaaaaaaaappy

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
    cmake --build ./build
    cd ./build
    ctest --output-on-failure
```

### Coding Style

Zappy is developed with C. EPITECH impose the Epitech Coding Style. [Check it right here.](https://intra.epitech.eu/file/Public/technical-documentations/epitech_c_coding_style.pdf)

## Development Policy

You will find below all the best practices to adopt by contributing to the project.

### Commit Policy

Your commits should follow the following format:

> \[Symbol\] Verb Description #IssueNumber

| Symbol | Meaning  |
| :-----: | :-: |
| + | Addition |
| - | Deletion |
| * | Modification |

For example :

```bash
    git commit -m "[+] Implement readme.md commit policy table #12"
```

Any commit that does not meet this standard will not be deleted. Just be careful.

It is recommended to commit on a regular basis.

### Branch Policy

Your branch should follow the following format:

> Issue/Which/I/Refer/To/IssueNumber

For example :

```bash
    git checkout -b Architecture/Setup/Readme/12
```

Any branch that does not respect this format will be refused all of its associated PRs.

Please make one branch per issue.

Try to push as regularly as possible so everyone can see where you are at.

### Pull Request Policy

### HotFixe Policy

### Issue Policy

### Testing Policy

## Authors

* **Lucas Tesnier, Guillaume Terriere, Thomas Prudhomme, Julien Hourcadette, Nathan Rousseau, Constant Vigneron**