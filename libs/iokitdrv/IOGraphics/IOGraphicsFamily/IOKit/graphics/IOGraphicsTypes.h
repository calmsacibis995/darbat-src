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
 * Copyright (c) 1998-2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
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

#ifndef _IOKIT_IOGRAPHICSTYPES_H
#define _IOKIT_IOGRAPHICSTYPES_H


#include <IOKit/IOTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#define IOGRAPHICSTYPES_REV	8

typedef SInt32	IOIndex;
typedef UInt32	IOSelect;
typedef UInt32	IOFixed1616;
typedef UInt32	IODisplayVendorID;
typedef UInt32	IODisplayProductID;

typedef SInt32	IODisplayModeID;
enum {
    // This is the ID given to a programmable timing used at boot time
    kIODisplayModeIDBootProgrammable = (long)0xFFFFFFFB,
    // Lowest (unsigned) DisplayModeID reserved by Apple
    kIODisplayModeIDReservedBase  = (long)0x80000000
};

enum {
    kIOMaxPixelBits 	= 64
};
typedef char IOPixelEncoding[ kIOMaxPixelBits ];

// Common Apple pixel formats

#define IO1BitIndexedPixels	"P"
#define IO2BitIndexedPixels	"PP"
#define IO4BitIndexedPixels	"PPPP"
#define IO8BitIndexedPixels	"PPPPPPPP"
#define IO16BitDirectPixels	"-RRRRRGGGGGBBBBB"
#define IO32BitDirectPixels	"--------RRRRRRRRGGGGGGGGBBBBBBBB"

// other possible pixel formats

#define IOYUV422Pixels		"Y4U2V2"
#define IO8BitOverlayPixels	"O8"
// page flipping
#define IOPagedPixels		"Page1"

#define IO_SampleTypeAlpha	'A'
#define IO_SampleTypeSkip	'-'

// Info about a pixel format
enum {
    kIOCLUTPixels		= 0,
    kIOFixedCLUTPixels		= 1,
    kIORGBDirectPixels 		= 2,
    kIOMonoDirectPixels 	= 3,
    kIOMonoInverseDirectPixels	= 4
};

/*!
 * @struct IOPixelInformation
 * @abstract A structure defining the format of a framebuffer.
 * @discussion This structure is used by IOFramebuffer to define the format of the pixels.
 * @field bytesPerRow The number of bytes per row.
 * @field bytesPerPlane Not used.
 * @field bitsPerPixel The number of bits per pixel, including unused bits and alpha.
 * @field pixelType One of kIOCLUTPixels (indexed pixels with changeable CLUT), kIORGBDirectPixels (direct pixels).
 * @field componentCount One for indexed pixels, three for direct pixel formats.
 * @field bitsPerComponent Number of bits per component in each pixel.
 * @field componentMasks Mask of the bits valid for each component of the pixel - in R, G, B order for direct pixels.
 * @field pixelFormat String description of the pixel format - IO32BitDirectPixels, IO16BitDirectPixels etc.
 * @field flags None defined - set to zero.
 * @field activeWidth Number of pixels visible per row.
 * @field activeHeight Number of visible pixel rows.
 * @field reserved Set to zero.
 */

struct IOPixelInformation {
    IOByteCount			bytesPerRow;
    IOByteCount			bytesPerPlane;
    UInt32			bitsPerPixel;
    UInt32			pixelType;
    UInt32			componentCount;
    UInt32			bitsPerComponent;
    UInt32			componentMasks[ 8 * 2 ];
    IOPixelEncoding		pixelFormat;
    UInt32			flags;
    UInt32			activeWidth;
    UInt32			activeHeight;
    UInt32			reserved[ 2 ];
};
typedef struct IOPixelInformation IOPixelInformation;

// ID for industry standard display timings
typedef UInt32  IOAppleTimingID;

/*!
 * @struct IODisplayModeInformation
 * @abstract A structure defining the format of a framebuffer.
 * @discussion This structure is used by IOFramebuffer to define the format of the pixels.
 * @field nominalWidth Number of pixels visible per row.
 * @field nominalHeight Number of visible pixel rows.
 * @field refreshRate Refresh rate in fixed point 16.16.
 * @field maxDepthIndex Highest depth index available in this display mode.
 * @field flags Flags for the mode, including: <br>
    kDisplayModeInterlacedFlag mode is interlaced. <br>
    kDisplayModeSimulscanFlag mode is available on multiple display connections. <br>
    kDisplayModeNotPresetFlag mode is not a factory preset for the display (geometry may need correction). <br>
    kDisplayModeStretchedFlag mode is stretched/distorted to match the display aspect ratio. <br>
 * @field reserved Set to zero.
 */

struct IODisplayModeInformation {
    UInt32			nominalWidth;
    UInt32			nominalHeight;
    IOFixed1616			refreshRate;
    IOIndex			maxDepthIndex;
    UInt32			flags;
    UInt32			reserved[ 4 ];
};
typedef struct IODisplayModeInformation IODisplayModeInformation;

// flags
enum {
    kDisplayModeSafetyFlags		= 0x00000007,

    kDisplayModeAlwaysShowFlag		= 0x00000008,
    kDisplayModeNeverShowFlag		= 0x00000080,
    kDisplayModeNotResizeFlag		= 0x00000010,
    kDisplayModeRequiresPanFlag		= 0x00000020,

    kDisplayModeInterlacedFlag		= 0x00000040,

    kDisplayModeSimulscanFlag		= 0x00000100,
    kDisplayModeBuiltInFlag		= 0x00000400,
    kDisplayModeNotPresetFlag		= 0x00000200,
    kDisplayModeStretchedFlag		= 0x00000800,
    kDisplayModeNotGraphicsQualityFlag	= 0x00001000,
    kDisplayModeTelevisionFlag		= 0x00100000
};
enum {
    kDisplayModeValidFlag		= 0x00000001,
    kDisplayModeSafeFlag		= 0x00000002,
    kDisplayModeDefaultFlag		= 0x00000004
};

// Framebuffer info - obsolete

struct IOFramebufferInformation {
    IOPhysicalAddress		baseAddress;
    UInt32			activeWidth;
    UInt32			activeHeight;
    IOByteCount			bytesPerRow;
    IOByteCount			bytesPerPlane;
    UInt32			bitsPerPixel;
    UInt32			pixelType;
    UInt32			flags;
    UInt32			reserved[ 4 ];
};
typedef struct IOFramebufferInformation IOFramebufferInformation;

// flags
enum {
    kFramebufferSupportsCopybackCache	= 0x00010000,
    kFramebufferSupportsWritethruCache	= 0x00020000,
    kFramebufferSupportsGammaCorrection	= 0x00040000,
    kFramebufferDisableAltivecAccess	= 0x00080000
};

