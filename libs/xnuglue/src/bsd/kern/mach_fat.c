/*
 * mach_fat.c
 *
 * Geoffrey Lee < glee at cse unsw edu au > 
 */

struct vnode { int dummy ; };

#include <vm/vm_kern.h>
#include <mach/kern_return.h>
#include <mach/vm_param.h>

#include <mach-o/fat.h>
#include <kern/mach_loader.h>
#include <architecture/byte_order.h>

#define CPU_TYPE_NATIVE         (cpu_type())
#define CPU_TYPE_CLASSIC        CPU_TYPE_POWERPC 

/* XXX should be in common header */
extern int grade_binary(cpu_type_t exectype, cpu_subtype_t execsubtype);



static load_return_t
fatfile_getarch2(
#if 0
        struct vnode    *vp,
#else
        __unused struct vnode   *vp,
#endif
        vm_offset_t     data_ptr,
        cpu_type_t      req_cpu_type,
        cpu_type_t      mask_bits,
        struct fat_arch *archret)
{
        /* vm_pager_t           pager; */
        vm_offset_t             addr;
        vm_size_t               size;
        load_return_t           lret;
        struct fat_arch         *arch;
        struct fat_arch         *best_arch;
        int                     grade;
        int                     best_grade;
        int                     nfat_arch;
        int                     end_of_archs;
        struct fat_header       *header;
#if 0
        off_t filesize;
#endif

        /*
         *      Get the pager for the file.
         */

        header = (struct fat_header *)data_ptr;

        /*
         *      Map portion that must be accessible directly into
         *      kernel's map.
         */
        nfat_arch = NXSwapBigLongToHost(header->nfat_arch);

        end_of_archs = sizeof(struct fat_header)
                + nfat_arch * sizeof(struct fat_arch);
#if 0
        filesize = ubc_getsize(vp);
        if (end_of_archs > (int)filesize) {
                return(LOAD_BADMACHO);
        }
#endif

        /* This is beacuse we are reading only 512 bytes */

        if (end_of_archs > 512)
                return(LOAD_BADMACHO);
        /*
         *      Round size of fat_arch structures up to page boundry.
         */
        size = round_page_32(end_of_archs);
        if (size == 0)
                return(LOAD_BADMACHO);

        /*
         * Scan the fat_arch's looking for the best one.
         */
        addr = data_ptr;
        best_arch = NULL;
        best_grade = 0;
        arch = (struct fat_arch *) (addr + sizeof(struct fat_header));
        for (; nfat_arch-- > 0; arch++) {

                /*
                 *      Check to see if right cpu type.
                 */
                if(((cpu_type_t)NXSwapBigIntToHost(arch->cputype) & ~mask_bits) != req_cpu_type)
                        continue;

                /*
                 *      Get the grade of the cpu subtype.
                 */
                grade = grade_binary(
                            NXSwapBigIntToHost(arch->cputype),
                            NXSwapBigIntToHost(arch->cpusubtype));


                /*
                 *      Remember it if it's the best we've seen.
                 */
                if (grade > best_grade) {
                        best_grade = grade;
                        best_arch = arch;
                }
        }


        /*
         *      Return our results.
         */
        if (best_arch == NULL) {
                lret = LOAD_BADARCH;
        } else {
                archret->cputype        =
                            NXSwapBigIntToHost(best_arch->cputype);
                archret->cpusubtype     =
                            NXSwapBigIntToHost(best_arch->cpusubtype);
                archret->offset         =
                            NXSwapBigLongToHost(best_arch->offset);
                archret->size           =
                            NXSwapBigLongToHost(best_arch->size);
                archret->align          =
                            NXSwapBigLongToHost(best_arch->align);

                lret = LOAD_SUCCESS;
        }

        /*
         * Free the memory we allocated and return.
         */
        return(lret);
}

load_return_t
fatfile_getarch(
        struct vnode            *vp,
        vm_offset_t     data_ptr,
        struct fat_arch         *archret)
{
        return fatfile_getarch2(vp, data_ptr, CPU_TYPE_NATIVE, 0, archret);
}

