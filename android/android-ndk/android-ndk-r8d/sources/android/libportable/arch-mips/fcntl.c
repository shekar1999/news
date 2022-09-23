/*
 * Copyright 2012, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl_portable.h>

#include <portability.h>

#if F_GETLK_PORTABLE==F_GETLK
#error Bad build environment
#endif

#define PORTABLE_TAG "fcntl_portable"
#include <log_portable.h>

static char *map_portable_cmd_to_name(int cmd)
{
    char *name;

    switch(cmd) {
    case F_DUPFD_PORTABLE:              name = "F_DUPFD_PORTABLE";              break;  /* 0 */
    case F_GETFD_PORTABLE:              name = "F_GETFD_PORTABLE";              break;  /* 1 */
    case F_SETFD_PORTABLE:              name = "F_SETFD_PORTABLE";              break;  /* 2 */
    case F_GETFL_PORTABLE:              name = "F_GETFL_PORTABLE";              break;  /* 3 */
    case F_SETFL_PORTABLE:              name = "F_SETFL_PORTABLE";              break;  /* 4 */
    case F_GETLK_PORTABLE:              name = "F_GETLK_PORTABLE";              break;  /* 5 */
    case F_SETLK_PORTABLE:              name = "F_SETLK_PORTABLE";              break;  /* 6 */
    case F_SETLKW_PORTABLE:             name = "F_SETLKW_PORTABLE";             break;  /* 7 */
    case F_SETOWN_PORTABLE:             name = "F_SETOWN_PORTABLE";             break;  /* 8 */
    case F_GETOWN_PORTABLE:             name = "F_GETOWN_PORTABLE";             break;  /* 9 */
    case F_SETSIG_PORTABLE:             name = "F_SETSIG_PORTABLE";             break;  /* 10 */
    case F_GETSIG_PORTABLE:             name = "F_GETSIG_PORTABLE";             break;  /* 11 */
    case F_GETLK64_PORTABLE:            name = "F_GETLK64_PORTABLE";            break;  /* 12 */
    case F_SETLK64_PORTABLE:            name = "F_SETLK64_PORTABLE";            break;  /* 13 */
    case F_SETLKW64_PORTABLE:           name = "F_SETLKW64_PORTABLE";           break;  /* 14 */
    case F_SETLEASE_PORTABLE:           name = "F_SETLEASE_PORTABLE";           break;  /* 1024 */
    case F_GETLEASE_PORTABLE:           name = "F_GETLEASE_PORTABLE";           break;  /* 1025 */
    case F_NOTIFY_PORTABLE:             name = "F_NOTIFY_PORTABLE";             break;  /* 1026 */
    case F_CANCELLK_PORTABLE:           name = "F_CANCELLK_PORTABLE";           break;  /* 1029 */
    case F_DUPFD_CLOEXEC_PORTABLE:      name = "F_DUPFD_CLOEXEC_PORTABLE";      break;  /* 1030 */
    default:                            name = "<UNKNOWN>";                     break;
    }
    return(name);
}

static int mips_change_cmd(int cmd)
{
    switch(cmd) {
    case F_DUPFD_PORTABLE:      /* 0 --> 0 */
        return F_DUPFD;
    case F_GETFD_PORTABLE:      /* 1 --> 1 */
        return F_GETFD;
    case F_SETFD_PORTABLE:      /* 2 --> 2 */
        return F_SETFD;
    case F_GETFL_PORTABLE:      /* 3 --> 3 */
        return F_GETFL;
    case F_SETFL_PORTABLE:      /* 4 --> 4 */
        return F_SETFL;
    case F_GETLK_PORTABLE:      /* 5 --> 14 */
        return F_GETLK;
    case F_SETLK_PORTABLE:      /* 6 --> 6 */
        return F_SETLK;
    case F_SETLKW_PORTABLE:     /* 7 --> 7 */
        return F_SETLKW;
    case F_SETOWN_PORTABLE:     /* 8 --> 24 */
        return F_SETOWN;
    case F_GETOWN_PORTABLE:     /* 9 --> 23 */
        return F_GETOWN;
    case F_SETSIG_PORTABLE:     /* 10 --> 10 */
        return F_SETSIG;
    case F_GETSIG_PORTABLE:     /* 11 --> 11 */
        return F_GETSIG;
    case F_GETLK64_PORTABLE:    /* 12 --> 33 */
        return F_GETLK64;
    case F_SETLK64_PORTABLE:    /* 13 --> 34 */
        return F_SETLK64;
    case F_SETLKW64_PORTABLE:   /* 14 --> 35 */
        return F_SETLKW64;
    case F_SETLEASE_PORTABLE:   /* 1024 --> 1024 */
        return F_SETLEASE;
    case F_GETLEASE_PORTABLE:   /* 1025 --> 1025 */
        return F_GETLEASE;
    case F_NOTIFY_PORTABLE:      /* 1026 --> 1026 */
        return F_NOTIFY;
    case F_CANCELLK_PORTABLE:      /* 1029 --> void */
        ALOGE("%s: case F_CANCELLK_PORTABLE: Not likely supported by MIPS.", __func__);
        return(cmd);
    case F_DUPFD_CLOEXEC_PORTABLE: /* 1030 --> VOID */
        ALOGE("%s: case F_DUPFD_CLOEXEC_PORTABLE: Not likely supported by MIPS.", __func__);
        return(cmd);
    default:
        ALOGE("%s: cmd:%d Not Supported", __func__, cmd);
        /* Fall thru and default to the command being the same */
    }
    return(cmd);
}