// Aperture is an index into supported pixel formats for a mode & depth
typedef IOIndex IOPixelAperture;
enum {
    kIOFBSystemAperture	= 0
};

//// CLUTs

typedef UInt16 IOColorComponent;

/*!
 * @struct IOColorEntry
 * @abstract A structure defining one entry of a color lookup table.
 * @discussion This structure is used by IOFramebuffer to define an entry of a color lookup table.
 * @field index Number of pixels visible per row.
 * @field red Value of red component 0-65535.
 * @field green Value of green component 0-65535.
 * @field blue Value of blue component 0-65535.
 */

struct IOColorEntry {
    UInt16	   		index;
    IOColorComponent   		red;
    IOColorComponent   		green;
    IOColorComponent   		blue;
};
typedef struct IOColorEntry IOColorEntry;

// options (masks)
enum {
    kSetCLUTByValue		= 0x00000001,		// else at index
    kSetCLUTImmediately		= 0x00000002,		// else at VBL
    kSetCLUTWithLuminance	= 0x00000004		// else RGB
};

//// Controller attributes

enum {
    kIOPowerAttribute			= 'powr',
    kIOHardwareCursorAttribute		= 'crsr',

    kIOMirrorAttribute			= 'mirr',
    kIOMirrorDefaultAttribute		= 'mrdf',

    kIOCapturedAttribute		= 'capd',

    kIOCursorControlAttribute		= 'crsc',

    kIOSystemPowerAttribute		= 'spwr',
    kIOVRAMSaveAttribute		= 'vrsv',
    kIODeferCLUTSetAttribute		= 'vclt'
};

// values for kIOMirrorAttribute
enum {
    kIOMirrorIsPrimary			= 0x80000000,
    kIOMirrorHWClipped			= 0x40000000
};

// values for kIOMirrorDefaultAttribute
enum {
    kIOMirrorDefault			= 0x00000001,
    kIOMirrorForced			= 0x00000002
};

//// Display mode timing information

struct IODetailedTimingInformationV1 {
    // from EDID defn
    UInt32			pixelClock;		// Hertz
    UInt32			horizontalActive;	// pixels
    UInt32			horizontalBlanking;	// pixels
    UInt32			horizontalBorder;	// pixels
    UInt32			horizontalSyncOffset;	// pixels
    UInt32			horizontalSyncWidth;	// pixels
    UInt32			verticalActive;		// lines
    UInt32			verticalBlanking;	// lines
    UInt32			verticalBorder;		// lines
    UInt32			verticalSyncOffset;	// lines
    UInt32			verticalSyncWidth;	// lines
};
typedef struct IODetailedTimingInformationV1 IODetailedTimingInformationV1;

/*!
 * @struct IODetailedTimingInformationV2
 * @abstract A structure defining the detailed timing information of a display mode.
 * @discussion This structure is used by IOFramebuffer to define detailed timing information for a display mode. The VESA EDID document has more information.
 * @field __reservedA Set to zero.
 * @field horizontalScaledInset If the mode is scaled, sets the number of active pixels to remove the left and right edges in order to display an underscanned image.
 * @field verticalScaledInset If the mode is scaled, sets the number of active lines to remove the top and bottom edges in order to display an underscanned image.
 * @field scalerFlags If the mode is scaled,
     kIOScaleStretchToFit may be set to allow stretching.
     kIOScaleRotateFlags is mask which may have the value given by kIOScaleRotate90, kIOScaleRotate180, kIOScaleRotate270 to display a rotated framebuffer.
 * @field horizontalScaled If the mode is scaled, sets the size of the image before scaling or rotation.
 * @field verticalScaled If the mode is scaled, sets the size of the image before scaling or rotation.
 * @field signalConfig 
    kIOAnalogSetupExpected set if display expects a blank-to-black setup or pedestal.  See VESA signal standards. <br>
    kIOInterlacedCEATiming set for a CEA style interlaced timing:<br>
	Field 1 vertical blanking = half specified vertical blanking lines. <br>
	Field 2 vertical blanking = (half vertical blanking lines) + 1 line. <br>
	Field 1 vertical offset = half specified vertical sync offset. <br>
	Field 2 vertical offset = (half specified vertical sync offset) + 0.5 lines. <br>
 * @field signalLevels One of:<br>
    kIOAnalogSignalLevel_0700_0300 0.700 - 0.300 V p-p.<br>
    kIOAnalogSignalLevel_0714_0286 0.714 - 0.286 V p-p.<br>
    kIOAnalogSignalLevel_1000_0400 1.000 - 0.400 V p-p.<br>
    kIOAnalogSignalLevel_0700_0000 0.700 - 0.000 V p-p.<br>
 * @field pixelClock Pixel clock frequency in Hz.
 * @field minPixelClock Minimum pixel clock frequency in Hz, with error.
 * @field maxPixelClock Maximum pixel clock frequency in Hz, with error.
 * @field horizontalActive Pixel clocks per line.
 * @field horizontalBlanking Blanking clocks per line.
 * @field horizontalSyncOffset First clock of horizontal sync.
 * @field horizontalSyncPulseWidth Width of horizontal sync.
 * @field verticalActive Number of lines per frame.
 * @field verticalBlanking Blanking lines per frame.
 * @field verticalSyncOffset First line of vertical sync.
 * @field verticalSyncPulseWidth Height of vertical sync.
 * @field horizontalBorderLeft Number of pixels in left horizontal border.
 * @field horizontalBorderRight Number of pixels in right horizontal border.
 * @field verticalBorderTop Number of lines in top vertical border.
 * @field verticalBorderBottom Number of lines in bottom vertical border.
 * @field horizontalSyncConfig kIOSyncPositivePolarity for positive polarity horizontal sync (0 for negative).
 * @field horizontalSyncLevel Zero.
 * @field verticalSyncConfig kIOSyncPositivePolarity for positive polarity vertical sync (0 for negative).
 * @field verticalSyncLevel Zero.
 * @field numLinks number of links to be used by a dual link timing, if zero, assume one link.
 * @field __reservedB Reserved set to zero.
 */

struct IODetailedTimingInformationV2 {

    UInt32	__reservedA[3];			// Init to 0
    UInt32	horizontalScaledInset;		// pixels
    UInt32	verticalScaledInset;		// lines

    UInt32	scalerFlags;
    UInt32	horizontalScaled;
    UInt32	verticalScaled;

    UInt32	signalConfig;
    UInt32	signalLevels;

    UInt64	pixelClock;			// Hz

