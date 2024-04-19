#include <stdint.h>
#include <sys/stat.h>

#include <uart/uart.h>

int _close(int fd) {
    return -1;
}

int _fstat(int fd, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}

int _isatty(int fd) {
  return 1;
}

int _lseek(int fd, int offset, int whence) {
  return 0;
}

int _read(int fd, char *buf, int len) {
  return uart0_read();
}

char *_sbrk(int incr) {
  extern char _sheap;
  static char *heap_end = &_sheap;
  char *prev_heap_end;

  prev_heap_end = heap_end;
  heap_end += incr; /* may lead to heap and stack colliding */
  return prev_heap_end;
}

int _write(int fd, char *buf, int len) {
  for (int i = 0; i < len; i++) {
    uart0_write(buf[i]);
  }
  return len;
}
