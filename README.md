# Philipp's repository for CMake Modules

This is my small collection of CMake modules that might be useful.

How to Integrate
----------------

The modules can be directly placed in your Git project. I like to put them into
the `CMake/Modules` subdirectoy. To do so, type:
    cd <project-dir>
    git subtree add --squash --prefix=CMake/Modules https://github.com/philippharms/cmake-modules.git

To pull changes of the modules from this repository, type:
    cd <project-dir>
    git subtree pull --squash --prefix=CMake/Modules https://github.com/philippharms/cmake-modules.git

See also `man git-subtree` for infos about Git's `subtree` command.
