#include <iostream>
//#include <algorithm>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
int query(string instruction)
{
	//CREATE A VECTOR "Request" TO STORE REQUEST.
	vector<string> Request;
	//PUSH PARAMETERS OF REQUEST TO VECTOR "Request".
	istringstream str(instruction);
	while (!str.eof())
	{
		string tmp;
		str >> tmp;
		if (tmp != "")
			Request.push_back(tmp);
	}
	//CREATE A VARIABLE INT "nParameter" TO STORE THE NUMBER OF PARAMETERS INT THE REQUEST.
	size_t nParameter = Request.size();
	size_t nSpaces = count(instruction.begin(), instruction.end(), ' ');
	return nSpaces;
}
int main() {
	std::string abc = "Dinh Nhu Tan";
	cout << query(abc);
	return 0;
}