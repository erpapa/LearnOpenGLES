    .global _MATERIALS_DEFAULTMATERIAL_OFFSET;
    .global _MATERIALS_DEFAULTMATERIAL_SIZE;
    .global _MATERIALS_BLIT_OFFSET;
    .global _MATERIALS_BLIT_SIZE;
    .global _MATERIALS_BLUR_OFFSET;
    .global _MATERIALS_BLUR_SIZE;
    .global _MATERIALS_MIPMAPDEPTH_OFFSET;
    .global _MATERIALS_MIPMAPDEPTH_SIZE;
    .global _MATERIALS_SKYBOX_OFFSET;
    .global _MATERIALS_SKYBOX_SIZE;
    .global _MATERIALS_SAO_OFFSET;
    .global _MATERIALS_SAO_SIZE;
    .global _MATERIALS_TONEMAPPING_OFFSET;
    .global _MATERIALS_TONEMAPPING_SIZE;
    .global _MATERIALS_FXAA_OFFSET;
    .global _MATERIALS_FXAA_SIZE;

    .global _MATERIALS_PACKAGE
    .section __TEXT,__const
_MATERIALS_PACKAGE:
    .incbin "materials.bin"
_MATERIALS_DEFAULTMATERIAL_OFFSET:
    .int 0
_MATERIALS_DEFAULTMATERIAL_SIZE:
    .int 51392
_MATERIALS_BLIT_OFFSET:
    .int 51392
_MATERIALS_BLIT_SIZE:
    .int 20724
_MATERIALS_BLUR_OFFSET:
    .int 72116
_MATERIALS_BLUR_SIZE:
    .int 27396
_MATERIALS_MIPMAPDEPTH_OFFSET:
    .int 99512
_MATERIALS_MIPMAPDEPTH_SIZE:
    .int 20857
_MATERIALS_SKYBOX_OFFSET:
    .int 120369
_MATERIALS_SKYBOX_SIZE:
    .int 43090
_MATERIALS_SAO_OFFSET:
    .int 163459
_MATERIALS_SAO_SIZE:
    .int 37784
_MATERIALS_TONEMAPPING_OFFSET:
    .int 201243
_MATERIALS_TONEMAPPING_SIZE:
    .int 35870
_MATERIALS_FXAA_OFFSET:
    .int 237113
_MATERIALS_FXAA_SIZE:
    .int 49781

