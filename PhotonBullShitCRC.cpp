#include <iostream>
#include <vector>
#include <iomanip>
#include "types.h"
#include <chrono>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
using namespace std;
vector<u64> messageDigest(vector<u8>, bool);
vector<u64> messageDigest(char[], bool, u32);
vector<u8> byteSplitter(string);
void doRandom(u64, bool, u32);
string padZero(u64);
void readFlags(int argc, char* argv[], bool &debug, bool &bufferSizeFlag, u8 &bufferSizeLoc, u8 startOffset) {
	for (u8 i = startOffset; i < argc; i++) {
		switch(argv[i][0]) {
		case ('d'):
			debug = true;
			break;
		case ('b'):
			bufferSizeFlag = true;
			i++;
			bufferSizeLoc = i;
			break;
		}
	}
}
u32 argInt(char* argv[], u8 offset) {
	// Stackoverflowlol
    char *p;
    errno = 0;
    i64 conv = strtol(argv[offset], &p, 10);
    // Error checking
    if (errno != 0 || *p != '\0' || conv > UINT_MAX || conv < 0) { cout << "Invalid buffer size. Defaulting to 1024K.\n"; return 1024; }
    return (u32)conv;
}
int main(int argc, char* argv[]) {
	bool debug = false;
	bool bufferSizeFlag = false;
	u8 bufferSizeLoc = 0;
	vector<u8> data;
	vector<u64> ret;
	u32 bufferSize = 1024;
	f64 time;
	switch (argv[1][0]) {
	// Help
	case ('h'):
		cout << "PROGRAM <function> <function args> <..options>\n\nFUNCTIONS:\nh for help\nv for version info.\nt for terrasteel\ns <string-to-hash> for string hashing\nf <path/to/file/lol> for file hashing\nn <quantity> to generate a quantity of pseudorandom 128-bit numbers (seed will be based on system clock, hash algorithm will be used.)\n\nOPTIONS:\nd for debug information\nb for custom file read buffer size\n\nEXAMPLE COMMAND: PROGRAM s Terrasteel d\nThe program may recognize the first letter of other words as a command.\n\nTHIS GOES WITHOUT SAYING, BUT DO NOT USE THIS FOR SERIOUS CRYPTOGRAPHIC PURPOSES!!!";
		return 1;
	// Version
	case ('v'):
		cout << "Photon BullShit, v0.2\n(C) Photon 2021\n";
		return 1;
	// Terrasteel
	case ('t'):
		cout << "terrasteel\n";
		return 1;
	// Hash a string
	case ('s'):
		if (argc < 3) break;
		readFlags(argc, argv, debug, bufferSizeFlag, bufferSizeLoc, 3);
		data = byteSplitter(argv[2]);
		ret = messageDigest(data, debug);
		cout << hex << padZero(ret[0]) << ret[0] << padZero(ret[1]) << ret[1] << endl;
		return 1;
	// Hash a file
	case ('f'):
		if (argc < 3) break;
		readFlags(argc, argv, debug, bufferSizeFlag, bufferSizeLoc, 3);
		if (bufferSizeFlag) bufferSize = argInt(argv, bufferSizeLoc);
		clock_t start, end;
		start = clock();
		ret = messageDigest(argv[2], debug, bufferSize*1024);
		end = clock();
		time = (end-start) / f64(CLOCKS_PER_SEC);
		cout << hex << padZero(ret[0]) << ret[0] << padZero(ret[1]) << ret[1] << endl;
		cout << time << "s" << endl;
		return 1;
	// Raw Random Numbers
	case ('n'):
		if (argc < 3) break;
		readFlags(argc, argv, debug, bufferSizeFlag, bufferSizeLoc, 3);
		u64 rawRandomAmount = argInt(argv, 2);
		doRandom(rawRandomAmount, debug, 0);
		return 1;
	}
	// Ultimate Invalid
	cout << "Invalid input(s), execute PROGRAM h for help.\n";
	return 0;
}
