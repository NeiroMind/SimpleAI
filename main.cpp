#include "lib.cpp"
#define in fin
#define out cout

#define start_qed 0.01
#define start_dw 0.1
#define speed 0.01
#define qe_tresh 0.001

fstream fin("text.in");

float net_try(Neuron& neuron)
// It reads input from stream (only one time), give some stats and return right answer (from stream too)
{
	float na;
	int k = neuron.num;
	out << "------------------------------\n" << "Enter " << k << " inputs:" << endl;
	for (int i = 0; i < k; ++i)
		in >> neuron.inputs[i];

	out << endl << "Entered values: \t";
	for (int i = 0; i < k; ++i)
		out << neuron.inputs[i] << ' ';

	out << endl << "Net weights are: \t";
	for (int i = 0; i < k; ++i)
		out << neuron.weights[i] << ' ';

	na = neuron.summ();
	out << endl << "Net answer is:  \t" << na << endl;

	out << "Right answer?" << endl;
	float ra;
	in >> ra;
	out << endl << "Entered [right] answer: " << ra << endl;
	return ra;
}

inline float get_qe(float na, float ra) // Small lifehack...
{ return (na - ra) * (na - ra); }

void net_learn(Neuron& neuron) {
	vector<float> dw(neuron.num, start_dw);		// weight deltas
	vector<float> qed(neuron.num, start_qed);	// = Quadratic Error Deltas
	
	float ra = net_try(neuron);
	float na = neuron.summ();
	vector<float> qel(neuron.num, get_qe(na, ra));	// tmp var
	float qec = qe_tresh + 1;								// Variable for current QE
	
	while (qec > qe_tresh)
	{
		for (int i = 0; i < neuron.num; ++i)
		// iterating inputs
		{
			/* changing weight */
			if (abs(dw[i]) > 0.0001)
				dw[i] = -speed * qed[i] * neuron.inputs[i] / dw[i];
			else dw[i] = 0;
			neuron.weights[i] += dw[i];
			/* getting error delta */
			float na = neuron.summ();
			float qen = get_qe(na, ra);
			qed[i] = qen - qel[i];
			qel[i] = qen;
			/*--------------------*/
		}
		qec = get_qe(neuron.summ(), ra);
		cout << qec << " " << neuron.weights[0] << " " << neuron.weights[1] << endl;
		int n; cin >> n;
	}
}

int main() {
	srand(1);
	Neuron n(2);
	net_learn(n);
	cout << "Second epoch!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
	net_learn(n);
	net_learn(n);
	return 0;
}
