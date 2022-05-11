#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Csv {
    public:
	Csv(istream &fin = cin, string sep = ",") : fin(fin), fieldsep(sep)
	{
	}
	bool getline(string &);
	string getfield(int n);
	int getnfield() const
	{
		return nfield;
	}
	const string &operator[](const int);

    private:
	istream &fin;
	string line;
	vector<string> field;
	int nfield;
	string fieldsep;

	int split(void);
	int endofline(char);
	int advplain(const string &line, string &fld, int);
	int advquote(const string &line, string &fld, int);
};
