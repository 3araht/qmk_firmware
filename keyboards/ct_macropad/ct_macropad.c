/* Copyright 2021 3araht
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ct_macropad.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {
    {
        { 6, 0, 2, 4, 3, 1, 5, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
    }, {
        {   0, 64 }, {  75, 64 }, { 150,  64 }, { 224, 64 }, { 187,  32 }, {  113,  32 }, {   0,    0 }
    }, {
          4, 4, 4, 4, 4, 4, 4,
    }
};
#endif