static int mips_change_flags(int flags)
{
    int mipsflags = flags & O_ACCMODE_PORTABLE;

    if (flags & O_CREAT_PORTABLE)
        mipsflags |= O_CREAT;
    if (flags & O_EXCL_PORTABLE)
        mipsflags |= O_EXCL;
    if (flags & O_NOCTTY_PORTABLE)
        mipsflags |= O_NOCTTY;
    if (flags & O_TRUNC_PORTABLE)
        mipsflags |= O_TRUNC;
    if (flags & O_APPEND_PORTABLE)
        mipsflags |= O_APPEND;
    if (flags & O_NONBLOCK_PORTABLE)
        mipsflags |= O_NONBLOCK;
    if (flags & O_SYNC_PORTABLE)
        mipsflags |= O_SYNC;
    if (flags & FASYNC_PORTABLE)
        mipsflags |= FASYNC;
    if (flags & O_DIRECT_PORTABLE)
        mipsflags |= O_DIRECT;
    if (flags & O_LARGEFILE_PORTABLE)
        mipsflags |= O_LARGEFILE;
    if (flags & O_DIRECTORY_PORTABLE)
        mipsflags |= O_DIRECTORY;
    if (flags & O_NOFOLLOW_PORTABLE)
        mipsflags |= O_NOFOLLOW;
    if (flags & O_NOATIME_PORTABLE)
        mipsflags |= O_NOATIME;
    if (flags & O_NDELAY_PORTABLE)
        mipsflags |= O_NDELAY;

    return mipsflags;
}

static int portable_change_flags(int flags)
{
    int portableflags = flags & O_ACCMODE_PORTABLE;
    if (flags & O_CREAT)
        portableflags |= O_CREAT_PORTABLE;
    if (flags & O_EXCL)
        portableflags |= O_EXCL_PORTABLE;
    if (flags & O_NOCTTY)
        portableflags |= O_NOCTTY_PORTABLE;
    if (flags & O_TRUNC)
        portableflags |= O_TRUNC_PORTABLE;
    if (flags & O_APPEND)
        portableflags |= O_APPEND_PORTABLE;
    if (flags & O_NONBLOCK)
        portableflags |= O_NONBLOCK_PORTABLE;
    if (flags & O_SYNC)
        portableflags |= O_SYNC_PORTABLE;
    if (flags & FASYNC)
        portableflags |= FASYNC_PORTABLE;
    if (flags & O_DIRECT)
        portableflags |= O_DIRECT_PORTABLE;
    if (flags & O_LARGEFILE)
        portableflags |= O_LARGEFILE_PORTABLE;
    if (flags & O_DIRECTORY)
        portableflags |= O_DIRECTORY_PORTABLE;
    if (flags & O_NOFOLLOW)
        portableflags |= O_NOFOLLOW_PORTABLE;
    if (flags & O_NOATIME)
        portableflags |= O_NOATIME_PORTABLE;
    if (flags & O_NDELAY)
        portableflags |= O_NDELAY_PORTABLE;

    return portableflags;
}

extern int __fcntl64(int, int, void *);

/*
 * For 32 bit flocks we are converting a portable/AMR struct flock to a MIPS struct flock:
 *
 * MIPS:                        ARM:
 *     struct flock {           struct flock_portable {
 *       short l_type;            short l_type;
 *
 *       short l_whence;          short l_whence;
 *       off_t l_start;           loff_t l_start;
 *       off_t l_len;             loff_t l_len;
 *       long l_sysid;
 *
 *       __kernel_pid_t l_pid;    pid_t l_pid;
 *       long pad[4];
 *     };                       }
 *
 * which have identically sized structure members:
 *
 * For a 64 bit flocks we only have to deal with
 * a four byte padding in the ARM/Portable structure:
 *
 *    MIPS:                     ARM:
 *        struct flock64 {      struct flock64_portable {
 *        short l_type;           short l_type;
 *        short l_whence;         short l_whence;
 *                                unsigned char __padding[4];   <----  NOTE
 *        loff_t l_start;         loff_t l_start;
 *        loff_t l_len;           loff_t l_len;
 *        pid_t l_pid;            pid_t l_pid;
 *      }                       }
 */

