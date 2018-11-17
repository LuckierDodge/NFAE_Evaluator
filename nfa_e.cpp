#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

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
	vector<int> transitions[nstates][3];
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
			cout << "} {" << *it;
		for(vector<int>::iterator it = transitions[i][2].begin(); it != transitions[i][2].end(); ++it)
			cout << " " << *it;
		cout << "}" << endl;
	}

	//Process Words
	for (int w = 0; w < nwords; w++) {
		string word = words[w];
		vector<int> current_states(1, 0);

		vector<int> e_states;
		bool modified;
		do {
			modified = false;
			for (vector<int>::iterator csit=current_states.begin(); csit != current_states.end(); ++csit)
				for (vector<int>::iterator eit = transitions[*csit][2].begin(); eit != transitions[*csit][2].end(); ++eit)
					if (find(current_states.begin(), current_states.end(), *eit) == current_states.end()) {
						e_states.push_back(*eit);
						modified = true;
					}
			current_states.insert(current_states.end(), e_states.begin(), e_states.end());
		} while (modified);


		for ( string::iterator it=word.begin(); it != word.end(); ++it) {
			vector<int> new_states;
			for (vector<int>::iterator csit = current_states.begin(); csit != current_states.end(); ++csit) {
				if (*it == 'a')
					for (vector<int>::iterator vit = transitions[*csit][0].begin(); vit != transitions[*csit][0].end(); ++vit)
						new_states.push_back(*vit);
				else
					for (vector<int>::iterator vit = transitions[*csit][1].begin(); vit != transitions[*csit][1].end(); ++vit)
						new_states.push_back(*vit);
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
