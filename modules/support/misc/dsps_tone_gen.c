// Copyright 2018-2019 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "dsps_tone_gen.h"
#include <math.h>

esp_err_t dsps_tone_gen_f32(float *output, int len, float A, float f, float ph)
{
    if (f >= 1) {
        return ESP_ERR_DSP_INVALID_PARAM;
    }
    if (f <= -1) {
        return ESP_ERR_DSP_INVALID_PARAM;
    }
    float phase = ph / 180 * M_PI;
    float freq  = 2 * M_PI * f;
    for (int i = 0 ; i < len ; i++) {
        output[i] = A * sin(phase);
        phase += freq;
        if (phase > 2 * M_PI) {
            phase -= 2 * M_PI;
        }
        if (phase < -2 * M_PI) {
            phase += 2 * M_PI;
        }
    }
    return ESP_OK;
}
