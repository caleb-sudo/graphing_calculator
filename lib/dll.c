#ifdef BUILD_DLL
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

EXPORT int __stdcall x(int xnum){
	return xnum;
}
EXPORT int __stdcall y(int ynum){
	return ynum;
}
EXPORT int __stdcall z(int znum){
	return znum;
}
EXPORT int __stdcall slope(int m){
	return m;
}
EXPORT int __stdcall intercept(int b) {
	return b;
}
