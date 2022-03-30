#include <stdio.h>
#include <stdlib.h>
int main() {
   FILE *fileRead, *fileOverwritten;
   char filename[100], c;
   printf("Enter the name of the file whos content will be copied: \n");
   scanf("%s",filename);

   // Open file for reading
   fileRead = fopen(filename, "r");
   if (fileRead == NULL) {
     //If the file cannot be open, notify the user and exit.
      printf("Cannot open file %s \n", filename);
      exit(0);
   }

   printf("Enter the name of the file which will be overwritten: \n");
   scanf("%s", filename);
   // Open the file that will be overwritten
   fileOverwritten = fopen(filename, "w");
   if (fileOverwritten == NULL) {
     //If the file cannot be open, notify the user and exit.
      printf("Cannot open file %s \n", filename);
      exit(0);
   }

   // Read contents from the first file
   c = fgetc(fileRead);
   while (c != EOF) {
     //start copying the content from file 1 to file 2
      fputc(c, fileOverwritten);
      c = fgetc(fileRead);
   }

   // Notify the user that the program succesfully copied the content.
   printf("\nContents copied to %s\n", filename);
   // Close both files that were previously opened
   fclose(fileRead);
   fclose(fileOverwritten);
   // Exit
   return 0;
}

// List of System Calls performed by this program upon a succesful run:
//     0.000000 execve("/usr/bin/ls", ["ls"], 0x7fffc3ae28f8 /* 25 vars */) = 0
//     0.047502 brk(NULL)                 = 0x7fffef7a4000
//     0.001127 arch_prctl(0x3001 /* ARCH_??? */, 0x7ffff76cf2c0) = -1 EINVAL (Invalid argument)
//     0.001220 access("/etc/ld.so.preload", R_OK) = -1 ENOENT (No such file or directory)
//     0.001007 openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
//     0.001056 fstat(3, {st_mode=S_IFREG|0644, st_size=40670, ...}) = 0
//     0.000626 mmap(NULL, 40670, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f407aba5000
//     0.000595 close(3)                  = 0
//     0.000623 openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libselinux.so.1", O_RDONLY|O_CLOEXEC) = 3
//     0.000436 read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0@p\0\0\0\0\0\0"..., 832) = 832
//     0.000420 fstat(3, {st_mode=S_IFREG|0644, st_size=163200, ...}) = 0
//     0.000455 mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f407aba0000
//     0.000560 mmap(NULL, 174600, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f407ab40000
//     0.000453 mprotect(0x7f407ab46000, 135168, PROT_NONE) = 0
//     0.000410 mmap(0x7f407ab46000, 102400, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x6000) = 0x7f407ab46000
//     0.000833 mmap(0x7f407ab5f000, 28672, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1f000) = 0x7f407ab5f000
//     0.000411 mmap(0x7f407ab67000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x26000) = 0x7f407ab67000
//     0.000757 mmap(0x7f407ab69000, 6664, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f407ab69000
//     0.000809 close(3)                  = 0
//     0.000430 openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
//     0.000600 read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\360q\2\0\0\0\0\0"..., 832) = 832
//     0.000431 pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
//     0.000403 pread64(3, "\4\0\0\0\20\0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0", 32, 848) = 32
//     0.000455 pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\t\233\222%\274\260\320\31\331\326\10\204\276X>\263"..., 68, 880) = 68
//     0.002986 fstat(3, {st_mode=S_IFREG|0755, st_size=2029224, ...}) = 0
//     0.000473 pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
//     0.000507 pread64(3, "\4\0\0\0\20\0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0", 32, 848) = 32
//     0.000490 pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\t\233\222%\274\260\320\31\331\326\10\204\276X>\263"..., 68, 880) = 68
//     0.001274 mmap(NULL, 2036952, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f407a940000
//     0.000756 mprotect(0x7f407a965000, 1847296, PROT_NONE) = 0
//     0.000458 mmap(0x7f407a965000, 1540096, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x25000) = 0x7f407a965000
//     0.000867 mmap(0x7f407aadd000, 303104, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x19d000) = 0x7f407aadd000     0.000471 mmap(0x7f407ab28000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7f407ab28000
//     0.000820 mmap(0x7f407ab2e000, 13528, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f407ab2e000
//     0.000756 close(3)                  = 0
//     0.000417 openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libpcre2-8.so.0", O_RDONLY|O_CLOEXEC) = 3
//     0.000480 read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\340\"\0\0\0\0\0\0"..., 832) = 832
//     0.000450 fstat(3, {st_mode=S_IFREG|0644, st_size=584392, ...}) = 0
//     0.000401 mmap(NULL, 586536, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f407a8b0000
//     0.000455 mmap(0x7f407a8b2000, 409600, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x7f407a8b2000
//     0.000741 mmap(0x7f407a916000, 163840, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x66000) = 0x7f407a916000
//     0.000541 mmap(0x7f407a93e000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x8d000) = 0x7f407a93e000
//     0.000831 close(3)                  = 0
//     0.000389 openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libdl.so.2", O_RDONLY|O_CLOEXEC) = 3
//     0.000465 read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0 \22\0\0\0\0\0\0"..., 832) = 832
//     0.000431 fstat(3, {st_mode=S_IFREG|0644, st_size=18816, ...}) = 0
//     0.002576 mmap(NULL, 20752, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f407a8a0000
//     0.000609 mmap(0x7f407a8a1000, 8192, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1000) = 0x7f407a8a1000
//     0.001138 mmap(0x7f407a8a3000, 4096, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x3000) = 0x7f407a8a3000
//     0.000683 mmap(0x7f407a8a4000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x3000) = 0x7f407a8a4000
//     0.000836 close(3)                  = 0
//     0.001350 openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libpthread.so.0", O_RDONLY|O_CLOEXEC) = 3
//     0.000804 read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\220\201\0\0\0\0\0\0"..., 832) = 832
//     0.000478 pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\345Ga\367\265T\320\374\301V)Yf]\223\337"..., 68, 824) = 68
//     0.000465 fstat(3, {st_mode=S_IFREG|0755, st_size=157224, ...}) = 0
//     0.000446 pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\345Ga\367\265T\320\374\301V)Yf]\223\337"..., 68, 824) = 68
//     0.000450 mmap(NULL, 140408, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f407a87d000
//     0.000467 mmap(0x7f407a884000, 69632, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x7000) = 0x7f407a884000
//     0.000659 mmap(0x7f407a895000, 20480, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x18000) = 0x7f407a895000
//     0.000479 mmap(0x7f407a89a000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1c000) = 0x7f407a89a000
//     0.000721 mmap(0x7f407a89c000, 13432, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f407a89c000
//     0.000828 close(3)                  = 0
//     0.000454 mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f407a870000
//     0.000411 arch_prctl(ARCH_SET_FS, 0x7f407a871000) = 0
//     0.000541 mprotect(0x7f407ab28000, 12288, PROT_READ) = 0
//     0.000277 mprotect(0x7f407a89a000, 4096, PROT_READ) = 0
//     0.000396 mprotect(0x7f407a8a4000, 4096, PROT_READ) = 0
//     0.000410 mprotect(0x7f407a93e000, 4096, PROT_READ) = 0
//     0.000431 mprotect(0x7f407ab67000, 4096, PROT_READ) = 0
//     0.000472 mprotect(0x7f407abd1000, 4096, PROT_READ) = 0
//     0.002099 mprotect(0x7f407ab9d000, 4096, PROT_READ) = 0
//     0.000434 munmap(0x7f407aba5000, 40670) = 0
//     0.000461 set_tid_address(0x7f407a8712d0) = 217
//     0.000366 set_robust_list(0x7f407a8712e0, 24) = 0
//     0.000449 rt_sigaction(SIGRTMIN, {sa_handler=0x7f407a884bf0, sa_mask=[], sa_flags=SA_RESTORER|SA_SIGINFO, sa_restorer=0x7f407a8923c0}, NULL, 8) = 0
//     0.000807 rt_sigaction(SIGRT_1, {sa_handler=0x7f407a884c90, sa_mask=[], sa_flags=SA_RESTORER|SA_RESTART|SA_SIGINFO, sa_restorer=0x7f407a8923c0}, NULL, 8) = 0
//     0.000724 rt_sigprocmask(SIG_UNBLOCK, [RTMIN RT_1], NULL, 8) = 0
//     0.000425 prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=8192*1024}) = 0
//     0.000790 statfs("/sys/fs/selinux", 0x7ffff76cf210) = -1 ENOENT (No such file or directory)
//     0.000957 statfs("/selinux", 0x7ffff76cf210) = -1 ENOENT (No such file or directory)
//     0.000791 brk(NULL)                 = 0x7fffef7a4000
//     0.000337 brk(0x7fffef7c5000)       = 0x7fffef7c5000
//     0.000499 openat(AT_FDCWD, "/proc/filesystems", O_RDONLY|O_CLOEXEC) = 3
//     0.000402 fstat(3, {st_mode=S_IFREG|0444, st_size=0, ...}) = 0
//     0.000412 read(3, "nodev\tsysfs\nnodev\trootfs\nnodev\tb"..., 4096) = 312
//     0.000423 read(3, "", 4096)         = 0
//     0.000394 close(3)                  = 0
//     0.000397 access("/etc/selinux/config", F_OK) = -1 ENOENT (No such file or directory)
//     0.000527 openat(AT_FDCWD, "/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
//     0.000395 fstat(3, {st_mode=S_IFREG|0644, st_size=3035952, ...}) = 0
//     0.000438 mmap(NULL, 3035952, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f407a58a000
//     0.000469 close(3)                  = 0
//     0.000473 openat(AT_FDCWD, "/usr/share/locale/locale.alias", O_RDONLY|O_CLOEXEC) = 3
//     0.000421 fstat(3, {st_mode=S_IFREG|0644, st_size=2996, ...}) = 0
//     0.000434 read(3, "# Locale name alias data base.\n#"..., 512) = 512
//     0.000435 read(3, "See the\n# GNU General Public Lic"..., 512) = 512
//     0.000448 read(3, "und for the time being for\n# bac"..., 512) = 512
//     0.000523 read(3, "These lines were removed\n# becau"..., 512) = 512
//     0.002934 read(3, "-8859-1\ngalego\t\tgl_ES.ISO-8859-1"..., 512) = 512
//     0.000485 read(3, "NO.ISO-8859-1 nb_NO.ISO-8859-1\nn"..., 512) = 436
//     0.000428 read(3, "", 512)          = 0
//     0.000421 close(3)                  = 0
//     0.000503 openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_IDENTIFICATION", O_RDONLY|O_CLOEXEC) = 3
//     0.000647 fstat(3, {st_mode=S_IFREG|0644, st_size=252, ...}) = 0
//     0.000567 mmap(NULL, 252, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f407abae000
//     0.000492 close(3)                  = 0
//     0.000449 openat(AT_FDCWD, "/usr/lib/x86_64-linux-gnu/gconv/gconv-modules.cache", O_RDONLY) = 3
//     0.001003 fstat(3, {st_mode=S_IFREG|0644, st_size=27002, ...}) = 0
//     0.000914 mmap(NULL, 27002, PROT_READ, MAP_SHARED, 3, 0) = 0x7f407aba7000
//     0.000462 close(3)                  = 0
//     0.000482 futex(0x7f407ab2d634, FUTEX_WAKE_PRIVATE, 2147483647) = 0
//     0.000431 openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_MEASUREMENT", O_RDONLY|O_CLOEXEC) = 3
//     0.000412 fstat(3, {st_mode=S_IFREG|0644, st_size=23, ...}) = 0
//     0.000457 mmap(NULL, 23, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f407aba6000
//     0.000402 close(3)                  = 0
//     0.000481 openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_TELEPHONE", O_RDONLY|O_CLOEXEC) = 3
//     0.000400 fstat(3, {st_mode=S_IFREG|0644, st_size=47, ...}) = 0
//     0.000457 mmap(NULL, 47, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f407aba5000
//     0.000399 close(3)                  = 0
//     0.000475 openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_ADDRESS", O_RDONLY|O_CLOEXEC) = 3
//     0.000421 fstat(3, {st_mode=S_IFREG|0644, st_size=131, ...}) = 0
//     0.000425 mmap(NULL, 131, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f407aba4000
//     0.000479 close(3)                  = 0
//     0.000454 openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_NAME", O_RDONLY|O_CLOEXEC) = 3
//     0.001958 fstat(3, {st_mode=S_IFREG|0644, st_size=62, ...}) = 0
//     0.000578 mmap(NULL, 62, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f407aba3000
//     0.000751 close(3)                  = 0
//     0.000528 openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_PAPER", O_RDONLY|O_CLOEXEC) = 3
//     0.000454 fstat(3, {st_mode=S_IFREG|0644, st_size=34, ...}) = 0
//     0.000430 mmap(NULL, 34, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f407aba2000
//     0.000430 close(3)                  = 0
//     0.000456 openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_MESSAGES", O_RDONLY|O_CLOEXEC) = 3
//     0.000421 fstat(3, {st_mode=S_IFDIR|0755, st_size=512, ...}) = 0
//     0.000399 close(3)                  = 0
//     0.000448 openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_MESSAGES/SYS_LC_MESSAGES", O_RDONLY|O_CLOEXEC) = 3
//     0.000485 fstat(3, {st_mode=S_IFREG|0644, st_size=48, ...}) = 0
//     0.000425 mmap(NULL, 48, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f407ab9c000
//     0.000590 close(3)                  = 0
//     0.001109 openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_MONETARY", O_RDONLY|O_CLOEXEC) = 3
//     0.000538 fstat(3, {st_mode=S_IFREG|0644, st_size=270, ...}) = 0
//     0.000445 mmap(NULL, 270, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f407ab6f000
//     0.000444 close(3)                  = 0
//     0.000460 openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_COLLATE", O_RDONLY|O_CLOEXEC) = 3
//     0.000427 fstat(3, {st_mode=S_IFREG|0644, st_size=1518110, ...}) = 0
//     0.000428 mmap(NULL, 1518110, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f407a417000
//     0.000442 close(3)                  = 0
//     0.000414 openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_TIME", O_RDONLY|O_CLOEXEC) = 3
//     0.000456 fstat(3, {st_mode=S_IFREG|0644, st_size=3360, ...}) = 0
//     0.000446 mmap(NULL, 3360, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f407ab6e000
//     0.000451 close(3)                  = 0
//     0.000440 openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_NUMERIC", O_RDONLY|O_CLOEXEC) = 3
//     0.000403 fstat(3, {st_mode=S_IFREG|0644, st_size=50, ...}) = 0
//     0.000452 mmap(NULL, 50, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f407ab6d000
//     0.000398 close(3)                  = 0
//     0.002183 openat(AT_FDCWD, "/usr/lib/locale/C.UTF-8/LC_CTYPE", O_RDONLY|O_CLOEXEC) = 3
//     0.000431 fstat(3, {st_mode=S_IFREG|0644, st_size=201272, ...}) = 0
//     0.000395 mmap(NULL, 201272, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f407a3e5000
//     0.000486 close(3)                  = 0
//     0.000500 ioctl(1, TCGETS, {B38400 opost isig icanon echo ...}) = 0
//     0.000373 ioctl(1, TIOCGWINSZ, {ws_row=30, ws_col=120, ws_xpixel=0, ws_ypixel=0}) = 0
//     0.000439 openat(AT_FDCWD, ".", O_RDONLY|O_NONBLOCK|O_CLOEXEC|O_DIRECTORY) = 3
//     0.000422 fstat(3, {st_mode=S_IFDIR|0777, st_size=512, ...}) = 0
//     0.000467 getdents64(3, /* 9 entries */, 32768) = 280
//     0.000479 getdents64(3, /* 0 entries */, 32768) = 0
//     0.000364 close(3)                  = 0
//     0.000517 fstat(1, {st_mode=S_IFCHR|0660, st_rdev=makedev(0x4, 0x1), ...}) = 0
//     0.000378 ioctl(1, TCGETS, {B38400 opost isig icanon echo ...}) = 0
//     0.000412 write(1, "FileContentCopy  Makefile  Q2-15"..., 73FileContentCopy  Makefile  Q2-15.c  Q2-15.d  Q2-15.o  Read.txt  Write.txt
// ) = 73
//     0.001373 close(1)                  = 0
//     0.000963 close(2)                  = 0
//     0.000534 exit_group(0)             = ?
//     0.000702 +++ exited with 0 +++
