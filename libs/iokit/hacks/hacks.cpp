/*
 * hacks.cpp
 *
 * Geoffrey Lee < glee at cse.unsw.edu.au >
 */

#include <libkern/c++/OSUnserialize.h>
#include <libkern/version.h>
#include <IOKit/IORegistryEntry.h>
#include <IOKit/IODeviceTreeSupport.h>
#include <IOKit/IOCatalogue.h>
#include <IOKit/IOUserClient.h>
#include <IOKit/IOMemoryDescriptor.h>
#include <IOKit/IOPlatformExpert.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOKitKeys.h>
#include <IOKit/IOKitDebug.h>

#include <l4/kip.h>
#include <l4/bootinfo.h>

extern "C" {

/*
 * initializePlatformExpert taken from IOStartIOKit.cpp
 */
void
initializePlatformExpert(void *p1, void *p2, void *p3, void *p4)
{
    IOPlatformExpertDevice *rootNub;

    rootNub = new IOPlatformExpertDevice;

    if( rootNub && rootNub->initWithArgs( p1, p2, p3, p4)) {
        rootNub->attach( 0 );

       /* Enter into the catalogue the drivers
        * provided by BootX.
        */
        gIOCatalogue->recordStartupExtensions();

        rootNub->registerService();
    }
}

/*
 * createDrvPd
 *
 * Create driver protection domain
 */
void
createDrvPd(const char *name)
{
	L4_KernelInterfacePage_t	*kip;
	void		*bootInfo;
	int		bootEntries, i;
	L4_BootRec_t	*rec;

	kip = L4_GetKernelInterface();
	bootInfo = (void *)L4_BootInfo(kip);
	assert(L4_BootInfo_Valid(bootInfo));

	bootEntries = L4_BootInfo_Entries(bootInfo);

	for (i = 0, rec = L4_BootInfo_FirstEntry(bootInfo); i < bootEntries;
	    i++, rec = L4_BootRec_Next(rec)) {

		;
	}
}

};	/* extern "C" */
