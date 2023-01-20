/*
 * @NICTA_MODIFICATIONS_START@
 * 
 * This source code is licensed under Apple Public Source License Version 2.0.
 * Portions copyright Apple Computer, Inc.
 * Portions copyright National ICT Australia.
 *
 * All rights reserved.
 *
 * This code was modified 2006-06-20.
 *
 * @NICTA_MODIFICATIONS_END@
 */
/*
 * Copyright (c) 2001-2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 2.0 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 *
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */
#include "PhantomAudioEngine.h"

#include <IOKit/audio/IOAudioControl.h>
#include <IOKit/audio/IOAudioLevelControl.h>
#include <IOKit/audio/IOAudioToggleControl.h>
#include <IOKit/audio/IOAudioDefines.h>

#include <IOKit/IOLib.h>
#include <IOKit/IOWorkLoop.h>
#include <IOKit/IOTimerEventSource.h>

#define INITIAL_SAMPLE_RATE	44100
#define BLOCK_SIZE			512		// Sample frames
#define NUM_BLOCKS			32
#define NUM_STREAMS			1

#define super IOAudioEngine

/*
 * PhantomAudioEngine
 *
 *  This class shows a simple subclass of IOAudioEngine that is fully configurable through the 
 *  registry and the IOKit personality entry.  Typically it will be the hardware that dictates
 *  how the audio engine should be configured, but as an example without any backing hardware
 *  it is possible to reconfigure the driver in many different ways.
 *
 *  This class is responsible for:
 *		- Creating IOAudioStreams and the allowable formats
 *		- Creating IOAudioControls
 *			- one mute and volume for each input/output channel
 *			- one passthru for each channel
 *			- master input/output mute and volume
 *		  NOTE: In this case, the controls' handler functions are in the PhantomAudioDevice as that
 *              is the most common place to perform the control value changes.  However, due to 
 *              the way that this driver gets its configuration from the registry, it is more 
 *              convenient to create the controls here rather than in the device.
 *		- Starting and stopping the audio engine when requested (performAudioEngineStart/Stop())
 *		- Taking timestamps when the buffer(s) wrap around
 *		- Reporting the current sample frame when requested (getCurrentSampleFrame())
 *		- Handling format and sample rate changes (performFormatChange())
 */
            

OSDefineMetaClassAndStructors(PhantomAudioEngine, IOAudioEngine)

/*
 * init()
 */
 
bool PhantomAudioEngine::init(OSDictionary *properties)
{
    bool result = false;
    OSNumber *number;
    
    IOLog("PhantomAudioEngine[%p]::init()\n", this);

    if (!super::init(properties)) {
        goto Done;
    }
    
    // Do class-specific initialization here
    // If no non-hardware initialization is needed, this function can be removed
    
    number = OSDynamicCast(OSNumber, getProperty(NUM_BLOCKS_KEY));
    if (number) {
        numBlocks = number->unsigned32BitValue();
    } else {
        numBlocks = NUM_BLOCKS;
    }
    
    number = OSDynamicCast(OSNumber, getProperty(BLOCK_SIZE_KEY));
    if (number) {
        blockSize = number->unsigned32BitValue();
    } else {
        blockSize = BLOCK_SIZE;
    }
    
    duringHardwareInit = FALSE;
    
    result = true;
    
Done:

    return result;
}

/*
 * initHardware()
 */

