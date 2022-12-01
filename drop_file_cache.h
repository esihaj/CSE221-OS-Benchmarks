#ifndef _DROP_FILE_CACHE_H
#define _DROP_FILE_CACHE_H

#include <cstdlib>

#if __APPLE__
    void drop_file_cache() {
        system("sudo purge");
    }
#else
    void drop_file_cache() {
        system("sudo echo 3 > /proc/sys/vm/drop_caches");
    }
#endif

#endif