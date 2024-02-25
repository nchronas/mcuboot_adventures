
#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/reboot.h>
#include <stdlib.h>

#include <zephyr/shell/shell.h>
#include <version.h>
#include <zephyr/drivers/uart.h>
#include "app_version.h"

#include <zephyr/fs/fs.h>

#include <zephyr/storage/disk_access.h>

#include <zephyr/fs/littlefs.h>


// #include <ff.h>
#include <string.h>

#if defined(CONFIG_DISK_DRIVER_SDMMC)
#define DISK_NAME CONFIG_SDMMC_VOLUME_NAME
#elif IS_ENABLED(CONFIG_DISK_DRIVER_MMC)
#define DISK_NAME CONFIG_MMC_VOLUME_NAME
#else
#error "No disk device defined, is your board supported?"
#endif

#define MAX_PATH_LEN 255

struct fs_littlefs lfsfs;
static struct fs_mount_t __mp = {
    .type = FS_LITTLEFS,
    .fs_data = &lfsfs,
    .flags = FS_MOUNT_FLAG_USE_DISK_ACCESS,
};
struct fs_mount_t *mountpoint = &__mp;

static int cmd_fstatvfs(const struct shell *sh, size_t argc, char **argv)
{
    if (argc != 1) {
        shell_print(sh, "Too many arguments");
        return 0;
    }

    struct fs_statvfs sbuf;
    int rc;

    rc = fs_statvfs(mountpoint->mnt_point, &sbuf);
    if (rc != 0) {
        shell_print(sh, "FAIL: statvfs: %d\n", rc);
        return 0;
    }

    shell_print(sh, "%s: bsize = %lu ; frsize = %lu ;"
            " blocks = %lu ; bfree = %lu\n",
            mountpoint->mnt_point,
            sbuf.f_bsize, sbuf.f_frsize,
            sbuf.f_blocks, sbuf.f_bfree);

    return 0;
}

SHELL_CMD_ARG_REGISTER(vfs_stat, NULL, "Virtual file stats", cmd_fstatvfs, 1, 0);

static int cmd_fstat(const struct shell *sh, size_t argc, char **argv)
{
    if (argc != 2) {
        shell_print(sh, "Not enough arguments");
        return 0;
    }
    char fname[MAX_PATH_LEN];
    snprintf(fname, sizeof(fname), "%s/%s", mountpoint->mnt_point, &argv[1][0]);

    struct fs_dirent sbuf;
    int rc;

    rc = fs_stat(fname, &sbuf);
    shell_print(sh, "File %s stat: %d\n", fname, rc);

    return 0;
}

SHELL_CMD_ARG_REGISTER(fstat, NULL, "SD file stats", cmd_fstat, 2, 0);

static int cmd_frm(const struct shell *sh, size_t argc, char **argv)
{
    if (argc != 2) {
        shell_print(sh, "Not enough arguments");
        return 0;
    }

    int rc = 0;

    char fname[MAX_PATH_LEN];
    snprintf(fname, sizeof(fname), "%s/%s", mountpoint->mnt_point, &argv[1][0]);

    rc = fs_unlink(fname);
    if (rc < 0) {
        shell_print(sh, "FAIL: open %s: %d\n", fname, rc);
    }

    return 0;
}

SHELL_CMD_ARG_REGISTER(rm, NULL, "Removes a file or a directory", cmd_frm, 2, 0);

