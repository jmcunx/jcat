## jcat - slow down scrolling

This is a little utility will allow you to
slowdown scrolling of file or stream.
Useful if you do not want to pipe information
through more(1), less(1) or pg(1).

[j\_lib2](https://github.com/jmcunx/j_lib2) is an **optional** dependency.

[GNU automake](https://en.wikipedia.org/wiki/Automake)
only confuses me, but this seems to be good enough for me.

**To compile:**
* If "DESTDIR" is not set, will install under /usr/local
* Execute ./build.sh to create a Makefile
* Works on Linux, BSD and AIX

_To uninstall_, execute
"make uninstall"
from the source directory

This is licensed using
[ISC Licence](https://en.wikipedia.org/wiki/ISC_license).