    UInt64	minPixelClock;			// Hz - With error what is slowest actual clock
    UInt64	maxPixelClock;			// Hz - With error what is fasted actual clock

    UInt32	horizontalActive;	  	// pixels
    UInt32	horizontalBlanking;	  	// pixels
    UInt32	horizontalSyncOffset;	  	// pixels
    UInt32	horizontalSyncPulseWidth;	// pixels

    UInt32	verticalActive;			// lines
    UInt32	verticalBlanking;		// lines
    UInt32	verticalSyncOffset;		// lines
    UInt32	verticalSyncPulseWidth;		// lines

    UInt32	horizontalBorderLeft;		// pixels
    UInt32	horizontalBorderRight;		// pixels
    UInt32	verticalBorderTop;		// lines
    UInt32	verticalBorderBottom;		// lines

    UInt32	horizontalSyncConfig;
    UInt32	horizontalSyncLevel;		// Future use (init to 0)
    UInt32	verticalSyncConfig;
    UInt32	verticalSyncLevel;		// Future use (init to 0)
    UInt32	numLinks;

    UInt32	__reservedB[7];			// Init to 0
};
typedef struct IODetailedTimingInformationV2 IODetailedTimingInformationV2;
typedef struct IODetailedTimingInformationV2 IODetailedTimingInformation;

struct IOTimingInformation {
    IOAppleTimingID		appleTimingID;	// kIOTimingIDXXX const
    UInt32			flags;
    union {
      IODetailedTimingInformationV1	v1;
      IODetailedTimingInformationV2	v2;
    }				detailedInfo;
};
typedef struct IOTimingInformation IOTimingInformation;

enum {
    // IOTimingInformation flags
    kIODetailedTimingValid	= 0x80000000,
    kIOScalingInfoValid		= 0x40000000
};

enum {
    // scalerFlags
    kIOScaleStretchToFit	= 0x00000001,

    kIOScaleRotateFlags		= 0x000000f0,

    kIOScaleSwapAxes		= 0x00000010,
    kIOScaleInvertX		= 0x00000020,
    kIOScaleInvertY		= 0x00000040,

    kIOScaleRotate0		= 0x00000000,
    kIOScaleRotate90		= kIOScaleSwapAxes | kIOScaleInvertX,
    kIOScaleRotate180		= kIOScaleInvertX  | kIOScaleInvertY,
    kIOScaleRotate270		= kIOScaleSwapAxes | kIOScaleInvertY
};


struct IOFBDisplayModeDescription {
    IODisplayModeInformation	info;
    IOTimingInformation 	timingInfo;
};
typedef struct IOFBDisplayModeDescription IOFBDisplayModeDescription;

/*!
 * @struct IODisplayTimingRange
 * @abstract A structure defining the limits and attributes of a display or framebuffer.
 * @discussion This structure is used to define the limits for modes programmed as detailed timings by the OS. The VESA EDID is useful background information for many of these fields. A data property with this structure under the key kIOFBTimingRangeKey in a framebuffer will allow the OS to program detailed timings that fall within its range.
 * @field __reservedA Set to zero.
 * @field version Set to zero.
 * @field __reservedB Set to zero.
 * @field minPixelClock minimum pixel clock frequency in range, in Hz.
 * @field minPixelClock maximum pixel clock frequency in range, in Hz.
 * @field maxPixelError largest variation between specified and actual pixel clock frequency, in Hz.
 * @field supportedSyncFlags mask of supported sync attributes. The following are defined:<br>
    kIORangeSupportsSeparateSyncs - digital separate syncs.<br>
    kIORangeSupportsSyncOnGreen - sync on green.<br>
    kIORangeSupportsCompositeSync - composite sync.<br>
    kIORangeSupportsVSyncSerration - vertical sync has serration and equalization pulses.<br>
 * @field supportedSignalLevels mask of possible signal levels. The following are defined:<br>
    kIORangeSupportsSignal_0700_0300 0.700 - 0.300 V p-p.<br>
    kIORangeSupportsSignal_0714_0286 0.714 - 0.286 V p-p.<br>
    kIORangeSupportsSignal_1000_0400 1.000 - 0.400 V p-p.<br>
    kIORangeSupportsSignal_0700_0000 0.700 - 0.000 V p-p.<br>
 * @field supportedSignalConfigs mask of possible signal configurations. The following are defined:<br>
    kIORangeSupportsInterlacedCEATiming Supports CEA style interlaced timing:<br>
	Field 1 vertical blanking = specified vertical blanking lines. <br>
	Field 2 vertical blanking = vertical blanking lines + 1 line. <br>
	Field 1 vertical offset = specified vertical sync offset. <br>
	Field 2 vertical offset = specified vertical sync offset + 0.5 lines. <br>
 * @field minFrameRate minimum frame rate (vertical refresh frequency) in range, in Hz.
 * @field maxFrameRate maximum frame rate (vertical refresh frequency) in range, in Hz.
 * @field minLineRate minimum line rate (horizontal refresh frequency) in range, in Hz.
 * @field maxLineRate maximum line rate (horizontal refresh frequency) in range, in Hz.
 * @field maxHorizontalTotal maximum clocks in horizontal line (active + blanking).
 * @field maxVerticalTotal maximum lines in vertical frame (active + blanking).
 * @field __reservedD Set to zero.
 * @field charSizeHorizontalActive horizontalActive must be a multiple of charSizeHorizontalActive.
 * @field charSizeHorizontalBlanking horizontalBlanking must be a multiple of charSizeHorizontalBlanking.
 * @field charSizeHorizontalSyncOffset horizontalSyncOffset must be a multiple of charSizeHorizontalSyncOffset.
 * @field charSizeHorizontalSyncPulse horizontalSyncPulse must be a multiple of charSizeHorizontalSyncPulse.
 * @field charSizeVerticalActive verticalActive must be a multiple of charSizeVerticalActive.
 * @field charSizeVerticalBlanking verticalBlanking must be a multiple of charSizeVerticalBlanking.
 * @field charSizeVerticalSyncOffset verticalSyncOffset must be a multiple of charSizeVerticalSyncOffset.
 * @field charSizeVerticalSyncPulse verticalSyncPulse must be a multiple of charSizeVerticalSyncPulse.
 * @field charSizeHorizontalBorderLeft horizontalBorderLeft must be a multiple of charSizeHorizontalBorderLeft.
 * @field charSizeHorizontalBorderRight horizontalBorderRight must be a multiple of charSizeHorizontalBorderRight.
 * @field charSizeVerticalBorderTop verticalBorderTop must be a multiple of charSizeVerticalBorderTop.
 * @field charSizeVerticalBorderBottom verticalBorderBottom must be a multiple of charSizeVerticalBorderBottom.
 * @field charSizeHorizontalTotal (horizontalActive + horizontalBlanking) must be a multiple of charSizeHorizontalTotal.
 * @field charSizeVerticalTotal (verticalActive + verticalBlanking) must be a multiple of charSizeVerticalTotal.
 * @field __reservedE Set to zero.
 * @field minHorizontalActiveClocks minimum value of horizontalActive.
 * @field maxHorizontalActiveClocks maximum value of horizontalActive.
 * @field minHorizontalBlankingClocks minimum value of horizontalBlanking.
 * @field maxHorizontalBlankingClocks maximum value of horizontalBlanking.
 * @field minHorizontalSyncOffsetClocks minimum value of horizontalSyncOffset.
 * @field maxHorizontalSyncOffsetClocks maximum value of horizontalSyncOffset.
 * @field minHorizontalPulseWidthClocks minimum value of horizontalPulseWidth.
 * @field maxHorizontalPulseWidthClocks maximum value of horizontalPulseWidth.
 * @field minVerticalActiveClocks minimum value of verticalActive.
 * @field maxVerticalActiveClocks maximum value of verticalActive.
 * @field minVerticalBlankingClocks minimum value of verticalBlanking.
 * @field maxVerticalBlankingClocks maximum value of verticalBlanking.
 * @field minVerticalSyncOffsetClocks minimum value of verticalSyncOffset.
 * @field maxVerticalSyncOffsetClocks maximum value of verticalSyncOffset.
 * @field minVerticalPulseWidthClocks minimum value of verticalPulseWidth.
 * @field maxVerticalPulseWidthClocks maximum value of verticalPulseWidth.
 * @field minHorizontalBorderLeft minimum value of horizontalBorderLeft.
 * @field maxHorizontalBorderLeft maximum value of horizontalBorderLeft.
 * @field minHorizontalBorderRight minimum value of horizontalBorderRight.
 * @field maxHorizontalBorderRight maximum value of horizontalBorderRight.
 * @field minVerticalBorderTop minimum value of verticalBorderTop.
 * @field maxVerticalBorderTop maximum value of verticalBorderTop.
 * @field minVerticalBorderBottom minimum value of verticalBorderBottom.
 * @field maxVerticalBorderBottom maximum value of verticalBorderBottom.
 * @field maxNumLinks number of links supported, if zero, 1 link is assumed.
 * @field minLink0PixelClock minimum pixel clock for link 0 (kHz).
 * @field maxLink0PixelClock maximum pixel clock for link 0 (kHz).
 * @field minLink1PixelClock minimum pixel clock for link 1 (kHz).
 * @field maxLink1PixelClock maximum pixel clock for link 1 (kHz).
 * @field __reservedF Set to zero.
 */