static int cmd_append(const struct shell *sh, size_t argc, char **argv)
{
    if (argc != 3) {
        shell_print(sh, "Not enough arguments");
        return 0;
    }

    struct fs_file_t file;
    int rc, ret = 0;

    char fname[MAX_PATH_LEN];
    snprintf(fname, sizeof(fname), "%s/%s", mountpoint->mnt_point, &argv[1][0]);

    char txt[10];
    snprintf(txt, sizeof(txt), "%s", &argv[2][0]);

    fs_file_t_init(&file);
    rc = fs_open(&file, fname, FS_O_CREATE | FS_O_WRITE);
    if (rc < 0) {
        shell_print(sh, "FAIL: open %s: %d\n", fname, rc);
        return 0;
    }

    rc = fs_seek(&file, 0, FS_SEEK_END);
    if (rc < 0) {
        shell_print(sh, "FAIL: seek %s: %d\n", fname, rc);
    }

    rc = fs_write(&file, &txt, strnlen(txt, 10));
    if (rc < 0) {
        shell_print(sh, "FAIL: write %s: %d\n", fname, rc);
    }

    ret = fs_close(&file);
    if (ret < 0) {
       shell_print(sh, "FAIL: close %s: %d\n", fname, ret);
        return ret;
    }

    return 0;
}

SHELL_CMD_ARG_REGISTER(append, NULL, "Appends up to 10 chars in a file in the beginning of the file", cmd_append, 3, 0);

static int cmd_fwr(const struct shell *sh, size_t argc, char **argv)
{
    if (argc != 3) {
        shell_print(sh, "Not enough arguments");
        return 0;
    }

    struct fs_file_t file;
    int rc, ret = 0;

    char fname[MAX_PATH_LEN];
    snprintf(fname, sizeof(fname), "%s/%s", mountpoint->mnt_point, &argv[1][0]);

    char txt[10];
    snprintf(txt, sizeof(txt), "%s", &argv[2][0]);

    fs_file_t_init(&file);
    rc = fs_open(&file, fname, FS_O_CREATE | FS_O_WRITE);
    if (rc < 0) {
        shell_print(sh, "FAIL: open %s: %d\n", fname, rc);
        return 0;
    }

    rc = fs_write(&file, &txt, strnlen(txt, 10));
    if (rc < 0) {
        shell_print(sh, "FAIL: write %s: %d\n", fname, rc);
    }

    ret = fs_close(&file);
    if (ret < 0) {
       shell_print(sh, "FAIL: close %s: %d\n", fname, ret);
        return ret;
    }

    return 0;
}

SHELL_CMD_ARG_REGISTER(fwrite, NULL, "Writes up to 10 chars in a file in the beginning of the file", cmd_fwr, 3, 0);

static int cmd_boot_count(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    uint8_t boot_count = 0;
    struct fs_file_t file;
    int rc, ret;

    char fname[MAX_PATH_LEN];
    snprintf(fname, sizeof(fname), "%s/boot_list", mountpoint->mnt_point);

    fs_file_t_init(&file);
    rc = fs_open(&file, fname, FS_O_CREATE | FS_O_RDWR);
    if (rc < 0) {
        shell_print(sh, "FAIL: open %s: %d\n", fname, rc);
        return rc;
    }

    shell_print(sh, "Read boot list:\n");
    while (1) {

        uint32_t version;

        rc = fs_read(&file, &boot_count, sizeof(boot_count));
        if (rc == 0) {
            break;
        } else if (rc != sizeof(boot_count)) {
            shell_print(sh, "FAIL: read boot_count %s: [rd:%d]", fname, rc);
            break;
        }

        rc = fs_read(&file, &version, sizeof(version));
        if (rc != sizeof(version)) {
            shell_print(sh, "FAIL: read version %s: [rd:%d]", fname, rc);
            break;
        }

        shell_print(sh, "Boot count:%d, version: %u.%u", boot_count, (version >> 16) & 0xFF, (version >> 8) & 0xFF);
    }
    shell_print(sh, "\nRead boot list finished\n");

    // Update table with the new entry of this boot
    boot_count += 1;
    rc = fs_write(&file, &boot_count, sizeof(boot_count));
    if (rc < 0) {
        shell_print(sh, "FAIL: write %s: %d\n", fname, rc);
        goto out;
    }

    uint32_t version = APP_VERSION_NUMBER;

    rc = fs_write(&file, &version, sizeof(version));
    if (rc < 0) {
        shell_print(sh, "FAIL: write %s: %d\n", fname, rc);
        goto out;
    }

    shell_print(sh, "%s write new boot count %u, version %u.%u: [wr:%d]\n", fname, boot_count, APP_VERSION_MAJOR, APP_VERSION_MINOR, rc);  // NOLINT

    out:
    ret = fs_close(&file);
    if (ret < 0) {
        shell_print(sh, "FAIL: close %s: %d\n", fname, ret);
        return ret;
    }

    return 0;
}

