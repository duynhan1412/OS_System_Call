#ifndef _SYSINFO_H_
#define _SYSINFO_H_

struct sysinfo {
  uint64 freemem;   // Số byte RAM còn trống
  uint64 nproc;     // Số tiến trình không ở trạng thái UNUSED
  uint64 nopenfiles;// Số lượng file đang mở trên toàn hệ thống
};

#endif