#include <bits/stdc++.h>
#define frand(i_max) (float(rand() * i_max) / RAND_MAX)
using namespace std;
#define f_qel 0.01

class Neuron {
private:
public:
	int num;				// number of input synapses
	vector<float> inputs;
	vector<float> weights;
	float qel;	// = Quadratic Error Last

	float output;	
	Neuron(int k) {
		/*Initializing input vectors*/
		num = k;
		output = 0;
		inputs.resize(k); 	// What about initialization...
		weights.resize(k); 	// ...before constrctor???
		qel = f_qel;		// ...
		for (int i = 0; i < k; ++i) {
			weights[i] = frand(0.1) - 0.05;		// [-0.05: +0.05]
		}
		/*----------------------*/
	}
	inline float activate(float x)
	{
		/* treshold function 
		if (x > 0)		return 1;
		else			return 0;
		*/
		/* sigmoid */
		return x / (abs(x) + 0.1);
	}
	// inline float derivative(float x)...

	float summ() {
		float s = 0;
		for (int i = 0; i < num; ++i)
			s += inputs[i] * weights[i];
		return activate(s);
		// NB: output!!!
	}

	/*float learn()
	// NB: write all deltas to class members (e.q. qed)!!!
	{
		for (int i = 0; i < num; ++i)
		// iterating inputs
		{
			;
		}
	}*/
	
};