SHELL_CMD_ARG_REGISTER(boot_count, NULL, "Updates and reads boot count and versions log", cmd_boot_count, 1, 0);

static int cmd_frd(const struct shell *sh, size_t argc, char **argv)
{
    if (argc != 2) {
        shell_print(sh, "Not enough arguments");
        return 0;
    }

    struct fs_file_t file;
    int rc, ret;

    char fname[MAX_PATH_LEN];
    snprintf(fname, sizeof(fname), "%s/%s", mountpoint->mnt_point, &argv[1][0]);

    fs_file_t_init(&file);
    rc = fs_open(&file, fname, FS_O_READ);
    if (rc < 0) {
        shell_print(sh, "FAIL: open %s: %d\n", fname, rc);
        return 0;
    }

    shell_print(sh, "File content %s:\n", fname);
    do {
        uint8_t temp = 0;

        rc = fs_read(&file, &temp, 1);
        if (rc < 0) {
            shell_print(sh, "\nFAIL: read %s: [rd:%d]", fname, rc);
            break;
        }

        if (rc != 1) {
            break;
        }

        shell_fprintf(sh, SHELL_INFO, "%u", temp);
    } while (rc == 1);
    shell_print(sh, "\nFile content finished\n");

    ret = fs_close(&file);
    if (ret < 0) {
       shell_print(sh, "FAIL: close %s: %d\n", fname, ret);
        return ret;
    }

    return 0;
}

SHELL_CMD_ARG_REGISTER(read, NULL, "SD file read", cmd_frd, 2, 0);

static int cmd_cat(const struct shell *sh, size_t argc, char **argv)
{
    if (argc != 2) {
        shell_print(sh, "Not enough arguments");
        return 0;
    }

    struct fs_file_t file;
    int rc, ret;

    char fname[MAX_PATH_LEN];
    snprintf(fname, sizeof(fname), "%s/%s", mountpoint->mnt_point, &argv[1][0]);

    fs_file_t_init(&file);
    rc = fs_open(&file, fname, FS_O_READ);
    if (rc < 0) {
        shell_print(sh, "FAIL: open %s: %d\n", fname, rc);
        return 0;
    }

    shell_print(sh, "File content %s:\n", fname);
    do {
        char temp[2];
        temp[1] = 0;

        rc = fs_read(&file, temp, 1);
        if (rc < 0) {
            shell_print(sh, "\nFAIL: read %s: [rd:%d]", fname, rc);
            break;
        }

        if (rc != 1) {
            break;
        }

        shell_fprintf(sh, SHELL_INFO, "%s", temp);
    } while (rc == 1);
    shell_print(sh, "\nFile content finished\n");

    ret = fs_close(&file);
    if (ret < 0) {
       shell_print(sh, "FAIL: close %s: %d\n", fname, ret);
        return ret;
    }

    return 0;
}

SHELL_CMD_ARG_REGISTER(cat, NULL, "SD file cat", cmd_cat, 2, 0);

