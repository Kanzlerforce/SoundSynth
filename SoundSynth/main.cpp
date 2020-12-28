#include <iostream>
using namespace std;

#include "olcNoiseMaker.h";

double makeNoise(double dTime) {
	double dOutput = 1.0 * sin(440.0 * 2 * 3.14159 * dTime);

	if(dOutput > 0.0) {
		return 0.2;
	} else {
		return -0.2;
	}
}

int main() {
	wcout << "Synthesizer Part 1" << endl;

	// Get all sound hardware
	vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

	// Display findings
	for (auto d : devices) wcout << "Found Output Device: " << d << endl;

	// Create sound machine
	// device, sample rate, channels, and two magic myster numbers
	olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);

	// Link noise function with sound machine
	sound.SetUserFunction(makeNoise);

	while(1) {

	}

	return 0;
}