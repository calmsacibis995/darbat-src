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

#ifndef _IOKIT_IODISPLAY_H
#define _IOKIT_IODISPLAY_H

#include <IOKit/IOService.h>
#include <IOKit/graphics/IOFramebuffer.h>

extern const OSSymbol *	gIODisplayParametersKey;
extern const OSSymbol *	gIODisplayGUIDKey;

extern const OSSymbol *	gIODisplayValueKey;
extern const OSSymbol *	gIODisplayMinValueKey;
extern const OSSymbol *	gIODisplayMaxValueKey;

extern const OSSymbol *	gIODisplayContrastKey;
extern const OSSymbol *	gIODisplayBrightnessKey;
extern const OSSymbol *	gIODisplayHorizontalPositionKey;
extern const OSSymbol * gIODisplayHorizontalSizeKey;
extern const OSSymbol *	gIODisplayVerticalPositionKey;
extern const OSSymbol *	gIODisplayVerticalSizeKey;
extern const OSSymbol *	gIODisplayTrapezoidKey;
extern const OSSymbol *	gIODisplayPincushionKey;
extern const OSSymbol *	gIODisplayParallelogramKey;
extern const OSSymbol *	gIODisplayRotationKey;
extern const OSSymbol * gIODisplayOverscanKey;
extern const OSSymbol * gIODisplayVideoBestKey;

extern const OSSymbol * gIODisplayParametersTheatreModeKey;
extern const OSSymbol * gIODisplayParametersTheatreModeWindowKey;

extern const OSSymbol *	gIODisplayParametersCommitKey;
extern const OSSymbol *	gIODisplayParametersDefaultKey;

enum {
    kIODisplayNumPowerStates = 4,
    kIODisplayMaxPowerState  = kIODisplayNumPowerStates - 1
};

// these are the private instance variables for power management
struct DisplayPMVars
{
    UInt32		currentState;
    // highest state number normally, lowest usable state in emergency
    unsigned long	maxState;
    // true if the display has had power lowered due to user inactivity
    bool 		displayIdle;
};

class IODisplayConnect : public IOService
{
    OSDeclareDefaultStructors(IODisplayConnect)

private:
    IOIndex	connection;

protected:
/*! @struct ExpansionData
    @discussion This structure will be used to expand the capablilties of this class in the future.
    */    
    struct ExpansionData { };

/*! @var reserved
    Reserved for future use.  (Internal use only)  */
    ExpansionData * reserved;

public:
    virtual bool initWithConnection( IOIndex connection );
    virtual IOFramebuffer * getFramebuffer( void );
    virtual IOIndex getConnection( void );
    virtual IOReturn getAttributeForConnection( IOSelect selector, UInt32 * value );
    virtual IOReturn setAttributeForConnection( IOSelect selector, UInt32 value );
    virtual void joinPMtree ( IOService * driver );
};

class IODisplay : public IOService
{
    OSDeclareAbstractStructors(IODisplay)

public:
    static void initialize( void );

protected:
    // used to query the framebuffer controller
    IODisplayConnect *			fConnection;
    class IODisplayParameterHandler *	fParameterHandler;
    OSDictionary *  			fDisplayParams;
    IONotifier *			fNotifier;

    // pointer to protected instance variables for power management
    struct DisplayPMVars *		fDisplayPMVars;

    // reserved for future expansion
    void * 				_IODisplay_reserved[32];

public:
    virtual IOService * probe(	IOService * 	provider,
				SInt32 *	score );

    virtual bool start( IOService * provider );
    virtual void stop( IOService * provider );
    virtual void free();

    virtual IODisplayConnect * getConnection( void );

    virtual IOReturn getConnectFlagsForDisplayMode(
		IODisplayModeID mode, UInt32 * flags );

    virtual IOReturn getGammaTableByIndex(
	UInt32 * channelCount, UInt32 * dataCount,
    	UInt32 * dataWidth, void ** data );

    virtual IOReturn readFramebufferEDID( void );

    // 
    virtual IOReturn framebufferEvent( IOFramebuffer * framebuffer, 
                                        IOIndex event, void * info );

    // parameter setting
    virtual IOReturn setProperties( OSObject * properties );
    virtual bool setForKey( OSDictionary * params, const OSSymbol * key,
                            SInt32 value, SInt32 min, SInt32 max );

    static bool addParameter( OSDictionary * params, const OSSymbol * paramName, SInt32 min, SInt32 max );
    static bool setParameter( OSDictionary * params, const OSSymbol * paramName, SInt32 value );
    static OSDictionary * getIntegerRange( OSDictionary * params, const OSSymbol * sym,
                                      SInt32 * value, SInt32 * min, SInt32 * max );

    // low level set/get
    virtual bool doIntegerSet( OSDictionary * params,
                               const OSSymbol * paramName, UInt32 value );
    virtual bool doDataSet( const OSSymbol * paramName, OSData * value );
    virtual bool doUpdate( void );

    // power management methods
    virtual IOReturn setAggressiveness( unsigned long, unsigned long newLevel );
    virtual IOReturn setPowerState( unsigned long, IOService * );
    virtual unsigned long maxCapabilityForDomainState( IOPMPowerFlags );
    virtual unsigned long initialPowerStateForDomainState( IOPMPowerFlags );
    virtual unsigned long powerStateForDomainState( IOPMPowerFlags );