bool PhantomAudioEngine::initHardware(IOService *provider)
{
    bool result = false;
    IOAudioSampleRate initialSampleRate;
    IOWorkLoop *wl;
    
    IOLog("PhantomAudioEngine[%p]::initHardware(%p)\n", this, provider);
    
    duringHardwareInit = TRUE;
    
    if (!super::initHardware(provider)) {
        goto Done;
    }
    
    initialSampleRate.whole = 0;
    initialSampleRate.fraction = 0;

    if (!createAudioStreams(&initialSampleRate)) {
        goto Done;
    }
    
    if (initialSampleRate.whole == 0) {
        goto Done;
    }
    
    blockTimeoutUS = 1000000 * blockSize / initialSampleRate.whole;
    
    setSampleRate(&initialSampleRate);
    
    // Set the number of sample frames in each buffer
    setNumSampleFramesPerBuffer(blockSize * numBlocks);
    
    wl = getWorkLoop();
    if (!wl) {
        goto Done;
    }
    
    timerEventSource = IOTimerEventSource::timerEventSource(this, timerFired);
    
    if (!timerEventSource) {
        goto Done;
    }
    
    workLoop->addEventSource(timerEventSource);
        
    result = true;
    
Done:

    duringHardwareInit = FALSE;
    
    return result;
}

/*
 * createAudioStreams()
 */
 
