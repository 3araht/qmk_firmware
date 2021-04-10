#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 5

#define CT_MACROPAD_MACROPAD
#ifdef CT_MACROPAD_MACROPAD
// Change the ID for VIA support.
#    undef PRODUCT_ID
#    define PRODUCT_ID   0xF4B3
#    undef PRODUCT
#    define PRODUCT ct_macropad12
#endif
