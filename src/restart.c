#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/wait.h>
#include "restart.h"
#define BLKSIZE PIPE_BUF
#define MILLION 1000000L
#define D_MILLION 1000000.0

/* Private functions */

__attribute__ ((nonnull (2), nothrow, warn_unused_result))
static int gettimeout(struct timeval end,
                               struct timeval *restrict timeoutp) {
   gettimeofday(timeoutp, NULL);
   timeoutp->tv_sec = end.tv_sec - timeoutp->tv_sec;
   timeoutp->tv_usec = end.tv_usec - timeoutp->tv_usec;
   if (timeoutp->tv_usec >= MILLION) {
      timeoutp->tv_sec++;
      timeoutp->tv_usec -= MILLION;
   }
   if (timeoutp->tv_usec < 0) {
      timeoutp->tv_sec--;
      timeoutp->tv_usec += MILLION;
   }
   error_check ((timeoutp->tv_sec < 0) ||
       ((timeoutp->tv_sec == 0) && (timeoutp->tv_usec == 0))) {
      errno = ETIME;
      return -1;
   }
   return 0;
}

/* Restart versions of traditional functions */

__attribute__ ((nothrow, warn_unused_result))
int r_close(int fildes) {
   int retval;
   do retval = close (fildes);
   while_echeck (retval == -1, EINTR) ;
   return retval;
}