bool PhantomAudioEngine::createAudioStreams(IOAudioSampleRate *initialSampleRate)
{
    bool result = false;
    OSNumber *number;
    UInt32 numStreams, streamNum;
    OSArray *formatArray, *sampleRateArray;
    UInt32 startingChannelID = 1;
    IOAudioControl *control;
    OSString *desc;
    OSBoolean *boolean;
    bool separateStreamBuffers = FALSE, separateInputBuffers = FALSE;
    
    desc = OSDynamicCast(OSString, getProperty(DESCRIPTION_KEY));
    if (desc) {
        setDescription(desc->getCStringNoCopy());
    }
    
    number = OSDynamicCast(OSNumber, getProperty(NUM_STREAMS_KEY));
    if (number) {
        numStreams = number->unsigned32BitValue();
    } else {
        numStreams = NUM_STREAMS;
    }
    
    formatArray = OSDynamicCast(OSArray, getProperty(FORMATS_KEY));
    if (formatArray == NULL) {
        goto Done;
    }
    
    sampleRateArray = OSDynamicCast(OSArray, getProperty(SAMPLE_RATES_KEY));
    if (sampleRateArray == NULL) {
        goto Done;
    }
    
    boolean = OSDynamicCast(OSBoolean, getProperty(SEPARATE_STREAM_BUFFERS_KEY));
    if (boolean != NULL) {
        separateStreamBuffers = boolean->getValue();
    }
    
    boolean = OSDynamicCast(OSBoolean, getProperty(SEPARATE_INPUT_BUFFERS_KEY));
    if (boolean != NULL) {
        separateInputBuffers = boolean->getValue();
    }
    
    if (separateStreamBuffers) {
        IOLog("PhantomAudioEngine::createAudioStreams() - Creating a separate buffer for each stream.\n");
    } else {
        IOLog("PhantomAudioEngine::createAudioStreams() - Sharing one buffer among all streams.\n");
    }
    
    if (separateInputBuffers) {
        IOLog("PhantomAudioEngine::createAudioStreams() - Creating separate buffers for input and output.\n");
    } else {
        IOLog("PhantomAudioEngine::createAudioStreams() - Sharing input and output buffers.\n");
    }
    
    for (streamNum = 0; streamNum < numStreams; streamNum++) {
        IOAudioStream *inputStream = NULL, *outputStream = NULL;
        UInt32 maxBitWidth = 0;
        UInt32 maxNumChannels = 0;
        OSCollectionIterator *formatIterator = NULL, *sampleRateIterator = NULL;
        OSDictionary *formatDict;
        IOAudioSampleRate sampleRate;
        IOAudioStreamFormat initialFormat;
        bool initialFormatSet;
        UInt32 channelID;
        char outputStreamName[20], inputStreamName[20];
        UInt32 streamBufferSize;
        
        initialFormatSet = false;
        
        sampleRate.whole = 0;
        sampleRate.fraction = 0;
                
        inputStream = new IOAudioStream;
        if (inputStream == NULL) {
            goto Error;
        }
        
        outputStream = new IOAudioStream;
        if (outputStream == NULL) {
            goto Error;
        }
        
        sprintf(inputStreamName, "Input Stream #%ld", streamNum + 1);
        sprintf(outputStreamName, "Output Stream #%ld", streamNum + 1);

        if (!inputStream->initWithAudioEngine(this, kIOAudioStreamDirectionInput, startingChannelID, inputStreamName) ||
            !outputStream->initWithAudioEngine(this, kIOAudioStreamDirectionOutput, startingChannelID, outputStreamName)) {
            goto Error;
        }
        
        formatIterator = OSCollectionIterator::withCollection(formatArray);
        if (!formatIterator) {
            goto Error;
        }
        
        sampleRateIterator = OSCollectionIterator::withCollection(sampleRateArray);
        if (!sampleRateIterator) {
            goto Error;
        }
        
        formatIterator->reset();
        while (formatDict = (OSDictionary *)formatIterator->getNextObject()) {
            IOAudioStreamFormat format;
            
            if (OSDynamicCast(OSDictionary, formatDict) == NULL) {
                goto Error;
            }
            
            if (IOAudioStream::createFormatFromDictionary(formatDict, &format) == NULL) {
                goto Error;
            }
            
            if (!initialFormatSet) {
                initialFormat = format;
            }
            
            sampleRateIterator->reset();
            while (number = (OSNumber *)sampleRateIterator->getNextObject()) {
                if (!OSDynamicCast(OSNumber, number)) {
                    goto Error;
                }
                
                sampleRate.whole = number->unsigned32BitValue();
                
                inputStream->addAvailableFormat(&format, &sampleRate, &sampleRate);
                if (format.fBitDepth == 24) {
                    IOAudioStream::AudioIOFunction functions[2];
                    functions[0] = process24BitSamples;
                    functions[1] = clip24BitSamples;
                    //outputStream->addAvailableFormat(&format, &sampleRate, &sampleRate, functions, 2);
                    outputStream->addAvailableFormat(&format, &sampleRate, &sampleRate, (IOAudioStream::AudioIOFunction)clip24BitSamples);
					if (format.fNumericRepresentation == kIOAudioStreamSampleFormatLinearPCM && format.fIsMixable == TRUE) {
						format.fIsMixable = FALSE;
						outputStream->addAvailableFormat(&format, &sampleRate, &sampleRate, (IOAudioStream::AudioIOFunction)clip24BitSamples);
					}
                } else if (format.fBitDepth == 16) {
                    IOAudioStream::AudioIOFunction functions[2];
                    functions[0] = process16BitSamples;
                    functions[1] = clip16BitSamples;
                    //outputStream->addAvailableFormat(&format, &sampleRate, &sampleRate, functions, 2);
                    outputStream->addAvailableFormat(&format, &sampleRate, &sampleRate, (IOAudioStream::AudioIOFunction)clip16BitSamples);
					if (format.fNumericRepresentation == kIOAudioStreamSampleFormatLinearPCM && format.fIsMixable == TRUE) {
						format.fIsMixable = FALSE;
						outputStream->addAvailableFormat(&format, &sampleRate, &sampleRate, (IOAudioStream::AudioIOFunction)clip24BitSamples);
					}
                } else {
                    outputStream->addAvailableFormat(&format, &sampleRate, &sampleRate);
					if (format.fNumericRepresentation == kIOAudioStreamSampleFormatLinearPCM && format.fIsMixable == TRUE) {
						format.fIsMixable = FALSE;
						outputStream->addAvailableFormat(&format, &sampleRate, &sampleRate, (IOAudioStream::AudioIOFunction)clip24BitSamples);
					}
                }
                
                if (format.fNumChannels > maxNumChannels) {
                    maxNumChannels = format.fNumChannels;
                }
                
                if (format.fBitWidth > maxBitWidth) {
                    maxBitWidth = format.fBitWidth;
                }
                
                if (initialSampleRate->whole == 0) {
                    initialSampleRate->whole = sampleRate.whole;
                }
            }
        }
        
        streamBufferSize = blockSize * numBlocks * maxNumChannels * maxBitWidth / 8;
        
        if (outputBuffer == NULL) {
            if (separateStreamBuffers) {
                outputBufferSize = streamBufferSize * numStreams;
            } else {
                outputBufferSize = streamBufferSize;
            }

            outputBuffer = (void *)IOMalloc(outputBufferSize);
            if (!outputBuffer) {
                IOLog("Error allocating output buffer - %lu bytes.\n", outputBufferSize);
                goto Error;
            }
            
            inputBufferSize = outputBufferSize;
            
            if (separateInputBuffers) {
                inputBuffer = (void *)IOMalloc(inputBufferSize);
                if (!inputBuffer) {
                    IOLog("Error allocating input buffer - %lu bytes.\n", inputBufferSize);
                    goto Error;
                }
            } else {
                inputBuffer = outputBuffer;
            }
        }
        
        inputStream->setFormat(&initialFormat);
        outputStream->setFormat(&initialFormat);
        
        if (separateStreamBuffers) {
            inputStream->setSampleBuffer(&((UInt8 *)inputBuffer)[streamBufferSize * streamNum], streamBufferSize);
            outputStream->setSampleBuffer(&((UInt8 *)outputBuffer)[streamBufferSize * streamNum], streamBufferSize);
        } else {
            inputStream->setSampleBuffer(inputBuffer, streamBufferSize);
            outputStream->setSampleBuffer(outputBuffer, streamBufferSize);
        }
        addAudioStream(inputStream);
        inputStream->release();
        
        addAudioStream(outputStream);
        outputStream->release();
        
        formatIterator->release();
        sampleRateIterator->release();
        
        for (channelID = startingChannelID; channelID < (startingChannelID + maxNumChannels); channelID++) {
            char channelName[20];
            
            sprintf(channelName, "Channel %lu", channelID);
            
            control = IOAudioLevelControl::createVolumeControl(65535,
                                                                0,
                                                                65535,
                                                                (-22 << 16) + (32768),
                                                                0,
                                                                channelID,
                                                                channelName,
                                                                0,
                                                                kIOAudioControlUsageOutput);
            if (!control) {
                goto Error;
            }
            
            control->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)PhantomAudioDevice::volumeChangeHandler, audioDevice);
            addDefaultAudioControl(control);
            control->release();
            
            control = IOAudioToggleControl::createMuteControl(false,
                                                                channelID,
                                                                channelName,
                                                                0,
                                                                kIOAudioControlUsageOutput);
            if (!control) {
                goto Error;
            }
            
            control->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)PhantomAudioDevice::outputMuteChangeHandler, audioDevice);
            addDefaultAudioControl(control);
            control->release();
                                                                
            control = IOAudioLevelControl::createVolumeControl(65535,
                                                                0,
                                                                65535,
                                                                (-22 << 16) + (32768),
                                                                0,
                                                                channelID,
                                                                channelName,
                                                                0,
                                                                kIOAudioControlUsageInput);
            if (!control) {
                goto Error;
            }
            
            control->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)PhantomAudioDevice::gainChangeHandler, audioDevice);
            addDefaultAudioControl(control);
            control->release();
            
            control = IOAudioToggleControl::createMuteControl(false,
                                                                channelID,
                                                                channelName,
                                                                0,
                                                                kIOAudioControlUsageInput);
            if (!control) {
                goto Error;
            }
            
            control->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)PhantomAudioDevice::inputMuteChangeHandler, audioDevice);
            addDefaultAudioControl(control);
            control->release();
            
            control = IOAudioToggleControl::createMuteControl(true,
                                                                channelID,
                                                                channelName,
                                                                0,
                                                                kIOAudioControlUsagePassThru);
            if (!control) {
                goto Error;
            }
            
            control->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)PhantomAudioDevice::passThruChangeHandler, audioDevice);
            addDefaultAudioControl(control);
            control->release();
        }
        
        startingChannelID += maxNumChannels;
        
        continue;

