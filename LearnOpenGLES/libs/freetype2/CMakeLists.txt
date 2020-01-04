add_definitions(-DFT2_BUILD_LIBRARY)

SET(DIR_FREETYPE_SRC
  src/base/ftbase.c
  src/base/ftbbox.c
  src/base/ftbdf.c
  src/base/ftbitmap.c
  src/base/ftcid.c
  src/base/ftfstype.c
  src/base/ftgasp.c
  src/base/ftglyph.c
  src/base/ftgxval.c
  src/base/ftinit.c
  src/base/ftmm.c
  src/base/ftotval.c
  src/base/ftpatent.c
  src/base/ftpfr.c
  src/base/ftstroke.c
  src/base/ftsynth.c
  src/base/ftsystem.c
  src/sfnt/sfnt.c
  src/smooth/smooth.c
  src/truetype/truetype.c
)

add_library(freetype2 ${DIR_FREETYPE_SRC})