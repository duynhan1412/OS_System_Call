#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  struct sysinfo info1, info2;

  printf("=== BAT DAU TEST SYSINFO ===\n");

  // --- LẦN 1: LẤY THÔNG SỐ BAN ĐẦU ---
  if (sysinfo(&info1) < 0) {
    printf("sysinfo failed\n");
    exit(1);
  }
  printf("\n[1] TRANG THAI BAN DAU:\n");
  // Ép kiểu (int) và dùng %d để phù hợp với printf của xv6
  printf("    - RAM trong (Free mem): %d bytes\n", (int)info1.freemem);
  printf("    - So tien trinh (nproc): %d\n", (int)info1.nproc);
  printf("    - So file dang mo (nopenfiles): %d\n", (int)info1.nopenfiles);

  // --- TẠO SỰ THAY ĐỔI TRONG HỆ THỐNG ---
  printf("\n[*] Dang thuc hien: sbrk(10 pages), open(README), fork()...\n");
  
  sbrk(10 * 4096);           // Tiêu tốn RAM: 10 trang
  int fd = open("README", 0); // Mở 1 file
  int pid = fork();          // Tạo 1 tiến trình con

  if (pid < 0) {
    printf("fork failed\n");
    exit(1);
  }

  if (pid == 0) {
    // Tiến trình con ngủ 10 tick để chờ cha đo lường
    sleep(10); 
    exit(0);
  } 
  else {
    // --- LẦN 2: LẤY LẠI THÔNG SỐ ĐỂ SO SÁNH ---
    if (sysinfo(&info2) < 0) {
      printf("sysinfo failed\n");
      exit(1);
    }
    
    printf("\n[2] TRANG THAI SAU KHI THAY DOI:\n");
    printf("    - RAM trong: %d bytes (Da giam %d bytes)\n", 
           (int)info2.freemem, (int)(info1.freemem - info2.freemem));
    printf("    - So tien trinh: %d (Da tang %d)\n", 
           (int)info2.nproc, (int)(info2.nproc - info1.nproc));
    printf("    - So file dang mo: %d (Da tang %d)\n", 
           (int)info2.nopenfiles, (int)(info2.nopenfiles - info1.nopenfiles));

    wait(0);     // Đợi con chạy xong
    close(fd);   // Đóng file
  }

  printf("\n=== KET THUC TEST ===\n");
  exit(0);
}