Error:

        IOLog("PhantomAudioEngine[%p]::createAudioStreams() - ERROR\n", this);
    
        if (inputStream) {
            inputStream->release();
        }
        
        if (outputStream) {
            outputStream->release();
        }
        
        if (formatIterator) {
            formatIterator->release();
        }
        
        if (sampleRateIterator) {
            sampleRateIterator->release();
        }
        
        goto Done;
    }
    
    control = IOAudioLevelControl::createVolumeControl(65535,
                                                        0,
                                                        65535,
                                                        (-22 << 16) + (32768),
                                                        0,
                                                        kIOAudioControlChannelIDAll,
                                                        kIOAudioControlChannelNameAll,
                                                        0,
                                                        kIOAudioControlUsageOutput);
    if (!control) {
        goto Done;
    }
    
    control->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)PhantomAudioDevice::volumeChangeHandler, audioDevice);
    addDefaultAudioControl(control);
    control->release();
    
    control = IOAudioToggleControl::createMuteControl(false,
                                                        kIOAudioControlChannelIDAll,
                                                        kIOAudioControlChannelNameAll,
                                                        0,
                                                        kIOAudioControlUsageOutput);
    if (!control) {
        goto Done;
    }
    
    control->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)PhantomAudioDevice::outputMuteChangeHandler, audioDevice);
    addDefaultAudioControl(control);
    control->release();
                                                        
    control = IOAudioLevelControl::createVolumeControl(65535,
                                                        0,
                                                        65535,
                                                        (-22 << 16) + (32768),
                                                        0,
                                                        kIOAudioControlChannelIDAll,
                                                        kIOAudioControlChannelNameAll,
                                                        0,
                                                        kIOAudioControlUsageInput);
    if (!control) {
        goto Done;
    }
    
    control->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)PhantomAudioDevice::gainChangeHandler, audioDevice);
    addDefaultAudioControl(control);
    control->release();
    
    control = IOAudioToggleControl::createMuteControl(false,
                                                        kIOAudioControlChannelIDAll,
                                                        kIOAudioControlChannelNameAll,
                                                        0,
                                                        kIOAudioControlUsageInput);
    if (!control) {
        goto Done;
    }
    
    control->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)PhantomAudioDevice::inputMuteChangeHandler, audioDevice);
    addDefaultAudioControl(control);
    control->release();
    
    control = IOAudioToggleControl::createMuteControl(true,
                                                        kIOAudioControlChannelIDAll,
                                                        kIOAudioControlChannelNameAll,
                                                        0,
                                                        kIOAudioControlUsagePassThru);
    if (!control) {
        goto Done;
    }
    
    control->setValueChangeHandler((IOAudioControl::IntValueChangeHandler)PhantomAudioDevice::passThruChangeHandler, audioDevice);
    addDefaultAudioControl(control);
    control->release();

    result = true;
    