struct IODisplayTimingRange
{
    UInt32	__reservedA[2];			// Init to 0
    UInt32	version;			// Init to 0
    UInt32	__reservedB[5];			// Init to 0

    UInt64	minPixelClock;            	// Min dot clock in Hz
    UInt64	maxPixelClock;            	// Max dot clock in Hz

    UInt32	maxPixelError;            	// Max dot clock error
    UInt32	supportedSyncFlags;
    UInt32	supportedSignalLevels;
    UInt32	supportedSignalConfigs;

    UInt32	minFrameRate;             	// Hz
    UInt32	maxFrameRate;             	// Hz
    UInt32	minLineRate;              	// Hz
    UInt32	maxLineRate;              	// Hz

    UInt32	maxHorizontalTotal;       	// Clocks - Maximum total (active + blanking)
    UInt32	maxVerticalTotal;         	// Clocks - Maximum total (active + blanking)
    UInt32	__reservedD[2];			// Init to 0

    UInt8	charSizeHorizontalActive;
    UInt8	charSizeHorizontalBlanking; 	
    UInt8	charSizeHorizontalSyncOffset; 
    UInt8	charSizeHorizontalSyncPulse; 

    UInt8	charSizeVerticalActive;   	
    UInt8	charSizeVerticalBlanking; 	
    UInt8	charSizeVerticalSyncOffset; 	
    UInt8	charSizeVerticalSyncPulse; 	

    UInt8	charSizeHorizontalBorderLeft; 
    UInt8	charSizeHorizontalBorderRight; 
    UInt8	charSizeVerticalBorderTop; 	
    UInt8	charSizeVerticalBorderBottom; 

    UInt8	charSizeHorizontalTotal;  		// Character size for active + blanking
    UInt8	charSizeVerticalTotal;    		// Character size for active + blanking
    UInt16	__reservedE;  		      		// Reserved (Init to 0)

    UInt32	minHorizontalActiveClocks;
    UInt32	maxHorizontalActiveClocks;
    UInt32	minHorizontalBlankingClocks;
    UInt32	maxHorizontalBlankingClocks;

    UInt32	minHorizontalSyncOffsetClocks;
    UInt32	maxHorizontalSyncOffsetClocks;
    UInt32	minHorizontalPulseWidthClocks;
    UInt32	maxHorizontalPulseWidthClocks;

    UInt32	minVerticalActiveClocks;
    UInt32	maxVerticalActiveClocks;
    UInt32	minVerticalBlankingClocks;
    UInt32	maxVerticalBlankingClocks;

    UInt32	minVerticalSyncOffsetClocks;
    UInt32	maxVerticalSyncOffsetClocks;
    UInt32	minVerticalPulseWidthClocks;
    UInt32	maxVerticalPulseWidthClocks;

    UInt32	minHorizontalBorderLeft;
    UInt32	maxHorizontalBorderLeft;
    UInt32	minHorizontalBorderRight;
    UInt32	maxHorizontalBorderRight;

    UInt32	minVerticalBorderTop;
    UInt32	maxVerticalBorderTop;
    UInt32	minVerticalBorderBottom;
    UInt32	maxVerticalBorderBottom;
    UInt32	maxNumLinks;                       // number of links, if zero, assume link 1
    UInt32	minLink0PixelClock;      	   // min pixel clock for link 0 (kHz)
    UInt32	maxLink0PixelClock;                // max pixel clock for link 0 (kHz)
    UInt32	minLink1PixelClock;                // min pixel clock for link 1 (kHz)
    UInt32	maxLink1PixelClock;                // max pixel clock for link 1 (kHz)

    UInt32	__reservedF[3];			// Init to 0
};
typedef struct IODisplayTimingRange  IODisplayTimingRange;