int fcntl_portable(int fd, int portable_cmd, ...)
{
    va_list ap;
    void * arg;
    int flags;
    int result = 0;
    struct flock flock;                                 /* Native MIPS structure */
    struct flock64 flock64;                             /* Native MIPS structure */
    int mips_cmd = mips_change_cmd(portable_cmd);
    char *portable_cmd_name = map_portable_cmd_to_name(portable_cmd);
    struct flock_portable *flock_portable = NULL;
    struct flock64_portable *flock64_portable = NULL;

    ALOGV(" ");
    ALOGV("%s(fd:%d, portable_cmd:%d:'%s', ...): MAPPED mips_cmd = %d",  __func__,
              fd,    portable_cmd,
                     portable_cmd_name,                 mips_cmd);

    va_start(ap, portable_cmd);
    arg = va_arg(ap, void *);
    va_end(ap);

    switch(mips_cmd) {
    case F_GETLK:
    case F_SETLK:
    case F_SETLKW:
        flock_portable = (struct flock_portable *) arg;

        if (invalid_pointer(flock_portable)) {
            ALOGE("%s: flock_portable:%p == {NULL||-1}", __func__, flock_portable);
            errno = EFAULT;
            result = -1;
            goto done;
        }

        /*
         * Lock type and Whence are the same for all ARCHs
         *      (F_RDLCK:0,   F_WRLCK:1,  F_UNLCK:2)
         *      (SEEK_SET:0, SEEK_CUR:1, SEEK_END:2)
         */
        flock.l_type = flock_portable->l_type;
        flock.l_whence = flock_portable->l_whence;
        flock.l_start = (off_t) flock_portable->l_start;
        flock.l_len =  (off_t) flock_portable->l_len;
        flock.l_sysid = 0L;
        flock.l_pid = flock_portable->l_pid;    /* Perhaps 0 would be better */

        result = __fcntl64(fd, mips_cmd, (void *) &flock);

        flock_portable->l_type = flock.l_type;
        flock_portable->l_whence = flock.l_whence;
        flock_portable->l_start = flock.l_start;
        flock_portable->l_len = flock.l_len;
        flock_portable->l_pid = flock.l_pid;
        break;

    case F_GETLK64:
    case F_SETLK64:
    case F_SETLKW64:
        flock64_portable = (struct flock64_portable *) arg;

        if (invalid_pointer(flock_portable)) {
            ALOGE("%s: flock_portable:%p == {NULL||-1}", __func__, flock_portable);
            errno = EFAULT;
            result = -1;
            goto done;
        }

        /*
         * Lock type and Whence are the same for all ARCHs
         *      (F_RDLCK:0,   F_WRLCK:1,  F_UNLCK:2)
         *      (SEEK_SET:0, SEEK_CUR:1, SEEK_END:2)
         */
        flock64.l_type = flock64_portable->l_type;
        flock64.l_whence = flock64_portable->l_whence;
        flock64.l_start = (off_t) flock64_portable->l_start;
        flock64.l_len =  (off_t) flock64_portable->l_len;
        flock64.l_pid = flock64_portable->l_pid;        /* Perhaps 0 would be better */

        result = __fcntl64(fd, mips_cmd, (void *) &flock);

        flock64_portable->l_type = flock64.l_type;
        flock64_portable->l_whence = flock64.l_whence;
        flock64_portable->l_start = flock64.l_start;
        flock64_portable->l_len = flock64.l_len;
        flock64_portable->l_pid = flock64.l_pid;
        break;

    case F_SETFL:
        flags = mips_change_flags((int)arg);
        result = __fcntl64(fd, mips_change_cmd(mips_cmd), (void *)flags);
        break;

    case F_GETFL:
        result = __fcntl64(fd, mips_change_cmd(mips_cmd), arg);
        if (result != -1)
            result = portable_change_flags(result);
        break;

    case F_DUPFD:
    case F_GETFD:
    case F_SETFD:
    case F_SETOWN:
    case F_GETOWN:
    case F_SETSIG:
    case F_GETSIG:
    case F_SETLEASE:
    case F_GETLEASE:
    case F_NOTIFY:
        result = __fcntl64(fd, mips_cmd, arg);
        break;

    default:
        /*
         * This is likely a rare situation, abort() would hang fcntl13 LTP test.
         */
        ALOGE("%s: mips_cmd:%d Doesn't appear to be supported; assume it doesn't need to be mapped!", __func__, mips_cmd);

        result = __fcntl64(fd, mips_cmd, arg);
    }

done:
    ALOGV("%s: return(result:%d); }", __func__, result);
    return(result);
}

