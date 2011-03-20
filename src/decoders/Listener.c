/* FreeEMS - the open source engine management system
 *
 * Copyright 2011 Fred Cooke
 *
 * This file is part of the FreeEMS project.
 *
 * FreeEMS software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeEMS software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * We ask that if you make any changes to this file you email them upstream to
 * us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
 *
 * Thank you for choosing FreeEMS to run your engine!
 */


/**	@file Listener.c
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Prevents main loop from running calculations and finishes quickly
 *
 * The purpose of this "decoder" is purely to listen to the inputs and trick the
 * rest of the code into not running any calculations and just sending as many
 * logs as it can.
 *
 * This is useful to get a smooth logic analyser or other high speed log free
 * of gaps in the stream.
 *
 * @author Fred Cooke
 */


#define DECODER_IMPLEMENTATION_C

#include "../inc/freeEMS.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"


const unsigned char decoderName[] = "Listener";
const unsigned char numberOfEvents = 1;
const unsigned short eventAngles[] = {0}; // no events really...
const unsigned short totalEventAngleRange = 720;
const unsigned short decoderMaxCodeTime = 100; // To be optimised (shortened)!


/** Primary RPM ISR
 *
 * Keep disabling calcs as often as we can.
 *
 * @author Fred Cooke
 */
void PrimaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x01;
	/* Reset the clock for reading timeout */
	Clocks.timeoutADCreadingClock = 0;
}


/** Secondary RPM ISR
 *
 * Keep disabling calcs as often as we can.
 *
 * @author Fred Cooke
 */
void SecondaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x02;
	/* Reset the clock for reading timeout */
	Clocks.timeoutADCreadingClock = 0;
}
