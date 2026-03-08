// =============================================
//  Gab's Hackpad — gabs_hackpad.h
// =============================================
#pragma once
#include "quantum.h"

// Layout macro — maps flat array to matrix
// Row 0: SW1  SW2  SW3  SW4  SW5  SW6
#define LAYOUT( \
    k00, k01, k02, \
    k03, k04, k05  \
) { \
    { k00, k01, k02, k03, k04, k05 } \
}
