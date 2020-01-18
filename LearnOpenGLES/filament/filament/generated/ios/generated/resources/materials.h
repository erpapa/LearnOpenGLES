#ifndef MATERIALS_H_
#define MATERIALS_H_

#include <stdint.h>

extern "C" {
    extern const uint8_t MATERIALS_PACKAGE[];
    extern int MATERIALS_DEFAULTMATERIAL_OFFSET;
    extern int MATERIALS_DEFAULTMATERIAL_SIZE;
    extern int MATERIALS_BLIT_OFFSET;
    extern int MATERIALS_BLIT_SIZE;
    extern int MATERIALS_BLUR_OFFSET;
    extern int MATERIALS_BLUR_SIZE;
    extern int MATERIALS_MIPMAPDEPTH_OFFSET;
    extern int MATERIALS_MIPMAPDEPTH_SIZE;
    extern int MATERIALS_SKYBOX_OFFSET;
    extern int MATERIALS_SKYBOX_SIZE;
    extern int MATERIALS_SAO_OFFSET;
    extern int MATERIALS_SAO_SIZE;
    extern int MATERIALS_TONEMAPPING_OFFSET;
    extern int MATERIALS_TONEMAPPING_SIZE;
    extern int MATERIALS_FXAA_OFFSET;
    extern int MATERIALS_FXAA_SIZE;
}
#define MATERIALS_DEFAULTMATERIAL_DATA (MATERIALS_PACKAGE + MATERIALS_DEFAULTMATERIAL_OFFSET)
#define MATERIALS_BLIT_DATA (MATERIALS_PACKAGE + MATERIALS_BLIT_OFFSET)
#define MATERIALS_BLUR_DATA (MATERIALS_PACKAGE + MATERIALS_BLUR_OFFSET)
#define MATERIALS_MIPMAPDEPTH_DATA (MATERIALS_PACKAGE + MATERIALS_MIPMAPDEPTH_OFFSET)
#define MATERIALS_SKYBOX_DATA (MATERIALS_PACKAGE + MATERIALS_SKYBOX_OFFSET)
#define MATERIALS_SAO_DATA (MATERIALS_PACKAGE + MATERIALS_SAO_OFFSET)
#define MATERIALS_TONEMAPPING_DATA (MATERIALS_PACKAGE + MATERIALS_TONEMAPPING_OFFSET)
#define MATERIALS_FXAA_DATA (MATERIALS_PACKAGE + MATERIALS_FXAA_OFFSET)

#endif