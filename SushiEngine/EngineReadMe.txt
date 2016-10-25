========================================================================
    STATIC LIBRARY : SushiEngine Project Overview
=======================================================================

SushiEngine.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

SushiEngine.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

/////////////////////////////////////////////////////////////////////////////

DEPENDENCIES

Additional Include Directories:
$(SolutionDir)Dependencies\glm;$(SolutionDir)Dependencies\gli;$(SolutionDir)Dependencies\assimp;$(SolutionDir)Dependencies;

Additional Library Directories:
$(SolutionDir)Dependencies\libs;

Additional Dependencies:
vulkan\vulkan-1.lib;assimp\assimp.lib;glfw\glfw3.lib;

