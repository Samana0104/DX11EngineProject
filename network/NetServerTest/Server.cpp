#include <iostream>
#include <string>
#include "MyNetIOCPServ.h"
#ifdef _DEBUG
	#pragma comment(lib, "network/network_d.lib")
#else
	#pragma comment(lib, "network/network_r.lib")
#endif

int main()
{
	MyProject::MyNetIOCPServ serv(10000);

	serv.Run();
	return 0;
}
