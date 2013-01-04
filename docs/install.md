How to install ScriptDev2
=========================

* download MaNGOS (using git clone)
* do the source stuff:
  - MS Windows:
    - Create a new folder under "src\bindings\" within the MaNGOS source called "ScriptDev2"
    - Checkout the ScriptDev2 trunk from "https://scriptdev2.svn.sourceforge.net/svnroot/scriptdev2"
    - Apply the Git patch to Mangos - "git am src/bindings/ScriptDev2/patches/MaNGOS-XXXX-ScriptDev2.patch" ('XXXX' is revision number for Mangos). (Note this is not required for compile, but needed to avoid deletion of untracked folders/files in GIT-directory when using certain GIT commands (example: git clean -f -d))
    - Compile MaNGOS
    - Compile ScriptDev2 using the ScriptVC80 or ScriptVC90 Solution within the ScriptDev2 folder (this will overwrite the Mangoscript dll in the output directory)
  - GNU/Linux:
    - Checkout the ScriptDev2 to "src/bindings/ScriptDev2" - "svn co https://scriptdev2.svn.sourceforge.net/svnroot/scriptdev2 src/bindings/ScriptDev2"
  - SVN:
    - Apply MaNGOS-XXXX-ScriptDev2.patch to Mangos, where XXXX is the highest version to that of your MaNGOS revision.
  - GIT:
    - Apply the Git patch to Mangos - "git am src/bindings/ScriptDev2/patches/MaNGOS-XXXX-ScriptDev2.patch"
  - Compile MaNGOS (ScriptDev2 will automatically be built when compiling Mangos from here on)
* Create the default ScriptDev2 database using `sql\scriptdev2_create_database.sql`, then execute
  `sql\scriptdev2_create_structure.sql` on that database.
* Execute the following on your ScriptDev2 database: `sql\scriptdev2_script_full.sql`
* Execute the following file on your MaNGOS database: `sql\mangos_scriptname_full.sql`
* Place the included `scriptdev2.conf` file within the directory containing your `mangosd.conf` and `realmd.conf` files. You may need to change this file to match the database you created and any custom settings you wish to use. Note this file will be different created for Unix based systems.
* Run mangosd from your output directory


To update ScriptDev2
=====================

MS Windows
----------
- All you have to do is open src\bindings\ and right click on the ScriptDev2 folder and click "Update" and then follow steps 4, 6, and 7 again. You must still compile MaNGOS before ScriptDev2 when on the Windows platform.

GNU/Linux
---------
- Go to the src/bindings/ScriptDev2 directory - "cd src/bindings/ScriptDev2"
- Update ScriptDev2 - "svn up"


To update your Database
-----------------------
* apply only the changes that were made during that revision by looking in the sql\update folder or (files named rXXX_scriptdev2.sql should be executed on the scriptdev2 db while rXXX_mangos.sql should be executed on your mangos db)
* reapply "mangos_scriptname_full.sql" to your MaNGOS database.

You can view the ScriptDev2 Change Log at:
http://scriptdev2.svn.sourceforge.net/viewvc/scriptdev2/?view=log