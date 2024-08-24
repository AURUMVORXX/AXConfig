# Sqrat - Squirrel Binding Utility

What is in this distribution?

- **sq**  
    stand alone interpreter that includes sqimport

- **sqimport**  
    import utility for creating/importing script/binary modules

- **sqrattest**  
    unit tests written for sqrat

- **sqratthread**  
    shared library that provides alternative squirrel thread implementation with new features

Some projects require [squirrel](https://gitlab.com/GothicMultiplayerTeam/dependencies/squirrel) to be build.

## Introduction

This repository is a copy of original [Sqrat](https://sourceforge.net/projects/scrat/) that adds changes needed for the [**Gothic 2 Online**](https://gothic-online.com.pl/) modification.

I've created this project because official repository isn't active lately, it's hard to make a contribution that will be merged at all.  
**G2O** also uses slightly modified version of sqrat, so this project includes all of the neccessary changes.

**NOTE!** This project requires minimum `cpp17` standard, this is becuause it utilizes folding expressions for handling functions with variadic number of arguments.

# Usage

- add this repo to your own project as `git submodule` (e,g: place it in **dependencies** directory)
- use **CMake** functions `add_subdirectory` in conjuction with `target_link_libraries` to include it in your project.

# Documentation

https://gothicmultiplayerteam.gitlab.io/dependencies/sqrat/