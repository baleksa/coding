#include "csv.hpp"

bool Csv::getline(string &str)
{
	char c;

	for (line = ""; fin.get(c) && !endofline(c);)
		line += c;

	split();
	str = line;
	return !fin.eof();
}

int Csv::endofline(char c)
{
	bool eol;
	eol = (c == '\r' || c == '\n');
	if (c == '\r') {
		fin.get(c);
		if (!fin.eof() && c != '\n')
			fin.putback(c);
	}

	return eol;
}

string Csv::getfield(int n)
{
	if (n < 0 || n >= nfield)
		return "";
	return field[n];
}

const string &Csv::operator[](const int i)
{
	if (i < 0 && i >= nfield) {
		cout << "Index out of bounds!";
		exit(0);
	}

	return field[i];
}

int Csv::split(void)
{
	nfield = 0;
	if (line.length() == 0)
		return 0;
	string fld;
	int j;
	int i = 0;
	do {
		fld = "";
		if (i < line.length() && line[i] == '"') {
			j = advquote(line, fld, ++i);
		} else {
			j = advplain(line, fld, i);
		}
		if (nfield >= field.size())
			field.push_back(fld);
		else
			field[nfield] = fld;
		++nfield;
		i = j + 1;
	} while (j < line.length());
	return nfield;
}

int Csv::advplain(const string &line, string &fld, int i)
{
	int k = line.find_first_of(fieldsep, i);
	if (k >= line.length())
		k = line.length();
	fld = string(line, i, k - i);
	return k;
}

int Csv::advquote(const string &line, string &fld, int pos)
{
	int k = 0;
	for (int i = pos; i < line.length(); ++i) {
		if (line[i] == '"' && line[++i] != '"') {
			k = line.find_first_of(fieldsep, i);
			if (k >= line.length()) {
				k = line.length();
			}
			fld += string(line, i, k - i);
			break;
		}
		fld += line[i];
	}
	return k;
}
