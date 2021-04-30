void show(const char* format, ...);

void check_buffer(const char* buf, char* str, size_t count);

char* resolved_path(const char* pathname);

void FILE_to_path(FILE* stream, char* name);

void int_to_path(int fd, char* name);

#define fd_path(a, b) \
    _Generic( (a), FILE *: FILE_to_path, \
                  int   : int_to_path)(a, b)
