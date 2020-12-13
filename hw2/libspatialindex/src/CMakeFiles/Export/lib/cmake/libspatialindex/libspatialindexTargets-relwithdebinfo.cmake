#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "spatialindex" for configuration "RelWithDebInfo"
set_property(TARGET spatialindex APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(spatialindex PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libspatialindex.so.6.1.1"
  IMPORTED_SONAME_RELWITHDEBINFO "libspatialindex.so.6"
  )

list(APPEND _IMPORT_CHECK_TARGETS spatialindex )
list(APPEND _IMPORT_CHECK_FILES_FOR_spatialindex "${_IMPORT_PREFIX}/lib/libspatialindex.so.6.1.1" )

# Import target "spatialindex_c" for configuration "RelWithDebInfo"
set_property(TARGET spatialindex_c APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(spatialindex_c PROPERTIES
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libspatialindex_c.so.6.1.1"
  IMPORTED_SONAME_RELWITHDEBINFO "libspatialindex_c.so.6"
  )

list(APPEND _IMPORT_CHECK_TARGETS spatialindex_c )
list(APPEND _IMPORT_CHECK_FILES_FOR_spatialindex_c "${_IMPORT_PREFIX}/lib/libspatialindex_c.so.6.1.1" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
