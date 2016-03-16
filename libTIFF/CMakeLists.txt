# ----------------------------------------------------------------------------
#  CMake file for libtiff. See root CMakeLists.txt
#
# ----------------------------------------------------------------------------
project(libTIFF)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.3)

STRING(TOUPPER ${PROJECT_NAME} PROJECT_NAME_CAPITALIZED)

set(libtiffinclude_HEADERS
	tiff.h
	tiffio.h
	tiffvers.h
)

if (HAVE_CXX)
  list(APPEND libtiffinclude_HEADERS tiffio.hxx)
endif()

if (EXISTS "tiffconf.h" OR EXISTS "tif_config.h")
  message(FATAL_ERROR "tiffconf.h/tif_config.h already exist in the source directory.")
endif()
set(nodist_libtiffinclude_HEADERS
	#"${CMAKE_CURRENT_BINARY_DIR}/tiffconf.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/tiffconf.h"
)

set(noinst_HEADERS
	t4.h
	tif_dir.h
	tif_predict.h
	tiffiop.h
	uvcode.h
    #"${CMAKE_CURRENT_BINARY_DIR}/tif_config.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/tiffconf.h"
)

set(libtiff_SOURCES
	tif_aux.c
	tif_close.c
	tif_codec.c
	tif_color.c
	tif_compress.c
	tif_dir.c
	tif_dirinfo.c
	tif_dirread.c
	tif_dirwrite.c
	tif_dumpmode.c
	tif_error.c
	tif_extension.c
	tif_fax3.c
	tif_fax3sm.c
	tif_flush.c
	tif_getimage.c
	tif_jbig.c
	tif_jpeg.c
	tif_jpeg_12.c
	tif_luv.c
	tif_lzma.c
	tif_lzw.c
	tif_next.c
	tif_ojpeg.c
	tif_open.c
	tif_packbits.c
	tif_pixarlog.c
	tif_predict.c
	tif_print.c
	tif_read.c
	tif_strip.c
	tif_swab.c
	tif_thunder.c
	tif_tile.c
	tif_version.c
	tif_warning.c
	tif_write.c
	tif_zip.c
)

if (HAVE_CXX)
  list(APPEND libtiff_SOURCES tif_stream.cxx)
endif()

if (WIN32_IO)
  add_definitions(-DUSE_WIN32_FILEIO=1)
  list(APPEND libtiff_SOURCES tif_win32.c)
else()
  list(APPEND libtiff_SOURCES tif_unix.c)
endif()

if (MSVC)
  set(TIFF_DEF_FILE libtiff.def)
  set(TIFF_RESOURCES libtiff.rc)
endif()

# TODO Add the LD_VERSION_SCRIPT files

# Create the targets
set(HEADERS ${libtiffinclude_HEADERS} ${nodist_libtiffinclude_HEADERS})
set(SOURCES ${HEADERS} ${noinst_HEADERS} ${libtiff_SOURCES})
add_library(${PROJECT_NAME} STATIC ${SOURCES})

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES DEFINE_SYMBOL ${PROJECT_NAME_CAPITALIZED}_LIB)
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES FOLDER GeneralLibs)