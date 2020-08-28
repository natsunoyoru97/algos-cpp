#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <iterator>
using namespace std;

unordered_map<string, string> make_pair_map(const vector<vector<string>>&);
unordered_map<string, vector<string>> make_preference_map(const vector<vector<string>>&);

set<pair<string, string>> stable_match(const vector<vector<string>>&,
						  const vector<vector<string>>&);
set<pair<string, string>> stable_match(
	unordered_map<string, vector<string>>&,
	unordered_map<string, string>&,
	unordered_map<string, vector<string>>&,
	unordered_map<string, string>&);

bool prefers_p(const vector<string>& vec,
			   const string& purposer, const string& fiance);

//the unordered map：first->second
unordered_map<string, string> make_pair_map(const vector<vector<string>>& vec)
{
	unordered_map<string, string> res;
	if (vec.empty() || vec[0].size() <= 1) return res;

	int m = vec.size();
	for (int i = 0; i < m; ++i) {
		res[vec[i][0]] = "";
	}

	return res;
}

unordered_map<string, vector<string>> make_preference_map(const vector<vector<string>>& vec)
{
	unordered_map<string, vector<string>> res;
	if (vec.empty() || vec[0].size() <= 1) return res;

	int m = vec.size(), n = vec[0].size();
	for (int i = 0; i < m; ++i) {
		for (int j = 1; j < n; ++j) {
			res[vec[i][0]].push_back(vec[i][j]);
		}
	}

	return res;
}

//TODO: support corner case: first.size() != second.size()
bool prefers_p(const vector<string>& vec,
			   const string& purposer, const string& fiance)
{
	int m = vec.size();
	int p = 0, f = 0;
	for ( ; p < m && vec[p] != purposer; ++p) { }
	for ( ; f < m && vec[f] != fiance; ++f)   { }

	return p < f;
}


/************************ NOTES: DEBUGGING FUNCTIONS ****************************/
void print_sv_tables(unordered_map<string, vector<string>>& table)
{
	if (table.empty()) cout << "TABLE IS EMPTY" << endl;

	for (auto elem : table) {
		cout << "first: " << elem.first << "\t";
		cout << "second: ";
		for (auto s : elem.second) {
			cout << s << "\t";
		}
		cout << endl;
	}
}

void print_ss_tables(unordered_map<string, string>& table)
{
	if (table.empty()) cout << "TABLE IS EMPTY" << endl;
	
	for (auto elem : table) {
		cout << "first: " << elem.first << "\tsecond: " << elem.second << endl;
	}
	cout << "END" << endl;
}