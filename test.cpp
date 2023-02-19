#include <iostream>
#include <math.h>
#include <chrono>
using namespace std;

double arr[10000000];

int main() {
	double sum = 0;
#pragma acc enter data create(arr[0:10000000], sum)
	double part = 2 * acos(-1) / 9999999;
	auto start = chrono::high_resolution_clock::now();
#pragma acc parallel loop present(arr[0:10000000])
	for (int i = 0; i < 10000000; i++) {
		arr[i] = sin(part * i);
	}
#pragma acc parallel loop present(arr[0:10000000], sum) reduction(+:sum)
	for (int i = 0; i < 10000000; i++) {
		sum = sum + arr[i];
	}
	auto elapsed = chrono::high_resolution_clock::now() - start;
	long long msec = chrono::duration_cast<chrono::microseconds>(elapsed).count();
#pragma acc exit data delete(arr[0:10000000]) copyout(sum)
	cout << sum << "/n";
	cout << msec;
	return 0;
}
