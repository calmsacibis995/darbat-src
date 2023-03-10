#include <libkern/c++/OSArray.h>
#include <libkern/c++/OSBoolean.h>
#include <libkern/c++/OSCollection.h>
#include <libkern/c++/OSCollectionIterator.h>
#include <libkern/c++/OSData.h>
#include <libkern/c++/OSDictionary.h>
#include <libkern/c++/OSNumber.h>
#include <libkern/c++/OSString.h>
#include <libkern/c++/OSSymbol.h>

#include <IOKit/IOLib.h>

void printPlist(OSObject * plist, UInt32 indent = 0) {
    const OSMetaClass * typeID;
    OSCollectionIterator * iterator;
    OSString * key;
    OSObject * value;
    unsigned int i;

    if (!plist) {
        IOLog("error! null plist\n");
        return;
    }

    typeID = OSTypeIDInst(plist);

    if (typeID ==  OSTypeID(OSDictionary)) {

        IOLog("{\n");
        OSDictionary * dict = OSDynamicCast(OSDictionary, plist);
        iterator = OSCollectionIterator::withCollection(dict);
        while ( (key = OSDynamicCast(OSString, iterator->getNextObject())) ) {
            for (i = 0; i < indent + 4; i++) {
                IOLog(" ");
            }
            IOLog("%s = ", key->getCStringNoCopy());
            value = dict->getObject(key);
            printPlist(value, indent + 4);
        }

        for (i = 0; i < indent; i++) {
            IOLog(" ");
        }
        IOLog("}\n");

    } else if (typeID == OSTypeID(OSArray)) {

        IOLog("{\n");

        OSArray * array = OSDynamicCast(OSArray, plist);
        iterator = OSCollectionIterator::withCollection(array);
        while ( (value = iterator->getNextObject()) ) {
            for (i = 0; i < indent + 4; i++) {
                IOLog(" ");
            }
            printPlist(value, indent + 4);
        }

        for (i = 0; i < indent; i++) {
            IOLog(" ");
        }
        IOLog("}\n");

    } else if (typeID == OSTypeID(OSString) || typeID == OSTypeID(OSSymbol)) {

        OSString * string = OSDynamicCast(OSString, plist);
        IOLog("\"%s\"\n", string->getCStringNoCopy());

    } else if (typeID == OSTypeID(OSNumber)) {

        OSNumber * number = OSDynamicCast(OSNumber, plist);
        UInt32 numberValue = number->unsigned32BitValue();
        IOLog("0x%lx (%ld base 10)\n", numberValue, numberValue);

    } else if (typeID == OSTypeID(OSBoolean)) {

        OSBoolean * boolObj = OSDynamicCast(OSBoolean, plist);
        IOLog("%s\n", boolObj->isTrue() ? "true" : "false");

    } else if (typeID == OSTypeID(OSData)) {

        IOLog("(binary data)\n");

    } else {

        IOLog("(object of class %s)\n", plist->getMetaClass()->getClassName());

    }

    return;
}

