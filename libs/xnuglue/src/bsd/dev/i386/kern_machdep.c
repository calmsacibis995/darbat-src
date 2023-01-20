#include        <sys/types.h>
#include        <mach/machine.h>
//#include        <kern/cpu_number.h>

extern int grade_binary(cpu_type_t exectype, cpu_subtype_t execsubtype);


int
grade_binary(__unused cpu_type_t exectype, cpu_subtype_t execsubtype)
{
        int             cpusubtype = cpu_subtype();

        switch (cpusubtype) {
            case CPU_SUBTYPE_386:
                switch (execsubtype) {
                    case CPU_SUBTYPE_386:
                        return 1;
                    default:
                        return 0;
                }

            case CPU_SUBTYPE_486:
                switch (execsubtype) {
                    case CPU_SUBTYPE_386:
                        return 1;

                    case CPU_SUBTYPE_486SX:

                        return 2;

                    case CPU_SUBTYPE_486:
                        return 3;

                    default:
                        return 0;
                }

            case CPU_SUBTYPE_486SX:
                switch (execsubtype) {
                    case CPU_SUBTYPE_386:
                        return 1;

                    case CPU_SUBTYPE_486:
                        return 2;

                    case CPU_SUBTYPE_486SX:
                        return 3;

                    default:
                        return 0;
                }

            case CPU_SUBTYPE_586:
                switch (execsubtype) {
                    case CPU_SUBTYPE_386:
                        return 1;

                    case CPU_SUBTYPE_486SX:
                        return 2;

                    case CPU_SUBTYPE_486:
                        return 3;

                    case CPU_SUBTYPE_586:
                        return 4;

                    default:
                        return 0;
                }

            default:
                if (    CPU_SUBTYPE_INTEL_MODEL(execsubtype) ==
                        CPU_SUBTYPE_INTEL_MODEL_ALL) {
                    if (        CPU_SUBTYPE_INTEL_FAMILY(cpusubtype) >=
                                CPU_SUBTYPE_INTEL_FAMILY(execsubtype))
                        return CPU_SUBTYPE_INTEL_FAMILY_MAX -
                            CPU_SUBTYPE_INTEL_FAMILY(cpusubtype) -
                            CPU_SUBTYPE_INTEL_FAMILY(execsubtype);
                }
                else {
                    if (        cpusubtype == execsubtype)
                        return CPU_SUBTYPE_INTEL_FAMILY_MAX + 1;
                }
                return 0;
        }
}
