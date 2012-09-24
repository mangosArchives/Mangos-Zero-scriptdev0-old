Script Layout
=============
A quick explanation of the layout I hope everyone will follow for scriptdev2.


Sub Folders
-----------

* **Area**: contains scripts used solely by area triggers,
* **Boss**: boss scripts for bosses that are not zone specific,
* **Mob**: generic scripts for creatures that are not zone specific,
* **GO**: contains scripts used solely by game objects (GOs) that do not have
  a specific zone,
* **Guard**: scripts for guard NPCs,
* **Honor**: honor npcs (currently a blank script as these npcs do nothing,
  special)
* **Item**: item scripts,
* **NPC**: scripts for individual NPCs who do not have a specific zone,
* **Servers**: generic NPC servers script for things such as flightmasters
  and guildmasters,
* **Zone**: ALL zone specific scripts should be written within these folders.
  This includes creature scripts, boss scripts, go scripts, area scripts,
  and npc scripts.


Naming Conventions
------------------
Please keep file names to `type_objectname.cpp` where type is replaced by the
type of object and objectname is replaced by the name of the object, creature,
item, or area that this script will be used by.

`AddSC` functions should follow `void AddSC_creaturename(void);` format.

*Do not append AI or anything else.*