    // 
    virtual void initPowerManagement( IOService * provider);
    virtual void dropOneLevel( void );
    virtual void makeDisplayUsable( void );

private:
    OSMetaClassDeclareReservedUnused(IODisplay, 0);
    OSMetaClassDeclareReservedUnused(IODisplay, 1);
    OSMetaClassDeclareReservedUnused(IODisplay, 2);
    OSMetaClassDeclareReservedUnused(IODisplay, 3);
    OSMetaClassDeclareReservedUnused(IODisplay, 4);
    OSMetaClassDeclareReservedUnused(IODisplay, 5);
    OSMetaClassDeclareReservedUnused(IODisplay, 6);
    OSMetaClassDeclareReservedUnused(IODisplay, 7);
    OSMetaClassDeclareReservedUnused(IODisplay, 8);
    OSMetaClassDeclareReservedUnused(IODisplay, 9);
    OSMetaClassDeclareReservedUnused(IODisplay, 10);
    OSMetaClassDeclareReservedUnused(IODisplay, 11);
    OSMetaClassDeclareReservedUnused(IODisplay, 12);
    OSMetaClassDeclareReservedUnused(IODisplay, 13);
    OSMetaClassDeclareReservedUnused(IODisplay, 14);
    OSMetaClassDeclareReservedUnused(IODisplay, 15);
    OSMetaClassDeclareReservedUnused(IODisplay, 16);
    OSMetaClassDeclareReservedUnused(IODisplay, 17);
    OSMetaClassDeclareReservedUnused(IODisplay, 18);
    OSMetaClassDeclareReservedUnused(IODisplay, 19);

private:
    static IOReturn _framebufferEvent( OSObject * self, void * ref,
                    IOFramebuffer *framebuffer, IOIndex event, void * info );

    bool addParameterHandler( IODisplayParameterHandler * parameterHandler );
    bool removeParameterHandler( IODisplayParameterHandler * parameterHandler );
    static bool updateNumber( OSDictionary * params, const OSSymbol * key, SInt32 value );
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class IOBacklightDisplay : public IODisplay
{
    OSDeclareDefaultStructors(IOBacklightDisplay)

protected:
    // User preferred brightness level
    SInt32	fCurrentUserBrightness;
    SInt32	fCurrentBrightness;
    UInt32	fCurrentPowerState;
    SInt32	fMinBrightness;
    SInt32	fMaxBrightness;
    UInt8	fMaxBrightnessLevel[kIODisplayNumPowerStates];

public:
    virtual IOService * probe( IOService *, SInt32 * );
    virtual void stop( IOService * provider );
    virtual IOReturn setPowerState( unsigned long, IOService * );
    virtual unsigned long maxCapabilityForDomainState( IOPMPowerFlags );
    virtual unsigned long initialPowerStateForDomainState( IOPMPowerFlags );
    virtual unsigned long powerStateForDomainState( IOPMPowerFlags );
    virtual IOReturn setAggressiveness( unsigned long type, unsigned long newLevel );
    virtual IOReturn getAggressiveness( unsigned long type, unsigned long * currentLevel );

    // 
    virtual void initPowerManagement( IOService * );

public:
    virtual bool doIntegerSet( OSDictionary * params,
                               const OSSymbol * paramName, UInt32 value );
    virtual bool setBrightness( SInt32 value );

private:
    OSMetaClassDeclareReservedUnused(IOBacklightDisplay, 0);
    OSMetaClassDeclareReservedUnused(IOBacklightDisplay, 1);
    OSMetaClassDeclareReservedUnused(IOBacklightDisplay, 2);
    OSMetaClassDeclareReservedUnused(IOBacklightDisplay, 3);
    OSMetaClassDeclareReservedUnused(IOBacklightDisplay, 4);
    OSMetaClassDeclareReservedUnused(IOBacklightDisplay, 5);
    OSMetaClassDeclareReservedUnused(IOBacklightDisplay, 6);
    OSMetaClassDeclareReservedUnused(IOBacklightDisplay, 7);
    OSMetaClassDeclareReservedUnused(IOBacklightDisplay, 8);
    OSMetaClassDeclareReservedUnused(IOBacklightDisplay, 9);
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class IODisplayParameterHandler : public IOService
{
    OSDeclareDefaultStructors(IODisplayParameterHandler)

public:
    virtual bool setDisplay( IODisplay * display ) = 0;
    virtual bool doIntegerSet( OSDictionary * params,
                               const OSSymbol * paramName, UInt32 value ) = 0;
    virtual bool doDataSet( const OSSymbol * paramName, OSData * value ) = 0;
    virtual bool doUpdate( void ) = 0;

private:
    OSMetaClassDeclareReservedUnused(IODisplayParameterHandler, 0);
    OSMetaClassDeclareReservedUnused(IODisplayParameterHandler, 1);
    OSMetaClassDeclareReservedUnused(IODisplayParameterHandler, 2);
    OSMetaClassDeclareReservedUnused(IODisplayParameterHandler, 3);
    OSMetaClassDeclareReservedUnused(IODisplayParameterHandler, 4);
    OSMetaClassDeclareReservedUnused(IODisplayParameterHandler, 5);
    OSMetaClassDeclareReservedUnused(IODisplayParameterHandler, 6);
    OSMetaClassDeclareReservedUnused(IODisplayParameterHandler, 7);
    OSMetaClassDeclareReservedUnused(IODisplayParameterHandler, 8);
    OSMetaClassDeclareReservedUnused(IODisplayParameterHandler, 9);
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#endif /* ! _IOKIT_IODISPLAY_H */

