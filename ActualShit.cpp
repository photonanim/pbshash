#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <chrono>
#include <cmath>
// Aliases for types
#include "types.h"
using namespace std;
// Digits of pi, converted to binary, and then to bytes
vector<u8> DIGITS_OF_PI256 = {
		0xc3, 0x9e, 0x42, 0xc2, 0x82, 0x7d, 0xc3, 0xb7, 0xc3, 0x88, 0x1b, 0xc3, 0x82, 0xc2, 0xa1, 0xc3,
		0x8b, 0x2d, 0xc2, 0xae, 0x5e, 0xc3, 0xb5, 0x18, 0xc2, 0xac, 0x13, 0x5a, 0x4d, 0xc2, 0x82, 0xc2,
		0xb9, 0x22, 0xc2, 0xb8, 0x3e, 0xc2, 0x99, 0xc2, 0xbf, 0xc2, 0x99, 0x33, 0xc2, 0x9d, 0xc3, 0x93,
		0xc2, 0xa1, 0xc3, 0x9c, 0xc3, 0xa1, 0x10, 0xc2, 0x80, 0xc3, 0x9e, 0xc2, 0xb8, 0xc2, 0x98, 0x2b,
		0xc3, 0x85, 0xc3, 0x90, 0x2c, 0x11, 0x7e, 0xc3, 0xb0, 0x22, 0x4c, 0x44, 0xc3, 0x9d, 0x05, 0x24,
		0xc3, 0x98, 0x1f, 0xc3, 0xa9, 0xc3, 0x94, 0x07, 0x2d, 0x11, 0xc3, 0xb8, 0xc3, 0xb1, 0x20, 0x1e,
		0x18, 0x1d, 0x54, 0x20, 0x4f, 0x7f, 0xc2, 0x87, 0xc3, 0xae, 0xc3, 0x97, 0x44, 0x79, 0xc3, 0x8c,
		0xc2, 0x83, 0x3f, 0x49, 0xc3, 0x81, 0x13, 0xc3, 0xb7, 0xc3, 0x9f, 0x6a, 0x20, 0x68, 0x24, 0x3b,
		0x01, 0xc3, 0xb4, 0x21, 0x23, 0x2f, 0x47, 0x29, 0xc2, 0x87, 0x4e, 0xc3, 0x8b, 0x77, 0x7d, 0xc2,
		0x96, 0xc3, 0x90, 0x06, 0x20, 0xc2, 0xaf, 0xc2, 0x95, 0xc3, 0x84, 0x63, 0x68, 0x1c, 0xc3, 0x90,
		0xc2, 0x80, 0xc2, 0xaa, 0x7a, 0xc3, 0x97, 0x22, 0x7d, 0x24, 0xc2, 0xb4, 0xc2, 0x96, 0xc3, 0x91,
		0xc2, 0x9c, 0x51, 0xc3, 0x8d, 0xc3, 0x93, 0x2f, 0x2e, 0x0b, 0xc3, 0xbe, 0xc2, 0xa7, 0xc2, 0x8f,
		0x4e, 0xc3, 0x86, 0x25, 0x19, 0x28, 0xc2, 0xa9, 0xc2, 0xae, 0x2d, 0xc3, 0xb9, 0x59, 0x35, 0xc3,
		0xae, 0x2b, 0x4c, 0xc3, 0xb4, 0x31, 0x3a, 0xc2, 0x84, 0xc3, 0x89, 0x17, 0x07, 0xc2, 0x96, 0xc2,
		0x84, 0xc3, 0x98, 0x6d, 0xc2, 0x9a, 0x75, 0x58, 0x14, 0xc2, 0x9a, 0x50, 0x71, 0x37, 0xc2, 0x9a,
		0xc2, 0x97, 0x20, 0xc2, 0xb8, 0x16, 0x38, 0xc3, 0xa1, 0x71, 0xc3, 0xb0, 0xc3, 0x94, 0x73, 0x7f
};
// Digits of pi, as a digit each
vector<u8> DIGITS_OF_PI1024 {
	3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3,2,3,8,4,6,2,6,4,3,3,
	8,3,2,7,9,5,0,2,8,8,4,1,9,7,1,6,9,3,9,9,3,7,5,1,0,5,8
	,2,0,9,7,4,9,4,4,5,9,2,3,0,7,8,1,6,4,0,6,2,8,6,2,0,8,
	9,9,8,6,2,8,0,3,4,8,2,5,3,4,2,1,1,7,0,6,7,9,8,2,1,4,8,
	0,8,6,5,1,3,2,8,2,3,0,6,6,4,7,0,9,3,8,4,4,6,0,9,5,5,0,
	5,8,2,2,3,1,7,2,5,3,5,9,4,0,8,1,2,8,4,8,1,1,1,7,4,5,0,2
	,8,4,1,0,2,7,0,1,9,3,8,5,2,1,1,0,5,5,5,9,6,4,4,6,2,2,9,
	4,8,9,5,4,9,3,0,3,8,1,9,6,4,4,2,8,8,1,0,9,7,5,6,6,5,9,3,
	3,4,4,6,1,2,8,4,7,5,6,4,8,2,3,3,7,8,6,7,8,3,1,6,5,2,7,1,
	2,0,1,9,0,9,1,4,5,6,4,8,5,6,6,9,2,3,4,6,0,3,4,8,6,1,0,4,
	5,4,3,2,6,6,4,8,2,1,3,3,9,3,6,0,7,2,6,0,2,4,9,1,4,1,2,7,
	3,7,2,4,5,8,7,0,0,6,6,0,6,3,1,5,5,8,8,1,7,4,8,8,1,5,2,0,
	9,2,0,9,6,2,8,2,9,2,5,4,0,9,1,7,1,5,3,6,4,3,6,7,8,9,2,5,
	9,0,3,6,0,0,1,1,3,3,0,5,3,0,5,4,8,8,2,0,4,6,6,5,2,1,3,8,
	4,1,4,6,9,5,1,9,4,1,5,1,1,6,0,9,4,3,3,0,5,7,2,7,0,3,6,5,
	7,5,9,5,9,1,9,5,3,0,9,2,1,8,6,1,1,7,3,8,1,9,3,2,6,1,1,7,
	9,3,1,0,5,1,1,8,5,4,8,0,7,4,4,6,2,3,7,9,9,6,2,7,4,9,5,6,7,
	3,5,1,8,8,5,7,5,2,7,2,4,8,9,1,2,2,7,9,3,8,1,8,3,0,1,1,9,4,
	9,1,2,9,8,3,3,6,7,3,3,6,2,4,4,0,6,5,6,6,4,3,0,8,6,0,2,
	1,3,9,4,9,4,6,3,9,5,2,2,4,7,3,7,1,9,0,7,0,2,1,7,9,8,6,
	0,9,4,3,7,0,2,7,7,0,5,3,9,2,1,7,1,7,6,2,9,3,1,7,6,7,5,2,
	3,8,4,6,7,4,8,1,8,4,6,7,6,6,9,4,0,5,1,3,2,0,0,0,5,6,8,1,
	2,7,1,4,5,2,6,3,5,6,0,8,2,7,7,8,5,7,7,1,3,4,2,7,5,7,7,8,9
	,6,0,9,1,7,3,6,3,7,1,7,8,7,2,1,4,6,8,4,4,0,9,0,1,2,2,4,9,
	5,3,4,3,0,1,4,6,5,4,9,5,8,5,3,7,1,0,5,0,7,9,2,2,7,9,6,8,
	9,2,5,8,9,2,3,5,4,2,0,1,9,9,5,6,1,1,2,1,2,9,0,2,1,9,6,0,8,
	6,4,0,3,4,4,1,8,1,5,9,8,1,3,6,2,9,7,7,4,7,7,1,3,0,9,9,6,0,
	5,1,8,7,0,7,2,1,1,3,4,9,9,9,9,9,9,8,3,7,2,9,7,8,0,4,9,9,5,
	1,0,5,9,7,3,1,7,3,2,8,1,6,0,9,6,3,1,8,5,9,5,0,2,4,4,5,9,4,5,
	5,3,4,6,9,0,8,3,0,2,6,4,2,5,2,2,3,0,8,2,5,3,3,4,4,6,8,5,0,3,
	5,2,6,1,9,3,1,1,8,8,1,7,1,0,1,0,0,0,3,1,3,7,8,3,8,7,5,2,8,8,
	6,5,8,7,5,3,3,2,0,8,3,8,1,4,2,0,6,1,7,1,7,7,6,6,9,1,4,7,3,0,3,5,
	9,8,2,5,3,4,9,0,4,2,8,7,5,5,4,6,8,7,3,1,1,5,9,5,6,2,8,6,3,8,8,2,
	3,5,3,7,8,7,5,9,3,7,5,1,9,5,7,7,8,1,8,5,7,7,8,0,5,3,2,1,7,1,2,2,
	6,8,0,6,6,1,3,0,0,1,9,2,7,8,7,6,6,1,1,1,9,5,9,0,9,2,1,6,4,2,0,1,
	9,8,9,3,8,0,9,5,2,5,7,2,0,1,0,6,5,4,8,5,8,6,3,2,7,8
};
// Global Chunk ID, will be worked on directly by tickRNG(); and initRNG();
u64 globalRNGChunkID = 0;
// Pad Strings of Zeroes.
string padZero(u64 val) {
	u64 mask = 0xF000000000000000;
	string a = "";
	while ((val & mask) == 0x0000000000000000 && mask != 0) {
		a += "0";
		mask = mask >> 4;
	}
	return a;
}
// Splits a string into its bytes
vector<u8> byteSplitter(string a) {
	vector<u8> work;
	for (u64 i = 0; i < a.size(); i++) {
		work.push_back(a.at(i));
	}
	return work;
}
// Turns a byte stream (aligned to 64bits) into chunks of 64 bits
vector<u64> longChunker(vector<u8> data) {
	vector<u64> chunks;
	for (u64 i = 0; i < data.size(); i+=8) {
		u64 temp = 0;
		for (u8 j = 0; j < 8; j++) {
			temp += (((u64)data[i+j]) << (56-(j*8)));
		}
		chunks.push_back(temp);
	}
	return chunks;
}
// Pad a stream of bytes out to a certain alignment with the digits of pi
void pad(vector<u8> &data, u32 alignment) {
	u32 count = (alignment-(data.size()%alignment)%alignment);
	u32 index = data[data.size()-1];
	for (u8 i = 0; i < count; i++) {
		data.push_back(DIGITS_OF_PI256[(index+i)%256]);
	}
}
// LRT/RRT, ty stack overflow
u16 _rotl(const u16 value, i32 shift) {
    if ((shift &= sizeof(value)*8 - 1) == 0)
      return value;
    return (value << shift) | (value >> (sizeof(value)*8 - shift));
}