enum {
    // supportedSignalLevels
    kIORangeSupportsSignal_0700_0300	= 0x00000001,
    kIORangeSupportsSignal_0714_0286	= 0x00000002,
    kIORangeSupportsSignal_1000_0400	= 0x00000004,
    kIORangeSupportsSignal_0700_0000	= 0x00000008
};
enum {
    // supportedSyncFlags
    kIORangeSupportsSeparateSyncs	 = 0x00000001,
    kIORangeSupportsSyncOnGreen		 = 0x00000002,
    kIORangeSupportsCompositeSync	 = 0x00000004,
    kIORangeSupportsVSyncSerration	 = 0x00000008
};
enum {
    // supportedSignalConfigs
    kIORangeSupportsInterlacedCEATiming	 = 0x00000004
};

enum {
    // signalConfig
    kIODigitalSignal          = 0x00000001,
    kIOAnalogSetupExpected    = 0x00000002,
    kIOInterlacedCEATiming    = 0x00000004,
    kIONTSCTiming             = 0x00000008,
    kIOPALTiming              = 0x00000010
};

enum {
    // signalLevels for analog
    kIOAnalogSignalLevel_0700_0300 = 0,
    kIOAnalogSignalLevel_0714_0286 = 1,
    kIOAnalogSignalLevel_1000_0400 = 2,
    kIOAnalogSignalLevel_0700_0000 = 3
};

enum {
    // horizontalSyncConfig and verticalSyncConfig
    kIOSyncPositivePolarity     = 0x00000001
};

/*!
 * @struct IODisplayScalerInformation
 * @abstract A structure defining the scaling capabilities of a framebuffer.
 * @discussion This structure is used to define the limits for modes programmed as detailed timings by the OS. A data property with this structure under the key kIOFBScalerInfoKey in a framebuffer will allow the OS to program detailed timings that are scaled to a displays native resolution.
 * @field __reservedA Set to zero.
 * @field version Set to zero.
 * @field __reservedB Set to zero.
 * @field scalerFeatures Mask of scaling features. The following are defined:<br>
    kIOScaleStretchOnly If set the framebuffer can only provide stretched scaling with non-square pixels, without borders.<br>
    kIOScaleCanUpSamplePixels If set framebuffer can scale up from a smaller number of source pixels to a larger native timing (eg. 640x480 pixels on a 1600x1200 timing).<br>
    kIOScaleCanDownSamplePixels If set framebuffer can scale down from a larger number of source pixels to a smaller native timing (eg. 1600x1200 pixels on a 640x480 timing).<br>
    kIOScaleCanScaleInterlaced If set framebuffer can scale an interlaced detailed timing.<br>
    kIOScaleCanSupportInset If set framebuffer can support scaled modes with non-zero horizontalScaledInset, verticalScaledInset fields.<br>
    kIOScaleCanRotate If set framebuffer can support some of the flags in the kIOScaleRotateFlags mask.<br>
 * @field maxHorizontalPixels Maximum number of horizontal source pixels (horizontalScaled).<br>
 * @field maxVerticalPixels Maximum number of vertical source pixels (verticalScaled).<br>
 * @field __reservedC Set to zero.
 */

struct IODisplayScalerInformation {
    UInt32		__reservedA[1];		// Init to 0
    UInt32		version;		// Init to 0
    UInt32		__reservedB[2];		// Init to 0
    
    IOOptionBits	scalerFeatures;
    UInt32		maxHorizontalPixels;
    UInt32		maxVerticalPixels;
    UInt32		__reservedC[5];		// Init to 0
};
typedef struct IODisplayScalerInformation IODisplayScalerInformation;

enum {
    /* scalerFeatures */
    kIOScaleStretchOnly		  = 0x00000001,
    kIOScaleCanUpSamplePixels	  = 0x00000002,
    kIOScaleCanDownSamplePixels   = 0x00000004,
    kIOScaleCanScaleInterlaced    = 0x00000008,
    kIOScaleCanSupportInset       = 0x00000010,
    kIOScaleCanRotate    	  = 0x00000020
};

//// Connections

enum {
    kOrConnections			= 0xffffffe,
    kAndConnections			= 0xffffffd
};

enum {
    kConnectionFlags			= 'flgs',
    kConnectionSyncEnable		= 'sync',
    kConnectionSyncFlags		= 'sycf',
    kConnectionSupportsAppleSense	= 'asns',
    kConnectionSupportsLLDDCSense	= 'lddc',
    kConnectionSupportsHLDDCSense	= 'hddc',
    kConnectionEnable			= 'enab',
    kConnectionChanged			= 'chng',
    kConnectionPower			= 'powr',
    kConnectionPostWake			= 'pwak',
    kConnectionDisplayParameterCount	= 'pcnt',
    kConnectionDisplayParameters	= 'parm',
    kConnectionOverscan			= 'oscn',
    kConnectionVideoBest		= 'vbst'
};

// kConnectionFlags values
enum {
    kIOConnectionBuiltIn		= 0x00000800
};

// kConnectionSyncControl values
enum {
    kIOHSyncDisable			= 0x00000001,
    kIOVSyncDisable			= 0x00000002,
    kIOCSyncDisable			= 0x00000004,
    kIONoSeparateSyncControl		= 0x00000040,
    kIOTriStateSyncs			= 0x00000080,
    kIOSyncOnBlue			= 0x00000008,
    kIOSyncOnGreen			= 0x00000010,
    kIOSyncOnRed			= 0x00000020
};


#define IO_DISPLAY_CAN_FILL		0x00000040
#define IO_DISPLAY_CAN_BLIT		0x00000020

#define IO_24BPP_TRANSFER_TABLE_SIZE	256
#define IO_15BPP_TRANSFER_TABLE_SIZE	256
#define IO_8BPP_TRANSFER_TABLE_SIZE	256
#define IO_12BPP_TRANSFER_TABLE_SIZE	256
#define IO_2BPP_TRANSFER_TABLE_SIZE	256

#define STDFB_BM256_TO_BM38_MAP_SIZE	256
#define STDFB_BM38_TO_BM256_MAP_SIZE	256
#define STDFB_BM38_TO_256_WITH_LOGICAL_SIZE	\
	(STDFB_BM38_TO_BM256_MAP_SIZE + (256/sizeof(int)))

#define STDFB_4BPS_TO_5BPS_MAP_SIZE	16
#define STDFB_5BPS_TO_4BPS_MAP_SIZE	32

enum {
    // connection types for IOServiceOpen
    kIOFBServerConnectType		= 0,
    kIOFBSharedConnectType		= 1
};

enum {
    // options for IOServiceRequestProbe()
    kIOFBUserRequestProbe		= 0x00000001
};

