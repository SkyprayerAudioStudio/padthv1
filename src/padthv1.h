// padthv1.h
//
/****************************************************************************
   Copyright (C) 2012-2019, rncbc aka Rui Nuno Capela. All rights reserved.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*****************************************************************************/

#ifndef __padthv1_h
#define __padthv1_h

#include "config.h"

#include <stdint.h>

// forward declarations
class padthv1_impl;
class padthv1_port;
class padthv1_sample;
class padthv1_controls;
class padthv1_programs;


//-------------------------------------------------------------------------
// padthv1 - decl.
//

class padthv1
{
public:

	padthv1(uint16_t nchannels = 2, float srate = 44100.0f);

	virtual ~padthv1();

	void setChannels(uint16_t nchannels);
	uint16_t channels() const;

	void setSampleRate(float srate);
	float sampleRate() const;

	padthv1_sample *sample(int sid) const;

	void setBufferSize(uint32_t nsize);
	uint32_t bufferSize() const;

	void setTempo(float bpm);
	float tempo() const;

	enum ParamIndex	 {

		GEN1_SAMPLE1 = 0,
		GEN1_WIDTH1,
		GEN1_SCALE1,
		GEN1_NH1,
		GEN1_APOD1,
		GEN1_DETUNE1,
		GEN1_GLIDE1,
		GEN1_SAMPLE2,
		GEN1_WIDTH2,
		GEN1_SCALE2,
		GEN1_NH2,
		GEN1_APOD2,
		GEN1_DETUNE2,
		GEN1_GLIDE2,
		GEN1_BALANCE,
		GEN1_PHASE,
		GEN1_RINGMOD,
		GEN1_OCTAVE,
		GEN1_TUNING,
		GEN1_ENVTIME,
		DCF1_CUTOFF,
		DCF1_RESO,
		DCF1_TYPE,
		DCF1_SLOPE,
		DCF1_ENVELOPE,
		DCF1_ATTACK,
		DCF1_DECAY,
		DCF1_SUSTAIN,
		DCF1_RELEASE,
		LFO1_SHAPE,
		LFO1_WIDTH,
		LFO1_BPM,
		LFO1_RATE,
		LFO1_SYNC,
		LFO1_SWEEP,
		LFO1_PITCH,
		LFO1_BALANCE,
		LFO1_RINGMOD,
		LFO1_CUTOFF,
		LFO1_RESO,
		LFO1_PANNING,
		LFO1_VOLUME,
		LFO1_ATTACK,
		LFO1_DECAY,
		LFO1_SUSTAIN,
		LFO1_RELEASE,
		DCA1_VOLUME,
		DCA1_ATTACK,
		DCA1_DECAY,
		DCA1_SUSTAIN,
		DCA1_RELEASE,
		OUT1_WIDTH,
		OUT1_PANNING,
		OUT1_FXSEND,
		OUT1_VOLUME,

		DEF1_PITCHBEND,
		DEF1_MODWHEEL,
		DEF1_PRESSURE,
		DEF1_VELOCITY,
		DEF1_CHANNEL,
		DEF1_MONO,

		CHO1_WET,
		CHO1_DELAY,
		CHO1_FEEDB,
		CHO1_RATE,
		CHO1_MOD,
		FLA1_WET,
		FLA1_DELAY,
		FLA1_FEEDB,
		FLA1_DAFT,
		PHA1_WET,
		PHA1_RATE,
		PHA1_FEEDB,
		PHA1_DEPTH,
		PHA1_DAFT,
		DEL1_WET,
		DEL1_DELAY,
		DEL1_FEEDB,
		DEL1_BPM,
		REV1_WET,
		REV1_ROOM,
		REV1_DAMP,
		REV1_FEEDB,
		REV1_WIDTH,
		DYN1_COMPRESS,
		DYN1_LIMITER,

		NUM_PARAMS
	};

	void setParamPort(ParamIndex index, float *pfParam);
	padthv1_port *paramPort(ParamIndex index) const;

	void setParamValue(ParamIndex index, float fValue);
	float paramValue(ParamIndex index) const;

	bool running(bool on);

	void reset();

	padthv1_controls *controls() const;
	padthv1_programs *programs() const;

	void process_midi(uint8_t *data, uint32_t size);
	void process(float **ins, float **outs, uint32_t nframes);

	virtual void updatePreset(bool bDirty) = 0;

	void midiInEnabled(bool on);
	uint32_t midiInCount();

	void directNoteOn(int note, int vel);

	void updateTuning();

private:

	padthv1_impl *m_pImpl;
};


#endif// __padthv1_h

// end of padthv1.h
