#include <iostream>
#ifdef _DEBUG
	#pragma comment(lib, "network/network_d.lib")
#else
	#pragma comment(lib, "network/network_r.lib")
#endif
