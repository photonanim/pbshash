#include <iomanip>
#include <iostream>
#include <vector>
#include <string>
#include "types.h"
using namespace std;
void printVector(vector<u8> a) {
	cout << "[";
	for (unsigned int i = 0; i < a.size(); i++) {
		cout << hex << (u16)a[i] << ", ";
	}
	cout << "\b\b]" << endl;
}
void printVector(vector<u64> a) {
	cout << "[";
	for (unsigned int i = 0; i < a.size(); i++) {
		cout << hex << a[i] << ", ";
	}
	cout << "\b\b]" << endl;
}
void printVector(vector<u16> a) {
	cout << "[";
	for (unsigned int i = 0; i < a.size(); i++) {
		cout << hex << a[i] << ", ";
	}
	cout << "\b\b]" << endl;
}