Done:

    if (!result) {
        IOLog("PhantomAudioEngine[%p]::createAudioStreams() - failed!\n", this);
    }

    return result;
}

/*
 * free()
 */
 
void PhantomAudioEngine::free()
{
    IOLog("PhantomAudioEngine[%p]::free()\n", this);
    
    // We need to free our resources when we're going away
    
    if (inputBuffer != NULL) {
        // We only need to free the input buffer buffer if it was allocated independently of the output buffer
        if (inputBuffer != outputBuffer) {
            IOFree(inputBuffer, inputBufferSize);
        }
        
        inputBuffer = NULL;
    }

    if (outputBuffer != NULL) {
        IOFree(outputBuffer, outputBufferSize);
        outputBuffer = NULL;
    }
    
    super::free();
}

/*
 * stop()
 */
 
void PhantomAudioEngine::stop(IOService *provider)
{
    IOLog("PhantomAudioEngine[%p]::stop(%p)\n", this, provider);
    
    // Add code to shut down hardware (beyond what is needed to simply stop the audio engine)
    // If nothing more needs to be done, this function can be removed

    super::stop(provider);
}

/*
 * performAudioEngineStart()
 */
 
IOReturn PhantomAudioEngine::performAudioEngineStart()
{
    IOLog("PhantomAudioEngine[%p]::performAudioEngineStart()\n", this);
    
    // When performAudioEngineStart() gets called, the audio engine should be started from the beginning
    // of the sample buffer.  Because it is starting on the first sample, a new timestamp is needed
    // to indicate when that sample is being read from/written to.  The function takeTimeStamp() 
    // is provided to do that automatically with the current time.
    // By default takeTimeStamp() will increment the current loop count in addition to taking the current
    // timestamp.  Since we are starting a new audio engine run, and not looping, we don't want the loop count
    // to be incremented.  To accomplish that, false is passed to takeTimeStamp(). 
    
    // The audio engine will also have to take a timestamp each time the buffer wraps around
    // How that is implemented depends on the type of hardware - PCI hardware will likely
    // receive an interrupt to perform that task
    takeTimeStamp(false);
    currentBlock = 0;
    
    timerEventSource->setTimeoutUS(blockTimeoutUS);
    
    return kIOReturnSuccess;
}

