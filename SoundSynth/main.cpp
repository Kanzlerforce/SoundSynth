#include <iostream>
using namespace std;

#include "olcNoiseMaker.h";

atomic<double> dFrequencyOutput = 0.0;

double makeNoise(double dTime) {
	double dOutput = sin(dFrequencyOutput * 2 * 3.14159 * dTime);
	dOutput += sin((dFrequencyOutput + 20.0) * 2 * 3.14159 * dTime);
	dOutput *= 1.0;

	return dOutput * 0.4;

	/*
	if(dOutput > 0.0) {
		return 0.2;
	} else {
		return -0.2;
	}
	*/
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

	double dOctaveBaseFrequency = 110.0;	// A2
	double d12thRoofOf2 = pow(2.0, 1.0 / 12.0); 

	while(1) {
		// Add a keyboard like a piano
		// \xbcL is comma
		// \xbe is period
		bool bKeyPressed = false;
		for (int k = 0; k < 15; k++) {
			if(GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\xbe"[k])) & 0x8000) {
				dFrequencyOutput = dOctaveBaseFrequency * pow(d12thRoofOf2, k);
				bKeyPressed = true;
			} 
		}

		if(!bKeyPressed) {
			dFrequencyOutput = 0.0;
		}
	}

	return 0;
}