#ifndef DEBUG_H
#define DEBUG_H

#define DBG 0

#define debug_print(fmt, ...) do { if (DBG) fprintf(stderr, fmt, __VA_ARGS__); } while (0)

#endif