/*
 * performAudioEngineStop()
 */
 
IOReturn PhantomAudioEngine::performAudioEngineStop()
{
    IOLog("PhantomAudioEngine[%p]::performAudioEngineStop()\n", this);
    
    timerEventSource->cancelTimeout();
    
    return kIOReturnSuccess;
}

/*
 * getCurrentSampleFrame()
 */
 
UInt32 PhantomAudioEngine::getCurrentSampleFrame()
{
    //IOLog("PhantomAudioEngine[%p]::getCurrentSampleFrame() - currentBlock = %lu\n", this, currentBlock);
    
    // In order for the erase process to run properly, this function must return the current location of
    // the audio engine - basically a sample counter
    // It doesn't need to be exact, but if it is inexact, it should err towards being before the current location
    // rather than after the current location.  The erase head will erase up to, but not including the sample
    // frame returned by this function.  If it is too large a value, sound data that hasn't been played will be 
    // erased.
    
    // Change to return the real value
    return currentBlock * blockSize;
}

/*
 * performFormatChange()
 */
 
IOReturn PhantomAudioEngine::performFormatChange(IOAudioStream *audioStream, const IOAudioStreamFormat *newFormat, const IOAudioSampleRate *newSampleRate)
{
    if (!duringHardwareInit) {
        IOLog("PhantomAudioEngine[%p]::peformFormatChange(%p, %p, %p)\n", this, audioStream, newFormat, newSampleRate);
    }

    // It is possible that this function will be called with only a format or only a sample rate
    // We need to check for NULL for each of the parameters
    if (newFormat) {
        if (!duringHardwareInit) {
            IOLog("  -> %d bits per sample.\n", newFormat->fBitDepth);
        }
    }
    
    if (newSampleRate) {
        if (!duringHardwareInit) {
            IOLog("  -> %ld Hz.\n", newSampleRate->whole);
        }
    }
    
    return kIOReturnSuccess;
}

/*
 * timerFired()
 */
 
void PhantomAudioEngine::timerFired(OSObject *target, IOTimerEventSource *sender)
{
    if (target) {
        PhantomAudioEngine *audioEngine = OSDynamicCast(PhantomAudioEngine, target);
        
        if (audioEngine) {
            audioEngine->currentBlock++;
            if (audioEngine->currentBlock >= audioEngine->numBlocks) {
                audioEngine->currentBlock = 0;
                audioEngine->takeTimeStamp();
            }
            
            sender->setTimeoutUS(audioEngine->blockTimeoutUS);
        }
    }
}
