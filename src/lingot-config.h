//-*- C++ -*-
/*
 * lingot, a musical instrument tuner.
 *
 * Copyright (C) 2004-2007  Ibán Cereijo Graña, Jairo Chapela Martínez.
 *
 * This file is part of lingot.
 *
 * lingot is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * lingot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with lingot; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __LINGOT_CONFIG_H__
#define __LINGOT_CONFIG_H__

#include "lingot-defs.h"

/*
 Configuration class. Determines the tuner's behaviour.
 Some parameters are internal only.
 */

typedef struct _LingotConfig LingotConfig;

struct _LingotConfig
  {
    void* param[15]; // parameter pointer array.

    char audio_dev[80]; // default "/dev/dsp"
    unsigned int sample_rate; // soundcard sample rate.
    unsigned int oversampling; // oversampling factor.

    // frequency of the root A note (internal parameter).
    FLT root_frequency;

    FLT root_frequency_error; // deviation of the above root frequency.

    FLT min_frequency; // minimum valid frequency.

    unsigned int fft_size; // number of samples of the FFT.

    FLT calculation_rate;
    FLT visualization_rate;

    FLT temporal_window; // duration in seconds of the temporal window.

    // samples stored in the temporal window (internal parameter).
    unsigned int temporal_buffer_size;

    // samples read from soundcard. (internal parameter)
    unsigned int read_buffer_size;

    FLT noise_threshold_db; // dB
    FLT noise_threshold_un; // natural units (internal parameter)

    // frequency finding algorithm configuration
    //-------------------------------------------

    unsigned int peak_number; // number of maximum peaks considered.

    // number of adyacent samples needed to consider a peak.
    unsigned int peak_order;

    /* maximum amplitude relation between principal and secondary peaks.
     The max peak doesn't has to be the fundamental frequency carrier if it
     has an amplitude relation with the fundamental considered peak lower than
     this parameter. */
    FLT peak_rejection_relation_db; // dBs
    FLT peak_rejection_relation_un; // natural units (internal)

    // DFT approximation
    unsigned int dft_number; // number of DFTs.
    unsigned int dft_size; // samples of each DFT.

    // max iterations for Newton-Raphson algorithm.
    unsigned int max_nr_iter;

    //----------------------------------------------------------------------------

    // gauge rest value. (gauge contemplates [-0.5, 0.5])
    FLT vr;

    //----------------------------------------------------------------------------
  };

LingotConfig* lingot_config_new();

// back to default configuration.
void lingot_config_reset(LingotConfig* config);

// derivate internal parameters from external ones.
int lingot_config_update_internal_params(LingotConfig* config);

void lingot_config_save(LingotConfig* config, char* file);
void lingot_config_load(LingotConfig* config, char* file);

#endif // __LINGOT_CONFIG_H__