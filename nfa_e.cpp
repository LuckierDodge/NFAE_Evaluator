#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void epsilon_moves(vector<int>&, vector<vector<vector<int>>>& transitions);
vector<int> get_epsilon_moves(int current_state, vector<int> current_states, vector<vector<vector<int>>>& transitions); 

int main() {
	//Read from File
	string buffer1;
	string buffer2;
	cin >> buffer1 >> buffer2;
	int nstates = stoi(buffer1, nullptr);
	int naccepting = stoi(buffer2, nullptr);

	buffer1 = "";
	buffer2 = "";

	int accepting[naccepting];

	for (int i = 0; i < naccepting; i++) {
		cin >> buffer1;
		accepting[i] = stoi(buffer1, nullptr);
	}

	buffer1 = "";
	vector<vector<vector<int>>> transitions(nstates, vector<vector<int>> (3, vector<int> (0, 0)));
	for (int j = 0; j < nstates; j++) {
		// For input 'a'
		cin >> buffer1;
		int ntransistions = stoi(buffer1, nullptr);
		for (int k = 0; k < ntransistions; k++) {
			cin >> buffer2;
			transitions[j][0].push_back(stoi(buffer2, nullptr));
			buffer2 = "";
		}
		buffer1 = "";

		// For input 'b'
		cin >> buffer1;
		ntransistions = stoi(buffer1, nullptr);
		for (int k = 0; k < ntransistions; k++) {
			cin >> buffer2;
			transitions[j][1].push_back(stoi(buffer2, nullptr));
			buffer2 = "";
		}


		// For input 'e'
		cin >> buffer1;
		ntransistions = stoi(buffer1, nullptr);
		for (int k = 0; k < ntransistions; k++) {
			cin >> buffer2;
			transitions[j][2].push_back(stoi(buffer2, nullptr));
			buffer2 = "";
		}
	}

	buffer1 = "";
	int nwords;
	cin >> buffer1;
	nwords = stoi(buffer1, nullptr);

	string words[nwords];

	for (int k = 0; k < nwords; k++) {
		cin >> words[k];
	}

	// Print Table
	cout << "    | a b e" << endl;
	cout << "----+------" << endl;

	for (int i = 0; i < nstates; i++) {
		bool accepts = false;

		for (int j = 0; j < naccepting; j++)
			accepts = (accepting[j] == i ? true : accepts);

		cout << (accepts ? "* " : "  ") << i << " | {";
		for(vector<int>::iterator it = transitions[i][0].begin(); it != transitions[i][0].end(); ++it)
			cout << " " << *it;
		cout << "} {";
		for(vector<int>::iterator it = transitions[i][1].begin(); it != transitions[i][1].end(); ++it)
			cout << " " << *it;
		cout << "} {";
		for(vector<int>::iterator it = transitions[i][2].begin(); it != transitions[i][2].end(); ++it)
			cout << " " << *it;
		cout << "}" << endl;
	}

	//Process Words
	for (int w = 0; w < nwords; w++) {
		string word = words[w];
		vector<int> current_states(1, 0);
		
		current_states = get_epsilon_moves(0, current_states, transitions);

		for ( string::iterator it=word.begin(); it != word.end(); ++it) {
			vector<int> new_states;
			for (vector<int>::iterator csit = current_states.begin(); csit != current_states.end(); ++csit) {
				if (*it == 'a') {
					for (vector<int>::iterator vit = transitions[*csit][0].begin(); vit != transitions[*csit][0].end(); ++vit)
						if ( find(new_states.begin(), new_states.end(), *vit) == new_states.end() ) {
							new_states.push_back(*vit);
						}
				} else {
					for (vector<int>::iterator vit = transitions[*csit][1].begin(); vit != transitions[*csit][1].end(); ++vit)
						if ( find(new_states.begin(), new_states.end(), *vit) == new_states.end() ) {
							new_states.push_back(*vit);
						}
				}
				
				vector<int> temp_states;
				for (vector<int>::iterator nit = new_states.begin(); nit != new_states.end(); ++nit) {
					vector<int> buffer = get_epsilon_moves(*nit, new_states, transitions);
					for (vector<int>::iterator bit = buffer.begin(); bit != buffer.end(); ++bit) {
						if ( find(temp_states.begin(), temp_states.end(), *bit) == temp_states.end() ) {
							temp_states.push_back(*bit);
						}
					}
				}
				new_states = temp_states;
			}
			current_states = new_states;
		}

		bool accepts = false;
		for (vector<int>::iterator csit = current_states.begin(); csit != current_states.end(); ++csit) 
			for (int a = 0; a < naccepting; a++)
				accepts = (accepting[a] == *csit ? true: accepts);
		cout << word << (accepts ? " accepted" : " rejected") << endl;
	}
}

vector<int> get_epsilon_moves(int current_state, vector<int> current_states, vector<vector<vector<int>>>& transitions) {
	vector<int> e_states;
	if (transitions[current_state][2].empty()) {
		return current_states;
	}
	for (vector<int>::iterator eit = transitions[current_state][2].begin(); eit != transitions[current_state][2].end(); ++eit) {
		if ( find(current_states.begin(), current_states.end(), *eit) == current_states.end() ) {
			e_states.push_back(*eit);
		}
	}
	if (e_states.empty()) {
		return current_states;
	}

	current_states.insert(current_states.end(), e_states.begin(), e_states.end());

	vector<int> buffer;
	for (vector<int>::iterator sit = current_states.begin(); sit != current_states.end(); ++sit) {
		if (!transitions[*sit][2].empty()) {
			vector<int> temp_states = get_epsilon_moves(*sit, current_states, transitions);
			buffer.insert(buffer.end(), temp_states.begin(), temp_states.end());
		}
	}
	current_states.insert(current_states.end(), buffer.begin(), buffer.end());

	return current_states;
}
