# Introduction

This repository combines these projects:  
- **squirrel**
- **sqrat**
- **module-api**

into one **CMake** target that can be used as dependency while creating a **module** for [Gothic 2 Online](https://gothic-online.com.pl/).

# Usage

- add this repo to your own project as `git submodule` (e,g: place it in **dependencies** directory)
- use **CMake** functions `add_subdirectory` in conjuction with `target_link_libraries` to include it in your project.