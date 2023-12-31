#ifdef MYLIB_EXPORTS
#define MYLIB_API __declspec(dllexport)
#else
#define MYLIB_API __declspec(dllimport)
#endif

MYLIB_API int x;
MYLIB_API int y;
MYLIB_API int z;

MYLIB_API int slope;

MYLIB_API int xlimx;
MYLIB_API int xlimy;
MYLIB_API int xlimz;

MYLIB_API int ylimx;
MYLIB_API int ylimy;
MYLIB_API int ylimz;

MYLIB_API int zlimx;
MYLIB_API int zlimy;
MYLIB_API int zlimz;
