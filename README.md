scriptdev0 ![Project status](http://getmangos.com/assets/img/repository-status-maintained.png)
==========
*scriptdev0* provides bindings to create custom creature reactions, events,
game objects, items, spells, and more for [mangos-zero][10] that can not be
created via the [mangos-zero game content database][12].

*scriptdev0* is based on the original [scriptdev2][21] bindings for [mangos][20]
and contains many custom scripts for content which was available in the classic
[World of Warcaft][50] experience for *World of Warcraft Client Patch 1.12* -
[_Drums of War_][51].

**scriptdev0** is released under the GPL v2.  The file (`LICENSE.mdown`) **must**
be a part of any redistributable packages made from this software.  No licenses
should be removed from this software if you are making redistributable copies.


Development
-----------
The **develop** branch is where the development of *scriptdev0* is done.  Any
of the commits submitted here may or may not become part of the next release.

It is recommended to use the **master** branch for stable systems, and only use
the **develop** branch if you intend to test commits and submit issues and/or
reports.


Compatibility
-------------
The *scriptdev0* bindings are compatible with [mangos-zero revision 1765][10]
and newer.


Installation
------------
If your already have a local copy of the [mangos-zero][10] source code (either
via the git clone mechanism or via github downloads), you can clone or download
the *scriptdev0* bindings into `mangos-zero/src/bindings/` as `scriptdev0`.

Edit `mangos-zero/src/bindings/CMakeLists.txt`, and add a line containing

    add_subdirectory(scriptdev0)

at the bottom of the file.  Afterwards proceed with the usual *mangos-zero*
build process via CMake to create a build with scriptdev0 included.


And if something goes wrong?
----------------------------
_If_ you feel like submitting an issue, please do so *only* if you are willing
to provide a detailed report, and are available to verify any solution to the
issue provided by the developers of this repository.


[1]: https://github.com/mangos-zero "mangos-zero"

[10]: https://github.com/mangos-zero/server "mangos zero"
[11]: https://github.com/mangos-zero/scriptdev0 "script bindings"
[12]: https://github.com/mangos-zero/database "content database"

[20]: https://github.com/mangos/mangos "mangos"
[21]: https://github.com/scriptdev2/scriptdev2 "script bindings (scriptdev2)"

[50]: http://eu.blizzard.com/en-gb/games/wow/ "World of Warcraft"
[51]: http://www.wowpedia.org/Patch_1.12.0 "WoW 1.12.0 - Drums of War"

[101]: http://github.com/ "github - social coding"

[110]: http://nvie.com/posts/a-successful-git-branching-model/ "git flow extension"
[111]: http://yakiloo.com/getting-started-git-flow/ "git flow workflow"