static int cmd_ls(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    int res;
    struct fs_dir_t dirp;
    static struct fs_dirent entry;

    const char *path = mountpoint->mnt_point;

    fs_dir_t_init(&dirp);

    /* Verify fs_opendir() */
    res = fs_opendir(&dirp, path);
    if (res) {
        shell_print(sh, "Error opening dir %s [%d]\n", path, res);
        return res;
    }

    shell_print(sh, "\nListing dir %s ...\n", path);
    for (;;) {
        /* Verify fs_readdir() */
        res = fs_readdir(&dirp, &entry);

        /* entry.name[0] == 0 means end-of-dir */
        if (res || entry.name[0] == 0) {
            if (res < 0) {
                shell_print(sh, "Error reading dir [%d]\n", res);
            }
            break;
        }

        if (entry.type == FS_DIR_ENTRY_DIR) {
            LOG_PRINTK("[DIR ] %s\n", entry.name);
        } else {
            shell_print(sh, "[FILE] %s (size = %zu)\n",
                    entry.name, entry.size);
        }
    }

    /* Verify fs_closedir() */
    fs_closedir(&dirp);

    return 0;
}

SHELL_CMD_ARG_REGISTER(ls, NULL, "SD LS", cmd_ls, 1, 0);

// static int cmd_info(const struct shell *sh, size_t argc, char **argv)
// {
//     ARG_UNUSED(argc);
//     ARG_UNUSED(argv);

//     static const char *disk_pdrv = "SD";
//     uint64_t memory_size_mb;
//     uint32_t block_count;
//     uint32_t block_size;

//     if (disk_access_init(disk_pdrv) != 0) {
//         shell_print(sh, "Storage init ERROR!");
//         return 0;
//     }

//     if (disk_access_ioctl(disk_pdrv,
//         DISK_IOCTL_GET_SECTOR_COUNT, &block_count)) {
//             shell_print(sh, "Unable to get sector count");
//             return 0;
//     }
//     shell_print(sh, "Block count %u", block_count);

//     if (disk_access_ioctl(disk_pdrv,
//         DISK_IOCTL_GET_SECTOR_SIZE, &block_size)) {
//             shell_print(sh, "Unable to get sector size");
//             return 0;
//     }
//     shell_print(sh, "Sector size %u", block_size);

//     memory_size_mb = (uint64_t)block_count * block_size;
//     shell_print(sh, "Memory Size(MB) %u", (uint32_t)(memory_size_mb >> 20));

//     char fname1[MAX_PATH_LEN];
//     char fname2[MAX_PATH_LEN];
//     struct fs_statvfs sbuf;
//     int rc;

//     snprintf(fname1, sizeof(fname1), "%s/boot_count", mountpoint->mnt_point);
//     snprintf(fname2, sizeof(fname2), "%s/pattern.bin", mountpoint->mnt_point);

//     rc = fs_statvfs(mountpoint->mnt_point, &sbuf);
//     if (rc < 0) {
//         shell_print(sh, "FAIL: statvfs: %d\n", rc);
//         return 0;
//     }

//     shell_print(sh, "%s: bsize = %lu ; frsize = %lu ;"
//             " blocks = %lu ; bfree = %lu\n",
//             mountpoint->mnt_point,
//             sbuf.f_bsize, sbuf.f_frsize,
//             sbuf.f_blocks, sbuf.f_bfree);

//     return 0;
// }

// SHELL_CMD_ARG_REGISTER(info, NULL, "sd info", cmd_info, 1, 0);

static int cmd_unmount(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    int res = fs_unmount(mountpoint);
    LOG_PRINTK("%s unmount: %d\n", mountpoint->mnt_point, res);

    return 0;
}

SHELL_CMD_ARG_REGISTER(unmount, NULL, "Unmount sd", cmd_unmount, 1, 0);


static int cmd_mount(const struct shell *sh, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
    ARG_UNUSED(argv);

    static const char *disk_mount_pt = "/"DISK_NAME":";
    static const char *disk_pdrv = DISK_NAME;

    mountpoint->storage_dev = (void *)disk_pdrv;
    mountpoint->mnt_point = disk_mount_pt;

    int res = fs_mount(mountpoint);
    if (res < 0) {
        shell_print(sh, "LFS mount error\n");
    } else {
        shell_print(sh, "LFS mounted\n");
    }

    return 0;
}

SHELL_CMD_ARG_REGISTER(mount, NULL, "Mount sd", cmd_mount, 1, 0);
