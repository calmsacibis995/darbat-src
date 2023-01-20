#include <stdlib.h>
/* this program is used to test whether mtools drops its privileges correctly */

main(int argc, char **argv)
{
  setuid(strtoul(argv[1], 0,0));
  system("id");

}
