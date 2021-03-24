#include <iostream>
//#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int minWaitingTime(int n, int arrvalTime[], int completeTime[]) {
	// YOUR CODE HERE
	struct cus {
		int tt;
		int arr;
		int com;
		cus(int tt, int arr, int com) { this->tt = tt;  this->arr = arr; this->com = com; }
	};
	vector<cus> CUS;
	for (int i = 1; i < n; i++) {
		cus newcus(i,arrvalTime[i], completeTime[i]);
		CUS.push_back(newcus);
	}
	vector<int> time;
	vector<int> result;
	int mintime = completeTime[0];
	result.push_back(0);
	while (CUS.size() > 0) {
		int N = CUS.size();
		for (int j = 0; j < N; j++) {
			if (CUS[j].arr <= mintime) {
				time.push_back(CUS[j].tt);
				CUS.erase(CUS.begin() + j);

				N = CUS.size();
				j -= 1;
			}
		}
		while (time.size() > 0) {
			int t = 0;
			int nho = time[0];
			int M = time.size();
			for (int i = 0; i < M; i++) {
				if (completeTime[time[i]] < nho) {
					nho = completeTime[time[i]];
					t = i;
				}
			}
			mintime += completeTime[time[t]];
			result.push_back(time[t]);
			time.erase(time.begin() + t);
			int N = CUS.size();
			for (int j = 0; j < N; j++) {
				if (CUS[j].arr <= mintime) {
					time.push_back(CUS[j].tt);
					CUS.erase(CUS.begin() + j);
					N = CUS.size();
					j -= 1;
				}
			}
		}

		if (CUS.size() > 0) {
			int mint = CUS[0].arr;
			int m = 0;
			int L = CUS.size();
			for (int i = 0; i < L; i++) {
				if (CUS[i].arr < mint) { mint = CUS[i].arr; m = i; }
			}
			result.push_back(CUS[m].tt);
			mintime += CUS[m].com;
			CUS.erase(CUS.begin() + m);
		}

	}
	mintime = completeTime[result.front()];
	for (int i = 1; i < result.size(); i++) {
		mintime += completeTime[result[i]];
		if (arrvalTime[result[i]] < arrvalTime[0]) 
			mintime += completeTime[0];
		else if (arrvalTime[result[i]] - arrvalTime[0] < completeTime[0]) { 
			mintime += completeTime[0] - (arrvalTime[result[i]] - arrvalTime[0]); }

		int j = i - 1;
		while (j >= 1) {
			if (arrvalTime[result[i]] < arrvalTime[result[j]])
				mintime += completeTime[result[j]];
			else if (arrvalTime[result[i]] - arrvalTime[result[j]] < completeTime[result[j]]) {
				mintime += completeTime[result[j]] - (arrvalTime[result[i]] - arrvalTime[result[j]]);
			}
			j--;
		}
	}
	
	return mintime;
}
int main()
{
	int n = 4;
	int arrvalTime[] = { 0, 4, 2, 5 };
	int completeTime[] = { 4, 2, 3, 4 };

	cout << minWaitingTime(n, arrvalTime, completeTime);



   return 0;
}
