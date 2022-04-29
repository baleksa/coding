#include <cstdlib>
#include <iostream>
#include <deque>
#include <map>
#include <vector>

using namespace std;

const unsigned int MAXGEN = 10000;
const unsigned int NPREF = 2;
const string NONWORD = "\n";

typedef deque<string> Prefix;
map<Prefix, vector<string> > statetab;

void build(Prefix &prefix, istream &in);
void add(Prefix &prefix, const string &s);
void generate(int nwords);

int main(int argc, char *argv[])
{
	int nwords = MAXGEN;
	Prefix prefix;
	for (int i = 0; i < NPREF; ++i) {
		add(prefix, NONWORD);
	}

	build(prefix, std::cin);
	add(prefix, NONWORD);
	generate(nwords);
	return 0;
}

void build(Prefix &prefix, istream &in)
{
	string buf;

	while (in >> buf) {
		add(prefix, buf);
	}
}

void add(Prefix &prefix, const string &s)
{
	if (prefix.size() == NPREF) {
		statetab[prefix].push_back(s);
		prefix.pop_front();
	}
	prefix.push_back(s);
}

void generate(int nwords)
{
	Prefix prefix;

	for (int i = 0;  i < NPREF; ++i) {
		add(prefix, NONWORD);
	}

	for (int i = 0; i < nwords; ++i) {

		vector<string> &suffixes = statetab[prefix];
		std::vector<string>::size_type ind = random() % suffixes.size();
		string &word = suffixes[ind];

		if (word == NONWORD)
			break;

		std::cout << word << std::endl;

		prefix.pop_front();
		prefix.push_back(word);
	}
}