struct IOGPoint {
    SInt16	x;
    SInt16	y;
};
typedef struct IOGPoint IOGPoint;

struct IOGSize {
    SInt16	width;
    SInt16	height;
};
typedef struct IOGSize IOGSize;

struct IOGBounds {
    SInt16	minx;
    SInt16	maxx;
    SInt16	miny;
    SInt16	maxy;
};
typedef struct IOGBounds IOGBounds;

#if !defined(__Point__) && !defined(BINTREE_H) && !defined(__MACTYPES__)
#define __Point__
typedef IOGPoint Point;
#endif

#if !defined(__Bounds__) && !defined(BINTREE_H) && !defined(__MACTYPES__)
#define __Bounds__
typedef IOGBounds Bounds;
#endif

// cursor description

enum {
   kTransparentEncoding 	= 0,
   kInvertingEncoding
};

enum {
   kTransparentEncodingShift	= (kTransparentEncoding << 1),
   kTransparentEncodedPixel	= (0x01 << kTransparentEncodingShift),

   kInvertingEncodingShift	= (kInvertingEncoding << 1),
   kInvertingEncodedPixel	= (0x01 << kInvertingEncodingShift)
};

enum {
   kHardwareCursorDescriptorMajorVersion	= 0x0001,
   kHardwareCursorDescriptorMinorVersion	= 0x0000
};

/*!
 * @struct IOHardwareCursorDescriptor
 * @abstract A structure defining the format of a hardware cursor.
 * @discussion This structure is used by IOFramebuffer to define the format of a hardware cursor.
 * @field majorVersion Set to kHardwareCursorDescriptorMajorVersion.
 * @field minorVersion Set to kHardwareCursorDescriptorMinorVersion.
 * @field height Maximum size of the cursor.
 * @field width Maximum size of the cursor.
 * @field bitDepth Number bits per pixel, or a QD/QT pixel type, for example kIO8IndexedPixelFormat, kIO32ARGBPixelFormat.
 * @field maskBitDepth Unused.
 * @field numColors Number of colors for indexed pixel types.
 * @field colorEncodings An array pointer specifying the pixel values corresponding to the indices into the color table, for indexed pixel types.
 * @field flags None defined, set to zero.
 * @field supportedSpecialEncodings Mask of supported special pixel values, eg. kTransparentEncodedPixel, kInvertingEncodedPixel.
 * @field specialEncodings Array of pixel values for each supported special encoding.
 */

struct IOHardwareCursorDescriptor {
   UInt16		majorVersion;
   UInt16		minorVersion;
   UInt32		height;
   UInt32		width;
   UInt32		bitDepth;			// bits per pixel, or a QD/QT pixel type
   UInt32		maskBitDepth;			// unused
   UInt32		numColors;			// number of colors in the colorMap. ie. 
   UInt32 *		colorEncodings;
   UInt32		flags;
   UInt32		supportedSpecialEncodings;
   UInt32		specialEncodings[16];
};
typedef struct IOHardwareCursorDescriptor IOHardwareCursorDescriptor;

// interrupt types

enum {
    kIOFBVBLInterruptType		= 'vbl ',
    kIOFBHBLInterruptType		= 'hbl ',
    kIOFBFrameInterruptType		= 'fram',
    // Demand to check configuration (Hardware unchanged)
    kIOFBConnectInterruptType		= 'dci ',
    // Demand to rebuild (Hardware has reinitialized on dependent change)
    kIOFBChangedInterruptType		= 'chng',
    // Demand to remove framebuffer (Hardware not available on dependent change -- but must not buserror)
    kIOFBOfflineInterruptType		= 'remv',
    // Notice that hardware is available (after being removed)
    kIOFBOnlineInterruptType		= 'add '
};