__attribute__ ((nothrow, warn_unused_result))
int r_dup2(int fildes, int fildes2) {
   int retval;
   do retval = dup2 (fildes, fildes2);
   while_echeck (retval == -1, EINTR) ;
   return retval;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
int r_open2(const char *restrict path, int oflag) {
   int retval;
   do retval = open (path, oflag);
   while_echeck (retval == -1, EINTR) ;
   return retval;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
int r_open3(const char *restrict path, int oflag, mode_t mode) {
   int retval;
   do retval = open (path, oflag, mode);
   while_echeck (retval == -1, EINTR) ;
   return retval;
}

__attribute__ ((nonnull (2), nothrow, warn_unused_result))
ssize_t r_read(int fd, void *restrict buf, size_t size) {
   ssize_t retval;
   do retval = read(fd, buf, size);
   while_echeck (retval == -1, EINTR) ;
   return retval;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
pid_t r_wait(int *restrict stat_loc) {
   pid_t retval;
   do retval = wait (stat_loc);
   while_echeck (retval == -1, EINTR) ;
   return retval;
}

__attribute__ ((nonnull (2), nothrow, warn_unused_result))
pid_t r_waitpid(pid_t pid, int *restrict stat_loc, int options) {
   pid_t retval;
   do retval = waitpid (pid, stat_loc, options);
   while_echeck (retval == -1, EINTR) ;
   return retval;
}

__attribute__ ((nonnull (2), nothrow, warn_unused_result))
ssize_t r_write(int fd, void *restrict buf, size_t size) {
   char *restrict bufp;
   size_t bytestowrite;
   ssize_t byteswritten;
   size_t totalbytes;

   /* TODO verify that size <= SSIZE_MAX */

   for (bufp = buf, bytestowrite = size, totalbytes = 0;
        bytestowrite > 0;
        bufp += byteswritten, bytestowrite -= (size_t) byteswritten) {
      byteswritten = write(fd, bufp, bytestowrite);
      error_check ((byteswritten) == -1 && (errno != EINTR))
         return -1;
      error_check (byteswritten == -1) /* errno == EINTR */
         byteswritten = 0;
      totalbytes += (size_t) byteswritten;
   }
   return (ssize_t) totalbytes;
}

/* Utility functions */

__attribute__ ((nothrow, warn_unused_result))
struct timeval add2currenttime(double seconds) {
   struct timeval newtime;

   gettimeofday(&newtime, NULL);
   newtime.tv_sec += (int)seconds;
   newtime.tv_usec += (int)((seconds - (int)seconds)*D_MILLION + 0.5);
   if (newtime.tv_usec >= MILLION) {
      newtime.tv_sec++;
      newtime.tv_usec -= MILLION;
   }
   return newtime;
}

__attribute__ ((nothrow, warn_unused_result))
size_t copyfile(int fromfd, int tofd) {
   ssize_t bytesread;
   size_t totalbytes = 0;

   while ((bytesread = readwrite(fromfd, tofd)) > 0)
      totalbytes += (size_t) bytesread;
   return totalbytes;
}

__attribute__ ((nonnull (2), nothrow, warn_unused_result))
ssize_t readblock(int fd, void *restrict buf, size_t size) {
   char *restrict bufp;
   ssize_t bytesread;
   size_t bytestoread;
   size_t totalbytes;

   /* TODO verify that size <= SSIZE_MAX */

   for (bufp = buf, bytestoread = size, totalbytes = 0;
        bytestoread > 0;
        bufp += bytesread, bytestoread -= (size_t) bytesread) {
      bytesread = read(fd, bufp, bytestoread);
      if ((bytesread == 0) && (totalbytes == 0))
         return 0;
      error_check (bytesread == 0) {
         errno = EINVAL;
         return -1;
      }
      error_check ((bytesread) == -1 && (errno != EINTR))
         return -1;
      error_check (bytesread == -1) /* errno == EINTR */
         bytesread = 0;
      totalbytes += (size_t) bytesread;
   }
   return (ssize_t) totalbytes;
}

__attribute__ ((nonnull (2), nothrow, warn_unused_result))
ssize_t readline(int fd, char *restrict buf, size_t nbytes) {
   size_t numread = 0;
   ssize_t returnval;

   /* TODO verify that size <= SSIZE_MAX */

   while_expect (numread < nbytes - 1) { /* (see below) */
      returnval = read(fd, buf + numread, (size_t) 1);
      error_check ((returnval == -1) && (errno == EINTR))
         continue;
      if ((returnval == 0) && (numread == 0))
         return 0;
      if (returnval == 0)
         break;
      error_check (returnval == -1)
         return -1;
      numread++;
      if (buf[numread-1] == '\n') {
         buf[numread] = '\0';
         return (ssize_t) numread;
      }
   } /* expect true, because exiting loop like that is error-case */
   errno = EINVAL;
   return -1;
}

__attribute__ ((nonnull (2), nothrow, warn_unused_result))
ssize_t readtimed(int fd, void *restrict buf, size_t nbyte, double seconds) {
   struct timeval timedone;

   timedone = add2currenttime(seconds);
   error_check (waitfdtimed(fd, timedone) == -1)
      return (ssize_t)(-1);
   return r_read(fd, buf, nbyte);
}

__attribute__ ((nothrow, warn_unused_result))
ssize_t readwrite(int fromfd, int tofd) {
   char buf[BLKSIZE];
   ssize_t bytesread;

   error_check ((bytesread = r_read(fromfd, buf, (size_t) BLKSIZE)) < 0)
      return -1;
   if (bytesread == 0)
      return 0;
   error_check (r_write(tofd, buf, (size_t) bytesread) < 0)
      return -1;
   return bytesread;
}

__attribute__ ((nonnull (3), nothrow, warn_unused_result))
ssize_t readwriteblock(int fromfd, int tofd, char *restrict buf, size_t size) {
   ssize_t bytesread;

   bytesread = readblock(fromfd, buf, size);
   error_check (bytesread != (ssize_t) size)         /* can only be 0 or -1 */
      return bytesread;
   return r_write(tofd, buf, size);
}

__attribute__ ((nothrow, warn_unused_result))
int waitfdtimed(int fd, struct timeval end) {
   fd_set readset;
   int retval;
   struct timeval timeout;

   error_check ((fd < 0) || (fd >= FD_SETSIZE)) {
      errno = EINVAL;
      return -1;
   }
   FD_ZERO(&readset);
   FD_SET(fd, &readset);
   error_check (gettimeout(end, &timeout) == -1)
      return -1;
   while_echeck (
      (retval = select(fd+1, &readset, NULL, NULL, &timeout)) == -1,
      EINTR) {
      error_check (gettimeout(end, &timeout) == -1)
         return -1;
      FD_ZERO(&readset);
      FD_SET(fd, &readset);
   }
   error_check (retval == 0) {
      errno = ETIME;
      return -1;
   }
   error_check (retval == -1)
      return -1;
   return 0;
}
