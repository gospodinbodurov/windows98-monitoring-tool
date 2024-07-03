#include <windows.h>
#include <iostream.h>
#include <fstream.h>
#include <time.h>
#include <stdio.h>

void main() {
   	SYSTEM_INFO siSysInfo;
   
   	while(true) {
		ofstream ofs("C:/Inetpub/iissamples/default/info.txt", ofstream::trunc);
		GetSystemInfo(&siSysInfo);

		ofs << siSysInfo.dwNumberOfProcessors << ",";
		ofs << siSysInfo.dwPageSize << ",";
		ofs << siSysInfo.dwProcessorType << ",";

		MEMORYSTATUS memory;
		GlobalMemoryStatus(&memory);
		int totalrealmem = memory.dwTotalPhys / 1024;
		int availrealmem = memory.dwAvailPhys / 1024;
		int totalswap = memory.dwTotalPageFile / 1024;
		int availswap = memory.dwAvailPageFile / 1024;

		ofs << (totalrealmem - availrealmem) << ",";
		ofs << totalrealmem << ",";
		ofs << (totalswap - availswap) << ",";
		ofs << totalswap << ",";

		BOOLEAN bSuccess;

		ULARGE_INTEGER free_bytes_for_caller;
		free_bytes_for_caller.QuadPart = 0L;

		ULARGE_INTEGER bytes_on_disk;
		bytes_on_disk.QuadPart = 0L;

		ULARGE_INTEGER free_bytes_on_disk;
		free_bytes_on_disk.QuadPart = 0L;

		bSuccess = GetDiskFreeSpaceEx(
			"c:",
			&free_bytes_for_caller,
			&bytes_on_disk,
			&free_bytes_on_disk);

		if(!bSuccess){
			printf("Could not get drive information.\n");
			exit(EXIT_FAILURE);
		}

		double fb = (double)( (signed __int64)(free_bytes_for_caller.QuadPart) / 1.0e9);
		double bd = (double)( (signed __int64)(bytes_on_disk.QuadPart) / 1.0e9);
		double fbd = (double)( (signed __int64)(free_bytes_on_disk.QuadPart) / 1.0e9);

		ofs << (bd-fbd) << ",";
		ofs << bd;

		ofs.flush();
		ofs.close();

		Sleep(1000);
   	}
}
