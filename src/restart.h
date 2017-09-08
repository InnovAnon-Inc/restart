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

struct timeval add2currenttime(double seconds);
size_t copyfile(int fromfd, int tofd);
int r_close(int fildes);
int r_dup2(int fildes, int fildes2);
int r_open2(const char *path, int oflag);
int r_open3(const char *path, int oflag, mode_t mode);
ssize_t r_read(int fd, void *buf, size_t size);
pid_t r_wait(int *stat_loc);
pid_t r_waitpid(pid_t pid, int *stat_loc, int options);
ssize_t r_write(int fd, void *buf, size_t size);
ssize_t readblock(int fd, void *buf, size_t size);
ssize_t readline(int fd, char *buf, size_t nbytes);
ssize_t readtimed(int fd, void *buf, size_t nbyte, double seconds);
ssize_t readwrite(int fromfd, int tofd);
ssize_t readwriteblock(int fromfd, int tofd, char *buf, size_t size);
int waitfdtimed(int fd, struct timeval end);

#ifdef __cplusplus
}
#endif

#endif /* _RESTART_H_ */
