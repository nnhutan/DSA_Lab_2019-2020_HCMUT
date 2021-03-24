#include <iostream>
#include <vector>
#include <string>
#include <sstream>
//#include <iterator>
//#include <exception>
#include <iomanip>
#include <time.h>
#include <ctime>
//#include <algorithm>
using namespace std;

#ifndef BUS_NODE
#define BUS_NODE
class Bus
{
private:
	string CODE;
	string LP;
	string CASE;
	int TIMEA;
	int TIMEB;
	friend class BusSystem;

public:
	Bus()
	{
		this->CODE = "";
		this->LP = "";
		this->CASE = "";
		this->TIMEA = 0;
		this->TIMEB = 0;
	}
	Bus(vector<string> Request, size_t nParameter)
	{
		this->CODE = Request[1];
		this->LP = Request[2];
		this->CASE = (nParameter == 6) ? Request[3] : "0";
		this->TIMEA = stoi(Request[nParameter - 2]);
		this->TIMEB = stoi(Request[nParameter - 1]);
	}
	~Bus() {}
};
#endif
#ifndef BUS_SYSTEM
#define BUS_SYSTEM
class BusSystem
{
private:
	vector<Bus> *BUS;
	size_t N;				 //THE MAXIMUM NUMBER OF TRIPS PER ROUTER.
	bool setNumberTripsflag; //1 IF THE NUMBER OF TRIPS PER ROUTER WAS BE SET
public:
	BusSystem()
	{
		this->BUS = new vector<Bus>();
		this->N = 0;
		this->setNumberTripsflag = 0;
	}
	~BusSystem()
	{
		this->BUS->clear();
		this->N = 0;
		this->setNumberTripsflag = 0;
	}
	string query(string instruction)
	{
		size_t nParameter = instruction.length();
		if (instruction[0] == ' ' || instruction[nParameter - 1] == ' ')
			return "-1";
		nParameter = instruction.find("  ");
		if (nParameter != string::npos)
			return "-1";
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
		nParameter = Request.size();
		//CREATE A VARIABLE STRING "command" TO STORE THE COMMAND OF THE REQUEST.
		string command = Request[0];
		//CHECK THE VALIDITY OF THE REQUEST
		if (command == "SQ")
		{
			if (Request[1].find_first_not_of("0123456789") != string::npos || nParameter != 2)
				return "-1";
		}
		else if (command == "INS")
		{
			if (Request[1].size() > 5)
				return "-1";
			else if (Request[2].size() > 10)
				return "-1";
			else if (nParameter != 6 && nParameter != 5)
				return "-1";
			else if (Request[nParameter - 2].find_first_not_of("0123456789") != string::npos)
				return "-1";
			else if (Request[nParameter - 1].find_first_not_of("0123456789") != string::npos)
				return "-1";
			else if (stoi(Request[nParameter - 2]) >= stoi(Request[nParameter - 1]))
				return "-1";
			else if (nParameter == 6)
			{
				if (Request[3] != "1" && Request[3] != "0")
					return "-1";
			}
		}
		else if (command == "DEL")
		{
			if (nParameter != 4 && nParameter != 3 && nParameter != 2)
				return "-1";
			if (Request[1].size() > 5)
				return "-1";
			if (nParameter == 3 || nParameter == 4)
			{
				if (Request[2].find_first_not_of("0123456789") != string::npos)
					return "-1";
				if (nParameter == 4)
				{
					if (Request[3].find_first_not_of("0123456789") != string::npos)
						return "-1";
					if (stoi(Request[2]) > stoi(Request[3]))
						return "-1";
				}
			}
		}
		else if (command == "CS" || command == "CE" || command == "GS" || command == "GE")
		{
			if (nParameter != 3 && nParameter != 4)
				return "-1";
			if (Request[1].size() > 5)
				return "-1";
			if (Request[2].find_first_not_of("0123456789") != string::npos)
				return "-1";
			if (nParameter == 4)
				if (Request[3] != "1" && Request[3] != "0")
					return "-1";
		}

		//PERFORM REQUEST
		//SET THE MAXIMUM NUMBER OF TRIPS PER ROUTER.
		if (command == "SQ")
		{
			if (this->setNumberTripsflag == 1)
				return "-1";
			this->N = stoi(Request[1]);
			this->setNumberTripsflag = 1;
			return "1";
		}
		if (this->setNumberTripsflag == 0)
			return "-1";
		//ADD A TRIP TO THE LIST
		else if (command == "INS")
		{ //INS 50 50D1-23342 1234 5678

			Bus newbus(Request, nParameter);
			//cout << "[" << newbus.TIMEA << "]" << endl;
			//VARIABLE INT "checkN" STORES THE CURRENT TRIP NUMBER OF THE ROUTE WITH CODE <CODE>.
			size_t checkN = 0;
			//VARIABLE BOOL "flag" TO CHECK ADDING THE TRIP TO THE LIST.
			bool flag = 1;
			size_t index = 0;
			bool flagIndex = 0;
			for (auto &it : *BUS)
			{
				if (newbus.CODE == it.CODE)
				{
					checkN++;
					if (newbus.TIMEA > it.TIMEA)
						index++;
					flagIndex = 1;
				}
				if (!flagIndex)
					index++;
				if ((newbus.LP == it.LP && newbus.TIMEA <= it.TIMEB) ||
					(newbus.LP != it.LP && newbus.CODE == it.CODE && newbus.TIMEA == it.TIMEA && newbus.CASE == it.CASE))
					flag = 0;
			}
			if (flag == 1 && checkN < this->N)
			{
				this->BUS->insert(this->BUS->begin() + index, newbus);
				checkN++;
				return to_string(checkN);
			}
			else
				return "-1";
			//cout << "[" << newbus.TIMEB << "]" << endl;
		}

		//DELETE A TRIP FROM THE LIST.
		else if (command == "DEL")
		{
			//DEL <CODE> [<TIME_A>[<TIME_B>]
			string CodeDel = Request[1];
			int TimeDelA = -1, TimeDelB = -1;
			if (nParameter == 3 || nParameter == 4)
			{
				TimeDelA = stoi(Request[2]);
				if (nParameter == 4)
					TimeDelB = stoi(Request[3]);
			}
			size_t nTripDele = 0;
			size_t indexBegin = 0;
			bool flag = 0;
			//cout << TimeDelA << " " << TimeDelB;
			for (auto &it : *BUS)
			{
				if (!flag)
					indexBegin++;
				if (it.CODE == CodeDel)
				{
					if (TimeDelA == -1 && TimeDelB == -1)
					{
						flag = 1;
						nTripDele++;
					}
					else if (TimeDelA != -1 && TimeDelB == -1)
					{
						if (it.TIMEA == TimeDelA)
						{
							flag = 1;
							nTripDele++;
						}
					}
					else if (TimeDelA != -1 && TimeDelB != -1)
					{
						if (it.TIMEA >= TimeDelA && it.TIMEA <= TimeDelB)
						{
							flag = 1;
							nTripDele++;
						}
					}
				}
			}
			if (flag)
				this->BUS->erase(this->BUS->begin() + indexBegin - 1, this->BUS->begin() + (indexBegin + nTripDele - 1));
			return to_string(nTripDele);
		}

		//RETURN THE NUMBER OF TRIPS THAT HAVE STARTED BUT HAVE NOT YET ARRIVED AT...
		//...THE BUS STOP OF THE ROUTE WITH CODE <CODE> AT THE CONSIDERED TIME <TIME>.
		else if (command == "CS")
		{
			//CS <CODE>	<TIME>[<CASE>]
			string CodeTrip = Request[1];
			int NowTime = stoi(Request[2]);
			string CaseCheck = "-1";
			if (nParameter == 4)
				CaseCheck = Request[3];
			int nTrips = 0;
			for (auto &it : *BUS)
				//cout << (*it).TIMEA << NowTime << (*it).TIMEB;
				if (it.CODE == CodeTrip)
				{
					if (it.TIMEA <= NowTime && it.TIMEB >= NowTime)
					{
						if (CaseCheck == "-1" || CaseCheck == it.CASE)
							nTrips++;
					}
				}
			return to_string(nTrips);
		}

		//RETURN THE NUMBER OF TRIPS THAT HAVE ENDED OF THE ROUTE WITH CODE <CODE> AT...
		//...THE CONSIDERED TIME <TIME>.
		else if (command == "CE")
		{
			string CodeTrip = Request[1];
			int NowTime = stoi(Request[2]);
			string CaseCheck = "-1";
			if (nParameter == 4)
				CaseCheck = Request[3];
			int nTrips = 0;
			for (auto &it : *BUS)
				if (it.CODE == CodeTrip)
				{
					if (it.TIMEB < NowTime)
					{
						if (CaseCheck == "-1" || CaseCheck == it.CASE)
							nTrips++;
					}
				}
			return to_string(nTrips);
		}

		//RETURN THE LICENSE PLATE OF THE BUS TRIP OF THE ROUTE WITH CODE <CODE> WHICH HAS...
		//... STARTED AT THE TIME CLOSEST TO THE CONSIDERED TIME <TIME>.
		else if (command == "GS")
		{
			string CodeTrip = Request[1];
			int NowTime = stoi(Request[2]);
			string CaseCheck = "-1";
			if (nParameter == 4)
				CaseCheck = Request[3];
			Bus target;
			bool flag = 1;
			for (auto &it : *BUS)
			{
				if (it.CODE == CodeTrip && it.TIMEA <= NowTime)
				{
					if (CaseCheck == "-1")
					{
						if (flag)
						{
							target = it;
							flag = 0;
						}
						else if ((NowTime - it.TIMEA) < (NowTime - target.TIMEA))
							target = it;
						else if ((NowTime - it.TIMEA) == (NowTime - target.TIMEA))
						{
							if (it.CASE == "0" && target.CASE == "1")
								target = it;
						}
					}
					else if (it.CASE == CaseCheck)
					{
						if (flag)
						{
							target = it;
							flag = 0;
						}
						else if ((NowTime - it.TIMEA) < (NowTime - target.TIMEA))
							target = it;
					}
				}
			}
			if (flag)
				return "-1";
			return target.LP;
		}

		//RETURN THE LICENSE PLATE OF THE BUS TRIP OF THE ROUTE WITH CODE <CODE> WHICH HAS...
		//... ENDED AT THE TIME CLOSEST TO THE CONSIDERED TIME <TIME>.
		else if (command == "GE")
		{
			string CodeTrip = Request[1];
			int NowTime = stoi(Request[2]);
			string CaseCheck = "-1";
			if (nParameter == 4)
				CaseCheck = Request[3];
			Bus target;
			bool flag = 1;
			for (auto &it : *BUS)
			{
				if (it.CODE == CodeTrip && it.TIMEB < NowTime)
				{
					if (CaseCheck == "-1")
					{
						if (flag)
						{
							target = it;
							flag = 0;
						}
						else if ((NowTime - it.TIMEB) < (NowTime - target.TIMEB))
							target = it;
						else if ((NowTime - it.TIMEB) == (NowTime - target.TIMEB))
						{
							if (it.CASE == "0" && target.CASE == "1")
								target = it;
							else if (it.CASE == target.CASE)
								target = (it.TIMEA > target.TIMEA) ? it : target;
						}
					}
					else if (it.CASE == CaseCheck)
					{
						if (flag)
						{
							target = it;
							flag = 0;
						}
						else if ((NowTime - it.TIMEB) < (NowTime - target.TIMEB))
							target = it;
						else if ((NowTime - it.TIMEB) == (NowTime - target.TIMEB))
							target = (it.TIMEA > target.TIMEA) ? it : target;
					}
				}
			}
			if (flag)
				return "-1";
			return target.LP;
		}
		//IF REQUEST IS NOT COMPLETED, RETURN "-1"
		return "-1";
	}
	void PrintBusSystem()
	{
		cout << setfill('=');
		cout << setw(40) << "=" << endl;
		cout << setfill(' ');
		cout << setw(5) << left << "TT";
		cout << setw(10) << left << "CODE";
		cout << setw(8) << left << "LP";
		cout << setw(5) << left << "CASE";
		cout << setw(6) << left << "TIMEA";
		cout << setw(6) << left << "TIMEB" << endl;
		cout << setfill('=');
		cout << setw(40) << "=" << endl;
		cout << setfill(' ');
		int i = 0;
		for (auto &it : *BUS)
		{
			cout << setw(5) << left << ++i;
			cout << setw(5) << left << it.CODE;
			cout << setw(14) << left << it.LP;
			cout << setw(4) << left << it.CASE;
			cout << setw(6) << left << it.TIMEA;
			cout << setw(6) << left << it.TIMEB << endl;
		}
		cout << setfill('=');
		cout << setw(40) << "=" << endl;
	}
};
#endif

