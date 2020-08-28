#include "stable_match.hpp"

int main()
{
	//vector<vector<string>> players{
	//	{ "A", "X", "W", "Z", "Y" },
	//	{ "B", "Z", "Y", "X", "W" },
	//	{ "C", "Y", "X", "Z", "W" },
	//	{ "D", "X", "Z", "W", "Y" }
	//};
	//vector<vector<string>> teams{
	//	{ "W", "B", "D", "C", "A" },
	//	{ "X", "B", "D", "A", "C" },
	//	{ "Y", "A", "B", "C", "D" },
	//	{ "Z", "B", "C", "D", "A" }
	//};
	vector<vector<string>> companies{
		{ "A", "V", "W", "X", "Y", "Z" },
		{ "B", "W", "X", "Y", "Z", "V" },
		{ "C", "W", "Y", "Z", "X", "V" },
		{ "D", "X", "Z", "V", "W", "Y" },
		{ "E", "V", "X", "Z", "W", "Y" }
	};
	vector<vector<string>> interns{
		{ "V", "B", "E", "A", "C", "D" },
		{ "W", "A", "B", "C", "D", "E" },
		{ "X", "A", "B", "C", "D", "E" },
		{ "Y", "C", "B", "D", "A", "E" },
		{ "Z", "E", "C", "A", "B", "D" }
	};

	set<pair<string, string>> res = stable_match(companies, interns);

	return 0;
}

set<pair<string, string>> stable_match(const vector<vector<string>>& first,
						  const vector<vector<string>>& second)
{
	unordered_map<string, string> first_pair = make_pair_map(first);
	unordered_map<string, vector<string>> first_prefer = make_preference_map(first);
	unordered_map<string, string> second_pair = make_pair_map(second);
	unordered_map<string, vector<string>> second_prefer = make_preference_map(second);

	//print_sv_tables(first_prefer);
	//print_sv_tables(second_prefer);

	//print_ss_tables(first_pair);
	//print_ss_tables(second_pair);

	set<pair<string, string>> res = stable_match(first_prefer, first_pair,
											     second_prefer, second_pair);
	//cout << res.empty() << endl;
	for (auto elem : res) {
		cout << elem.first << "\t" << elem.second << endl;
	}

	return res;
}

//STABLE MATCH
//TODO: support template
set<pair<string, string>> stable_match(
	unordered_map<string, vector<string>>& first_prefer,
	unordered_map<string, string>& first_pair,
	unordered_map<string, vector<string>>& second_prefer,
	unordered_map<string, string>& second_pair)
{
	set<pair<string, string>> pair_set;
	queue<string> purposers;
	for (auto elem : first_pair) {
		purposers.push(elem.first);
	}

	while (!purposers.empty()) {
		string curr_f = purposers.front();

		for (auto curr_s : first_prefer[curr_f]) {
			if (second_pair[curr_s] == "") {
				second_pair[curr_s] = curr_f;
				first_pair[curr_f] = curr_s;
				pair_set.insert(make_pair(curr_f, curr_s));
				purposers.pop();
				break;
			}
			else {
				if (prefers_p(second_prefer[curr_s], curr_f,
			 		 second_pair[curr_s])) {
					string fiance = second_pair[curr_s];
					pair_set.erase(pair<string, string> { fiance, curr_s });
					first_pair[fiance] = "";
					purposers.push(fiance);

					second_pair[curr_s] = curr_f;
					first_pair[curr_f] = curr_s;
					pair_set.insert(make_pair(curr_f, curr_s));
					purposers.pop();
					break;
				}
				else { }
			}

			//print_ss_tables(first_pair);
			//print_ss_tables(second_pair);
		}
	}

	return pair_set;
}