// IOAppleTimingID's
enum {
    kIOTimingIDInvalid               = 0,	/*  Not a standard timing */
    kIOTimingIDApple_FixedRateLCD    = 42,	/*  Lump all fixed-rate LCDs into one category.*/
    kIOTimingIDApple_512x384_60hz    = 130,	/*  512x384  (60 Hz) Rubik timing. */
    kIOTimingIDApple_560x384_60hz    = 135,	/*  560x384  (60 Hz) Rubik-560 timing. */
    kIOTimingIDApple_640x480_67hz    = 140,	/*  640x480  (67 Hz) HR timing. */
    kIOTimingIDApple_640x400_67hz    = 145,	/*  640x400  (67 Hz) HR-400 timing. */
    kIOTimingIDVESA_640x480_60hz     = 150,	/*  640x480  (60 Hz) VGA timing. */
    kIOTimingIDVESA_640x480_72hz     = 152,	/*  640x480  (72 Hz) VGA timing. */
    kIOTimingIDVESA_640x480_75hz     = 154,	/*  640x480  (75 Hz) VGA timing. */
    kIOTimingIDVESA_640x480_85hz     = 158,	/*  640x480  (85 Hz) VGA timing. */
    kIOTimingIDGTF_640x480_120hz     = 159,	/*  640x480  (120 Hz) VESA Generalized Timing Formula */
    kIOTimingIDApple_640x870_75hz    = 160,	/*  640x870  (75 Hz) FPD timing.*/
    kIOTimingIDApple_640x818_75hz    = 165,	/*  640x818  (75 Hz) FPD-818 timing.*/
    kIOTimingIDApple_832x624_75hz    = 170,	/*  832x624  (75 Hz) GoldFish timing.*/
    kIOTimingIDVESA_800x600_56hz     = 180,	/*  800x600  (56 Hz) SVGA timing. */
    kIOTimingIDVESA_800x600_60hz     = 182,	/*  800x600  (60 Hz) SVGA timing. */
    kIOTimingIDVESA_800x600_72hz     = 184,	/*  800x600  (72 Hz) SVGA timing. */
    kIOTimingIDVESA_800x600_75hz     = 186,	/*  800x600  (75 Hz) SVGA timing. */
    kIOTimingIDVESA_800x600_85hz     = 188,	/*  800x600  (85 Hz) SVGA timing. */
    kIOTimingIDVESA_1024x768_60hz    = 190,	/* 1024x768  (60 Hz) VESA 1K-60Hz timing. */
    kIOTimingIDVESA_1024x768_70hz    = 200,	/* 1024x768  (70 Hz) VESA 1K-70Hz timing. */
    kIOTimingIDVESA_1024x768_75hz    = 204,	/* 1024x768  (75 Hz) VESA 1K-75Hz timing (very similar to kIOTimingIDApple_1024x768_75hz). */
    kIOTimingIDVESA_1024x768_85hz    = 208,	/* 1024x768  (85 Hz) VESA timing. */
    kIOTimingIDApple_1024x768_75hz   = 210,	/* 1024x768  (75 Hz) Apple 19" RGB. */
    kIOTimingIDApple_1152x870_75hz   = 220,	/* 1152x870  (75 Hz) Apple 21" RGB. */
    kIOTimingIDAppleNTSC_ST          = 230,	/*  512x384  (60 Hz, interlaced, non-convolved). */
    kIOTimingIDAppleNTSC_FF          = 232,	/*  640x480  (60 Hz, interlaced, non-convolved). */
    kIOTimingIDAppleNTSC_STconv      = 234,	/*  512x384  (60 Hz, interlaced, convolved). */
    kIOTimingIDAppleNTSC_FFconv      = 236,	/*  640x480  (60 Hz, interlaced, convolved). */
    kIOTimingIDApplePAL_ST           = 238,	/*  640x480  (50 Hz, interlaced, non-convolved). */
    kIOTimingIDApplePAL_FF           = 240,	/*  768x576  (50 Hz, interlaced, non-convolved). */
    kIOTimingIDApplePAL_STconv       = 242,	/*  640x480  (50 Hz, interlaced, convolved). */
    kIOTimingIDApplePAL_FFconv       = 244,	/*  768x576  (50 Hz, interlaced, convolved). */
    kIOTimingIDVESA_1280x960_75hz    = 250,	/* 1280x960  (75 Hz) */
    kIOTimingIDVESA_1280x960_60hz    = 252,	/* 1280x960  (60 Hz) */
    kIOTimingIDVESA_1280x960_85hz    = 254,	/* 1280x960  (85 Hz) */
    kIOTimingIDVESA_1280x1024_60hz   = 260,	/* 1280x1024 (60 Hz) */
    kIOTimingIDVESA_1280x1024_75hz   = 262,	/* 1280x1024 (75 Hz) */
    kIOTimingIDVESA_1280x1024_85hz   = 268,	/* 1280x1024 (85 Hz) */
    kIOTimingIDVESA_1600x1200_60hz   = 280,	/* 1600x1200 (60 Hz) VESA timing. */
    kIOTimingIDVESA_1600x1200_65hz   = 282,	/* 1600x1200 (65 Hz) VESA timing. */
    kIOTimingIDVESA_1600x1200_70hz   = 284,	/* 1600x1200 (70 Hz) VESA timing. */
    kIOTimingIDVESA_1600x1200_75hz   = 286,	/* 1600x1200 (75 Hz) VESA timing (pixel clock is 189.2 Mhz dot clock). */
    kIOTimingIDVESA_1600x1200_80hz   = 288,	/* 1600x1200 (80 Hz) VESA timing (pixel clock is 216>? Mhz dot clock) - proposed only. */
    kIOTimingIDVESA_1600x1200_85hz   = 289,	/* 1600x1200 (85 Hz) VESA timing (pixel clock is 229.5 Mhz dot clock). */
    kIOTimingIDVESA_1792x1344_60hz   = 296,	/* 1792x1344 (60 Hz) VESA timing (204.75 Mhz dot clock). */
    kIOTimingIDVESA_1792x1344_75hz   = 298,	/* 1792x1344 (75 Hz) VESA timing (261.75 Mhz dot clock). */
    kIOTimingIDVESA_1856x1392_60hz   = 300,	/* 1856x1392 (60 Hz) VESA timing (218.25 Mhz dot clock). */
    kIOTimingIDVESA_1856x1392_75hz   = 302,	/* 1856x1392 (75 Hz) VESA timing (288 Mhz dot clock). */
    kIOTimingIDVESA_1920x1440_60hz   = 304,	/* 1920x1440 (60 Hz) VESA timing (234 Mhz dot clock). */
    kIOTimingIDVESA_1920x1440_75hz   = 306,	/* 1920x1440 (75 Hz) VESA timing (297 Mhz dot clock). */
    kIOTimingIDSMPTE240M_60hz        = 400,	/* 60Hz V, 33.75KHz H, interlaced timing, 16:9 aspect, typical resolution of 1920x1035. */
    kIOTimingIDFilmRate_48hz         = 410,	/* 48Hz V, 25.20KHz H, non-interlaced timing, typical resolution of 640x480. */
    kIOTimingIDSony_1600x1024_76hz   = 500,	/* 1600x1024 (76 Hz) Sony timing (pixel clock is 170.447 Mhz dot clock). */
    kIOTimingIDSony_1920x1080_60hz   = 510,	/* 1920x1080 (60 Hz) Sony timing (pixel clock is 159.84 Mhz dot clock). */
    kIOTimingIDSony_1920x1080_72hz   = 520,	/* 1920x1080 (72 Hz) Sony timing (pixel clock is 216.023 Mhz dot clock). */
    kIOTimingIDSony_1920x1200_76hz   = 540,	/* 1900x1200 (76 Hz) Sony timing (pixel clock is 243.20 Mhz dot clock). */
    kIOTimingIDApple_0x0_0hz_Offline = 550,	/* Indicates that this timing will take the display off-line and remove it from the system. */
    kIOTimingIDVESA_848x480_60hz     = 570,	/*  848x480 (60 Hz)  VESA timing. */
    kIOTimingIDVESA_1360x768_60hz    = 590	/* 1360x768 (60 Hz)  VESA timing. */
};

// framebuffer property keys

#define kIOFramebufferInfoKey		"IOFramebufferInformation"

#define kIOFBWidthKey			"IOFBWidth"
#define kIOFBHeightKey			"IOFBHeight"
#define kIOFBRefreshRateKey		"IOFBRefreshRate"
#define kIOFBFlagsKey			"IOFBFlags"
#define kIOFBBytesPerRowKey		"IOFBBytesPerRow"
#define kIOFBBytesPerPlaneKey		"IOFBBytesPerPlane"
#define kIOFBBitsPerPixelKey		"IOFBBitsPerPixel"
#define kIOFBComponentCountKey		"IOFBComponentCount"
#define kIOFBBitsPerComponentKey	"IOFBBitsPerComponent"

#define kIOFBDetailedTimingsKey		"IOFBDetailedTimings"
#define kIOFBTimingRangeKey		"IOFBTimingRange"
#define kIOFBScalerInfoKey		"IOFBScalerInfo"
#define kIOFBCursorInfoKey		"IOFBCursorInfo"

#define kIOFBHostAccessFlagsKey		"IOFBHostAccessFlags"

#define kIOFBMemorySizeKey		"IOFBMemorySize"

#define kIOFBProbeOptionsKey		"IOFBProbeOptions"