int main()
{
	BusSystem *bs = new BusSystem();
	cout << bs->query("SQ 50") << endl;
	cout << bs->query("bug") << endl;
	cout << bs->query("INS 43 A0 1 24") << endl;
	cout << bs->query("INS 43 A0 0 30 35") << endl;
	cout << bs->query("INS 43 A1 1 2 2") << endl;  // invalid
	cout << bs->query("INS 43 A0 25 27") << endl;  // invalid
	cout << bs->query("INS 43 A0 1 1 27") << endl; // invalid
	cout << bs->query("INS 43 A1 1 1 24") << endl;
	cout << bs->query("INS 43 A1 1 25 35") << endl;
	cout << bs->query("INS 43 A0 0 40 50") << endl;
	cout << bs->query("INS 43 A0 0 50 60") << endl; // invalid
	cout << bs->query("INS 43 A0 0 51 60") << endl;
	cout << bs->query("INS 43 A1 1 36 45") << endl;
	cout << bs->query("INS 43 A1 1 46 50") << endl;
	cout << bs->query("INS 43 A1 1 55 70") << endl;

	cout << "\tB:" << endl;

	cout << bs->query("INS 43 B0 0 7 24") << endl;
	cout << bs->query("INS 43 B0 0 25 40") << endl;
	cout << bs->query("INS 43 B0 0 50 70") << endl;
	cout << bs->query("INS 43 B1 1 5 46") << endl;

	cout << "\tC:" << endl;

	cout << bs->query("INS 43 C0 0 5 40") << endl;
	cout << bs->query("INS 43 C1 1 7 40") << endl;

	cout << "\tD:" << endl;

	cout << bs->query("INS 43 D0 0 3 90") << endl;
	cout << bs->query("INS 43 D1 1 3 80") << endl;
	bs->PrintBusSystem();
	////	clock_t t = clock();
	////	BusSystem* bs = new BusSystem();
	////	cout << bs->query("SQ 500") << endl;						// 1
	////	cout << bs->query("INS 50 50D1-23362 1234 5678") << endl;	//1
	////	cout << bs->query("INS 50 50D1-23362 0 5679 6876") << endl;
	////	cout << bs->query("SQ 600") << endl;	//1
	////	cout << bs->query("INS 50 50D1-23344 0 1237 5680") << endl; //1
	////	cout << bs->query("INS 53 50D1-23345 0 1238 5681") << endl; //1
	////	cout << bs->query("INS 51 50D1-23348 0 1241 5684") << endl; //1
	////	cout << bs->query("INS 50 50D1-23346 1 1239 5682") << endl; //1
	////	cout << bs->query("INS 51 50D1-23347 1 1240 5683") << endl; //1
	////	cout << bs->query("INS 50 50D1-23349 0 1242 5685") << endl; //1
	////	cout << bs->query("INS 49 50D1-23350 0 1243 5686") << endl; //1
	////	cout << bs->query("INS 51 50D1-23357 0 1263 5786") << endl; //1
	////	cout << bs->query("INS 49 50D1-23359 0 1343 5676") << endl; //1
	////	cout << bs->query("INS 49 50D1-23361 0 1283 5621") << endl; //1
	////	cout << bs->query("INS 38 50D1-23547 0 2143 6686") << endl; //1
	////	cout << bs->query("INS 38 50D1-23430 0 1293 5616") << endl; //1
	////	cout << bs->query("INS 45 50D1-20650 0 3213 4686") << endl; //1
	////	cout << bs->query("INS 45 50D1-29350 0 1243 6786") << endl; //1
	////	cout << bs->query("INS 45 50D1-21350 0 1245 7686") << endl; //1
	////	cout << bs->query("INS 45 50D1-21350 0 1 1234") << endl;	//1
	////	cout << bs->query("CS 50 2134") << endl;					//1
	////	cout << bs->query("GE 50 2000") << endl;
	////
	////	bs->PrintBusSystem();
	////	cout << "[" << bs->query("DEL 38") << "]" << endl;
	////
	////	cout << bs->query("INS 49 50D1-23350 0 1243 5686") << endl; //1
	////	cout << bs->query("INS 51 50D1-23357 0 1263 5786") << endl; //1
	////	cout << bs->query("INS 49 50D1-23359 0 1343 5676") << endl; //1
	////	cout << bs->query("INS 49 50D1-23361 0 1283 5621") << endl; //1
	////	cout << bs->query("INS 38 50D1-23547 0 2143 6686") << endl; //1
	////	cout << bs->query("INS 38 50D1-23430 0 1293 5616") << endl; //1
	////	cout << bs->query("INS 49 50D1-23359 0 1343 5676") << endl; //1
	////	cout << bs->query("INS 49 50D1-23361 0 1283 5621") << endl; //1
	////	cout << bs->query("INS 38 50D1-23547 0 2143 6686") << endl; //1
	////	cout << bs->query("INS 38 50D1-23430 0 1293 5616") << endl; //1
	////	cout << bs->query("INS 45 50D1-20650 0 3213 4686") << endl; //1
	////	cout << bs->query("INS 45 50D1-29350 0 1243 6786") << endl; //1
	////	cout << bs->query("INS 45 50D1-21350 0 1245 7686") << endl; //1
	////	cout << bs->query("INS 45 50D1-21350 0 1 1234") << endl;	//1
	////	cout << bs->query("CS 50 2134") << endl;					//1
	////	cout << bs->query("GE 50 2000") << endl;
	////	cout << bs->query("INS 38 50D1-23430 0 1293 5616") << endl; //1
	////	cout << bs->query("INS 45 50D1-20650 0 3213 4686") << endl; //1
	////	cout << bs->query("INS 45 50D1-29350 0 1243 6786") << endl; //1
	////	cout << bs->query("INS 45 50D1-21350 0 1245 7686") << endl; //1
	////	cout << bs->query("INS 45 50D1-21350 0 1 1234") << endl;	//1
	////	cout << bs->query("CS 50 2134") << endl;					//1
	////	cout << bs->query("GE 50 2000") << endl;
	////
	////	cout << "{" << (float)(clock() - t) << "}";
	////	bs->PrintBusSystem();
	////	cout << "[" << bs->query("DEL 38") << "]" << endl;
	////	/*cout << bs->query("INS 50 50C1-1234 12 13") << endl;
	////	cout << bs->query("INS 50 50C1-1234 1 7 9") << endl;
	////	cout << bs->query("INS 50 50C1-1234 1 10 11") << endl;*/
	////	bs->PrintBusSystem();
	////	return 0;
	// BusSystem* bs = new BusSystem;
	// cout << "-----------------------Ravenclaw-----------------------" << endl;
	// cout << bs->query("SQ 50") << endl;
	// cout << bs->query("bug") << endl;
	// cout << bs->query("INS 43 A0 1 24") << endl;
	// cout << bs->query("INS 43 A0 0 30 35") << endl;
	// cout << bs->query("INS 43 A1 1 2 2") << endl; // invalid
	// cout << bs->query("INS 43 A0 25 27") << endl; // invalid
	// cout << bs->query("INS 43 A0 1 1 27") << endl; // invalid
	// cout << bs->query("INS 43 A1 1 1 24") << endl;
	// cout << bs->query("INS 43 A1 1 25 35") << endl;
	// cout << bs->query("INS 43 A0 0 40 50") << endl;
	// cout << bs->query("INS 43 A0 0 50 60") << endl; // invalid
	// cout << bs->query("INS 43 A0 0 51 60") << endl;
	// cout << bs->query("INS 43 A1 1 36 45") << endl;
	// cout << bs->query("INS 43 A1 1 46 50") << endl;
	// cout << bs->query("INS 43 A1 1 55 70") << endl;

	// cout << "\tB:" << endl;

	// cout << bs->query("INS 43 B0 0 7 24") << endl;
	// cout << bs->query("INS 43 B0 0 25 40") << endl;
	// cout << bs->query("INS 43 B0 0 50 70") << endl;
	// cout << bs->query("INS 43 B1 1 5 46") << endl;

	// cout << "\tC:" << endl;

	// cout << bs->query("INS 43 C0 0 5 40") << endl;
	// cout << bs->query("INS 43 C1 1 7 40") << endl;

	// cout << "\tD:" << endl;

	// cout << bs->query("INS 43 D0 0 3 90") << endl;
	// cout << bs->query("INS 43 D1 1 3 80") << endl;
	// bs->PrintBusSystem();
	// cout << bs->query("GE 43 36") << endl;
	// cout << "\n-----------------------Ravenclaw-----------------------" << endl;
	// cout << bs->query("DEL 43 7") << endl;
	// bs->PrintBusSystem();
	// cout << bs->query("DEL 43 25") << endl;
	// bs->PrintBusSystem();
	// cout << bs->query("DEL 43 25 70") << endl;

	// bs->PrintBusSystem();
}
