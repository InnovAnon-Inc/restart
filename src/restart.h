#ifndef _RESTART_H_
#define _RESTART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

#ifndef ETIME
#define ETIME ETIMEDOUT
#endif

struct timeval add2currenttime(double seconds)
__attribute__ ((nothrow, warn_unused_result)) ;
size_t copyfile(int fromfd, int tofd)
__attribute__ ((nothrow, warn_unused_result)) ;
int r_close(int fildes)
__attribute__ ((nothrow, warn_unused_result)) ;
int r_dup2(int fildes, int fildes2)
__attribute__ ((nothrow, warn_unused_result)) ;
int r_open2(const char *restrict path, int oflag)
__attribute__ ((nonnull (1), nothrow, warn_unused_result)) ;
int r_open3(const char *restrict path, int oflag, mode_t mode)
__attribute__ ((nonnull (1), nothrow, warn_unused_result)) ;
ssize_t r_read(int fd, void *restrict buf, size_t size)
__attribute__ ((nonnull (2), nothrow, warn_unused_result)) ;
pid_t r_wait(int *restrict stat_loc)
__attribute__ ((nonnull (1), nothrow, warn_unused_result)) ;
pid_t r_waitpid(pid_t pid, int *restrict stat_loc, int options)
__attribute__ ((nonnull (2), nothrow, warn_unused_result)) ;
ssize_t r_write(int fd, void *restrict buf, size_t size)
__attribute__ ((nonnull (2), nothrow, warn_unused_result)) ;
ssize_t readblock(int fd, void *restrict buf, size_t size)
__attribute__ ((nonnull (2), nothrow, warn_unused_result)) ;
ssize_t readline(int fd, char *restrict buf, size_t nbytes)
__attribute__ ((nonnull (2), nothrow, warn_unused_result)) ;
ssize_t readtimed(int fd, void *restrict buf, size_t nbyte, double seconds)
__attribute__ ((nonnull (2), nothrow, warn_unused_result)) ;
ssize_t readwrite(int fromfd, int tofd);
__attribute__ ((nothrow, warn_unused_result)) ;
ssize_t readwriteblock(int fromfd, int tofd, char *restrict buf, size_t size)
__attribute__ ((nonnull (3), nothrow, warn_unused_result));
int waitfdtimed(int fd, struct timeval end);
__attribute__ ((nothrow, warn_unused_result)) ;

#ifdef __cplusplus
}
#endif

#endif /* _RESTART_H_ */
