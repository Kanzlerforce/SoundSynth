#include <iostream>
using namespace std;

#include "olcNoiseMaker.h";

double w(double dHertz) {
	return dHertz * 2.0 * PI;
}


double osc(double dHertz, double dTime, int nType) {
	switch (nType) {
	case 0: // Sine wave
		return sin(w(dHertz) * dTime);
	case 1: // Square wave
		return sin(w(dHertz) * dTime) > 0.0 ? 1.0 : -1.0;
	case 2: // Triangle wave
		return asin(sin(w(dHertz) * dTime)) * (2.0 / PI);
	default:
		return 0.0;
	}
}

atomic<double> dFrequencyOutput = 0.0;
double dOctaveBaseFrequency = 110.0;	// A2
double d12thRoofOf2 = pow(2.0, 1.0 / 12.0);

double makeNoise(double dTime) {
	double dOutput = osc(dFrequencyOutput, dTime, 0);
	
	return dOutput * 0.4;
	
}

int main() {
	wcout << "Synthesizer Part 1" << endl;

	// Get all sound hardware
	vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

	// Display findings
	for (auto d : devices) wcout << "Found Output Device: " << d << endl;

	// Display a keyboard
	wcout << endl <<
		"|   |   |   |   |   | |   |   |   |   | |   | |   |   |   |" << endl <<
		"|   | S |   |   | F | | G |   |   | J | | K | | L |   |   |" << endl <<
		"|   |___|   |   |___| |___|   |   |___| |___| |___|   |   |__" << endl <<
		"|     |     |     |     |     |     |     |     |     |     |" << endl <<
		"|  Z  |  X  |  C  |  V  |  B  |  N  |  M  |  ,  |  .  |  /  |" << endl <<
		"|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|" << endl << endl;

	// Create sound machine
	// device, sample rate, channels, and two magic myster numbers
	olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512);

	// Link noise function with sound machine
	sound.SetUserFunction(makeNoise);


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