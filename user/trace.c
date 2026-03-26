#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int i;
  char *nargv[MAXARG];

  // Nếu người dùng nhập thiếu tham số (ví dụ chỉ gõ "trace" hoặc "trace 32")
  if(argc < 3 || (argv[1][0] < '0' || argv[1][0] > '9')){
    fprintf(2, "Usage: %s mask command\n", argv[0]);
    exit(1);
  }

  // Chuyển chuỗi argv[1] (ví dụ "32") thành số nguyên
  int mask = atoi(argv[1]);

  // Gọi system call trace để thiết lập mask cho tiến trình hiện tại
  if (trace(mask) < 0) {
    fprintf(2, "%s: trace failed\n", argv[0]);
    exit(1);
  }

  // Chuẩn bị mảng tham số mới cho chương trình đích
  // Bỏ qua argv[0] (là "trace") và argv[1] (là mask)
  for(i = 2; i < argc && i < MAXARG; i++){
    nargv[i-2] = argv[i];
  }
  nargv[i-2] = 0; // Đánh dấu kết thúc mảng tham số

  // Dùng exec để chạy chương trình đích với các tham số tương ứng
  // Nếu exec thành công, nó sẽ không bao giờ return.
  exec(nargv[0], nargv);

  // Nếu code chạy đến được dòng này, nghĩa là exec đã thất bại (ví dụ: gõ sai tên chương trình)
  fprintf(2, "exec %s failed\n", nargv[0]);
  exit(1);
}