#define kIOFBGammaWidthKey		"IOFBGammaWidth"
#define kIOFBGammaCountKey		"IOFBGammaCount"
#define kIOFBCLUTDeferKey		"IOFBCLUTDefer"

// diagnostic keys

#define kIOFBConfigKey			"IOFBConfig"
#define kIOFBModesKey			"IOFBModes"
#define kIOFBModeIDKey			"ID"
#define kIOFBModeDMKey			"DM"
#define kIOFBModeTMKey			"TM"
#define kIOFBModeAIDKey			"AID"
#define kIOFBModeDFKey			"DF"

// display property keys

#define kIODisplayEDIDKey		"IODisplayEDID"
#define kIODisplayLocationKey		"IODisplayLocation"		// CFString
#define kIODisplayConnectFlagsKey	"IODisplayConnectFlags"		// CFNumber
#define kIODisplayHasBacklightKey	"IODisplayHasBacklight"		// CFBoolean
#define kIODisplayIsDigitalKey		"IODisplayIsDigital"		// CFBoolean
#define kDisplayBundleKey		"DisplayBundle"

#define kAppleDisplayTypeKey		"AppleDisplayType"
#define kAppleSenseKey			"AppleSense"


enum {
    kDisplayVendorIDUnknown	= 'unkn',
    kDisplayProductIDGeneric	= 0x717
};

#define kDisplayVendorID		"DisplayVendorID"	 // CFNumber
#define kDisplayProductID		"DisplayProductID"	 // CFNumber
#define kDisplaySerialNumber		"DisplaySerialNumber"	 // CFNumber
#define kDisplaySerialString		"DisplaySerialString"	 // CFString
#define kDisplayWeekOfManufacture	"DisplayWeekManufacture" // CFNumber
#define kDisplayYearOfManufacture	"DisplayYearManufacture" // CFNumber

// CFDictionary of language-locale keys, name values
// eg. "en"="Color LCD", "en-GB"="Colour LCD"
#define kDisplayProductName		"DisplayProductName"

// all CFNumber or CFArray of CFNumber (floats)
#define kDisplayWhitePointX		"DisplayWhitePointX"
#define kDisplayWhitePointY		"DisplayWhitePointY"
#define kDisplayRedPointX		"DisplayRedPointX"
#define kDisplayRedPointY		"DisplayRedPointY"
#define kDisplayGreenPointX		"DisplayGreenPointX"
#define kDisplayGreenPointY		"DisplayGreenPointY"
#define kDisplayBluePointX		"DisplayBluePointX"
#define kDisplayBluePointY		"DisplayBluePointY"
#define kDisplayWhiteGamma		"DisplayWhiteGamma"
#define kDisplayRedGamma		"DisplayRedGamma"
#define kDisplayGreenGamma		"DisplayGreenGamma"
#define kDisplayBlueGamma		"DisplayBlueGamma"

// Display gamma
#define kDisplayGammaChannels		"DisplayGammaChannels" 	  // CFNumber 1 or 3 channel count
#define kDisplayGammaEntryCount		"DisplayGammaEntryCount"  // CFNumber 1-based count of entries per channel
#define kDisplayGammaEntrySize		"DisplayGammaEntrySize"	  // CFNumber size in bytes of each table entry
#define kDisplayGammaTable		"DisplayGammaTable" 	  // CFData

// CFBoolean
#define kDisplayBrightnessAffectsGamma	"DisplayBrightnessAffectsGamma"
#define kDisplayViewAngleAffectsGamma	"DisplayViewAngleAffectsGamma"

// CFData
#define kDisplayCSProfile		"DisplayCSProfile"

// CFNumber
#define kDisplayHorizontalImageSize	"DisplayHorizontalImageSize"
#define kDisplayVerticalImageSize	"DisplayVerticalImageSize"

// Pixel description

// CFBoolean
#define kDisplayFixedPixelFormat	"DisplayFixedPixelFormat"

enum {
    kDisplaySubPixelLayoutUndefined	= 0x00000000,
    kDisplaySubPixelLayoutRGB		= 0x00000001,
    kDisplaySubPixelLayoutBGR		= 0x00000002,
    kDisplaySubPixelLayoutQuadGBL	= 0x00000003,
    kDisplaySubPixelLayoutQuadGBR	= 0x00000004,

    kDisplaySubPixelConfigurationUndefined    = 0x00000000,
    kDisplaySubPixelConfigurationDelta	      = 0x00000001,
    kDisplaySubPixelConfigurationStripe	      = 0x00000002,
    kDisplaySubPixelConfigurationStripeOffset = 0x00000003,
    kDisplaySubPixelConfigurationQuad	      = 0x00000004,

    kDisplaySubPixelShapeUndefined	= 0x00000000,
    kDisplaySubPixelShapeRound		= 0x00000001,
    kDisplaySubPixelShapeSquare		= 0x00000002,
    kDisplaySubPixelShapeRectangular	= 0x00000003,
    kDisplaySubPixelShapeOval		= 0x00000004,
    kDisplaySubPixelShapeElliptical	= 0x00000005
};

// CFNumbers
#define kDisplaySubPixelLayout		"DisplaySubPixelLayout"
#define kDisplaySubPixelConfiguration	"DisplaySubPixelConfiguration"
#define kDisplaySubPixelShape		"DisplaySubPixelShape"

// Display parameters

#define kIODisplayParametersKey		"IODisplayParameters"
#define kIODisplayGUIDKey		"IODisplayGUID"

#define kIODisplayValueKey		"value"
#define kIODisplayMinValueKey		"min"
#define kIODisplayMaxValueKey		"max"

#define kIODisplayBrightnessKey		"brightness"
#define kIODisplayContrastKey		"contrast"
#define kIODisplayHorizontalPositionKey	"horizontal-position"
#define kIODisplayHorizontalSizeKey	"horizontal-size"
#define kIODisplayVerticalPositionKey	"vertical-position"
#define kIODisplayVerticalSizeKey	"vertical-size"
#define kIODisplayTrapezoidKey		"trapezoid"
#define kIODisplayPincushionKey		"pincushion"
#define kIODisplayParallelogramKey	"parallelogram"
#define kIODisplayRotationKey		"rotation"
#define kIODisplayTheatreModeKey	"theatre-mode"
#define kIODisplayTheatreModeWindowKey	"theatre-mode-window"
#define kIODisplayOverscanKey		"oscn"
#define kIODisplayVideoBestKey		"vbst"

#define kIODisplayParametersCommitKey	"commit"
#define kIODisplayParametersDefaultKey	"defaults"

#ifdef __cplusplus
}
#endif

#endif /* ! _IOKIT_IOGRAPHICSTYPES_H */