u16 _rotr(const u16 value, i32 shift) {
    if ((shift &= sizeof(value)*8 - 1) == 0)
      return value;
    return (value >> shift) | (value << (sizeof(value)*8 - shift));
}
u64 _rotl(const u64 value, i32 shift) {
    if ((shift &= sizeof(value)*8 - 1) == 0)
      return value;
    return (value << shift) | (value >> (sizeof(value)*8 - shift));
}

u64 _rotr(const u64 value, i32 shift) {
    if ((shift &= sizeof(value)*8 - 1) == 0)
      return value;
    return (value >> shift) | (value << (sizeof(value)*8 - shift));
}
u64 boolCondenser(vector<bool> collatz) {
	u64 rts = 0;
	u32 extra = 0;
	for (u16 i = 0; i < 64; i++) {
		u64 temp = (u64) collatz[(i+extra)%collatz.size()];
		temp = temp << (63-i);
		rts += temp;
		if (collatz[i%collatz.size()]) {
			extra += 1;
		}
	}
	return rts;
}
// collatzTabler(), boolCondenser() and collatzCounter() in the same function, at once, for efficiency reasons
void unifiedCollatz(vector<bool> &collatzBool, vector<u64> &collatzTable, u64 value) {
	if (value <= 1) {
		collatzBool.push_back(false);
		collatzTable.push_back(0);
		return;
	}
	while (value > 1) {
		if (value % 2 == 0) {
			value = value/2;
			collatzTable.push_back(value);
			collatzBool.push_back(true);
		}
		else {
			value = (3*value)+1;
			collatzTable.push_back(value);
			collatzBool.push_back(false);
		}
	}
	return;
}
// Debug methods, go to DebugMethods.cpp
void printVector(vector<u8>);
void printVector(vector<u64>);
void printVector(vector<u16>);
// Re-iterating
void iteration(vector<u64> &work, u64 chunk, bool debug, u64 chunkID, vector<u8> &firing_order) {
	// The Rest
	vector<u64> shiftAdd = {0, 0};
	vector<unsigned short> chp;
	vector<bool> collatz;
	vector<u64> collatzTable;
	unifiedCollatz(collatz, collatzTable, chunk);
	u64 collatzInt = boolCondenser(collatz);
	for (u8 i = 0; i < 4; i++) {
		chp.push_back((u16)(chunk >> (i*16)));
	}
	for (u8 i = 0; i < 12; i++) {
		u16 temp = (chp[i])+(chp[(i+1)%16]);
		temp = _rotr(temp, DIGITS_OF_PI1024[((chp[i+2]+chunkID+(i+3)))%1024]);
		temp += ((~chp[i+1]) ^ (collatzInt >> i%64));
		chp.push_back(temp);
	}
	for (u8 i = 0; i < 16; i++) {
		chp[i] = _rotl(chp[i], DIGITS_OF_PI1024[(chp[i])%1024]);
	}
	if (debug) {
		cout << "Post-array-extension: ";
		printVector(chp);
	}
	// XORing
	for (u8 i = 0; i < 16; i++) {
		u8 section = (u8)(firing_order[i]/64);
		u64 shifted;
		// Technically the modulo is unnecessary, ig? It'd loop around.
		if (section == 1) shifted = _rotr(((u64)chp[i]), (firing_order[i%64])+DIGITS_OF_PI1024[chp[abs((i-11))%16]%1024]);
		else shifted = _rotl(((u64)chp[i]), firing_order[i%64]+DIGITS_OF_PI1024[chp[abs((i-11))%16]%1024]);
		shifted += (((u64) collatz[i%collatz.size()])+collatzTable[i%collatzTable.size()]%69) << (collatzTable[i%collatzTable.size()]%64);
		work[section] += shifted;
	}
	if (debug) {
		cout << "Chunk" << chunkID << ": " << chunk << endl;
		cout << "Work" << chunkID << ": ";
		cout << hex << work[0] << work[1] << endl;
	}
	return;
}
// Main
vector<u64> messageDigest(vector<u8> data, bool debug) {
	// Order to XOR with the work var
	vector<u8> firing_order = {0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120};
	pad(data, 8);
	if (debug) {
		cout << "Postpadding: ";
		printVector(data);
	}
	vector<u64> chunks = longChunker(data);
	if (debug) {
		cout << "Post-64bit-chunking: ";
		printVector(chunks);
	}
	// Digits of phi (excluding the first) converted from decimal to binary and then to hex
	vector<u64> workvar = {0x62755FEAC4AB1D78,0x135256E12A6A6D64};
	for (u64 i = 0; i < chunks.size(); i++) {
		iteration(workvar, chunks[i], debug, i, firing_order);
	}
	return workvar;
}
// Get Size
ifstream::pos_type filesize(const char* filename) {
    ifstream in(filename, ifstream::ate | ifstream::binary);
    return in.tellg();
}
vector<u64> messageDigest(char filePath[], bool debug, u32 size) {
	// Order to XOR with the work var
	vector<u8> firing_order = {0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120};
	// File Loop
	ifstream bigFile(filePath, ios::binary);
	const char* file = filePath;
	u64 tfs = filesize(file);
	u64 fs = tfs;
	size_t bufferSize = size;
	u32 elSize = bufferSize;
	vector<u8> buffer;
	buffer.resize(bufferSize);
	// Prevent overages
	// Digits of phi (excluding the first) converted from decimal to binary and then to hex
	vector<u64> workvar = {0x62755FEAC4AB1D78,0x135256E12A6A6D64};
	u64 chunkID = 0;
	cout << dec << "0/" << tfs << "B";
	// DEBUG
	while (bigFile.good()) {
		char* a = ((char*)buffer.data());
	    bigFile.read(a, bufferSize);
		if (fs < bufferSize) {
			elSize = fs;
			buffer.resize(elSize);
			pad(buffer, 8);
			if (debug) {
				cout << "Postpadding: ";
				printVector(buffer);
			}
		}
	    vector<u64> fucking = longChunker(buffer);
	    for (u32 i = 0; i < fucking.size(); i++) {
	    	iteration(workvar, fucking[i], debug, chunkID, firing_order);
	    	chunkID++;
	    }
	    fs -= bufferSize;
	    cout << "\r" << (tfs-fs) << "/" << tfs << "B : " << ((f64)(tfs-fs)/tfs)*100.0 << "%                                  " << flush;
	}
	cout << "\r" << flush;
	bigFile.close();
	return workvar;
}
// Init RNG
// Needs empty values workVar and seed to fill by reference
// debug and seedMode are unused; seedMode is the mode used to determine the seed for future use
void initRNG(u64 &seed, vector<u64> &workvar, bool debug, u32 seedMode) {
	globalRNGChunkID = 0;
	auto time = chrono::high_resolution_clock::now();
	auto timec = time.time_since_epoch();
	seed = timec.count();
	workvar[0] = seed << 2;
	workvar[1] = seed >> 2;
}
// Tick the RNG Once
void tickRNG(u64 &seed, vector<u64> &workvar, bool debug) {
	vector<u8> firing_order = {0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120};
	iteration(workvar, seed, debug, globalRNGChunkID, firing_order);
	seed = _rotr(workvar[0], 9);
	workvar[0] = _rotr(workvar[1], 13);
	workvar[1] = _rotl(workvar[0], 22);
	globalRNGChunkID++;
}
// Generate raw 128-bit random numbers using InitRNG() and tickRNG()
void doRandom(u64 amt, bool debug, u32 seedMode) {
	vector<u64> workvar = {0, 0};
	u64 seed = 0;
	initRNG(seed, workvar, debug, seedMode);
	for (u64 i = 0; i < amt; i++) {
		tickRNG(seed, workvar, debug);
		cout << hex << padZero(workvar[0]) << workvar[0] << padZero(workvar[1]) << workvar[1] << "  ";
		if (i % 5 == 4) cout << endl;
	}
}
