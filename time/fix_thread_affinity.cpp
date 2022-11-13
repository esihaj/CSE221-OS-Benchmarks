#include <sched.h>
#include <pthread.h>

/**
 * pin the current thread 
 */
void fix() {
    cpu_set_t   *cpuset( nullptr );
    size_t cpu_allocate_size( -1 );
#if   (__GLIBC_MINOR__ > 9 ) && (__GLIBC__ == 2 )
    const int8_t   processors_to_allocate( 1 );
    cpuset = CPU_ALLOC( processors_to_allocate );
    assert( cpuset != nullptr );
    cpu_allocate_size = CPU_ALLOC_SIZE( processors_to_allocate );
    CPU_ZERO_S( cpu_allocate_size, cpuset );
#else
    cpu_allocate_size = sizeof( cpu_set_t );
    cpuset = (cpu_set_t*) malloc( cpu_allocate_size );
    assert( cpuset != nullptr );
    CPU_ZERO( cpuset );
#endif
    CPU_SET( d->core,
                cpuset );
    errno = 0;
    if( sched_setaffinity( 0 /* calling thread */,
                            cpu_allocate_size,
                            cpuset ) != 0 )
    {
        perror( "Failed to set affinity for cycle counter!!" );
        exit( EXIT_FAILURE );
    }
    /** wait till we know we're on the right processor **/
    pthread_yield();
}