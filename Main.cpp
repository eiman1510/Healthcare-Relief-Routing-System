#include<iostream>
#include<fstream>
#include<list>
#include<vector>
#include<string>
#include<stdio.h>
#include <sstream>

using namespace std;

class HospitalData
{
public:
	int Time;
	string name;
	HospitalData() { Time = 0; name = " "; };
	HospitalData(string n, int t) :Time(t), name(n) {}
	void display()
	{
		cout << name << " " << Time << " ";
	}
};

struct mypair
{
public:
	string prev;
	string current;
	mypair():prev(" "), current(" ") {}
	mypair(string a, string b) :prev(a), current(b) { }
};
class MinHeap
{
	HospitalData* data;
	int capacity;
	int current;

public:
	MinHeap()
	{
		data = nullptr;
		capacity = 0;
		current = 0;
	}
	MinHeap(int n)
	{
		data = new HospitalData[n];
		capacity = n;
		current = 0;
	}
	bool isEmpty() const
	{
		if (current == 0)
			return true;

		return false;
	}
	void ReheapUp(int root, int last) {
		int parent;
		if (last > root) {
			parent = (last - 1) / 2;
			if (data[parent].Time > data[last].Time) {
				swap(data[parent], data[last]);
				ReheapUp(root, parent);
			}
		}
	}

	void Insert(HospitalData newItem)
	{
		if (current < capacity) {
			current++;
			data[current - 1] = newItem;
			ReheapUp(0, current - 1);
		}
		else if (current == capacity)
		{
			capacity = capacity * 2;
			current++;
			data[current - 1] = newItem;
			ReheapUp(0, current - 1);
		}
	}

	void DeleteMin() {
		if (current > 0) {
			data[0] = data[current - 1];
			current--;

			ReheapifyMinHeap(0);
		}
	}

	void ReheapifyMinHeap(int root) {
		int leftChild = 2 * root + 1;
		int rightChild = 2 * root + 2;
		int smallest = root;

		if (leftChild < current && data[leftChild].Time < data[smallest].Time) {
			smallest = leftChild;
		}
		if (rightChild < current && data[rightChild].Time < data[smallest].Time) {
			smallest = rightChild;
		}

		if (smallest != root) {
			swap(data[root], data[smallest]);
			ReheapifyMinHeap(smallest);
		}
	}

	int getMin(string& s)
	{
		if (isEmpty())
		{
			cout << "The haep is empty!\n";
			return 0;
		}

		int min = data[0].Time;
		string temp = data[0].name;
		for (int i = 1; i < current; i++)
		{
			if (min > data[i].Time) {
				min = data[i].Time;
				temp = data[i].name;
			}
			else {
				min = min;
				temp = temp;
			}
		}
		s = temp;
		return min;
	}
	void changeVal(string s, int val, int v2, string n,mypair *&pL)
	{
		for (int i = 0; i < capacity; i++)
		{
			if (data[i].name == s)
			{
				if (s == "UN")
				{
					pL[i].prev = "-1";
					pL[i].current = s;
					return;
				}
				if (val + v2 <= data[i].Time && data[i].name!=n)
				{
					data[i].Time = val + v2;
					for (int j = 0; j < capacity + 1; j++)
					{
						if (pL[j].current == data[i].name)
						{
							pL[j].prev = n;
						}
					}
				}
			}
		}

	}
	void Display()
	{
		for (int i = 0; i < current; i++) {
			data[i].display();
			cout << endl;
		}
	}

};


int main()
{

	ifstream aoo("input.txt");
	ofstream jaoo("Text.txt");
	string s;
	while (!aoo.eof())
	{
		aoo >> s;
		if (s != "(" && s != ")" && s != "," && s != ".")
			jaoo << s << " ";

		if (s == ".")
			jaoo << endl;
	}



	vector<list<HospitalData>> complete;
	ifstream in("Text.txt");
	int total;
	in >> total;
	int j = 1, k = 0;
	for (int i = 0; i < j; ++i) {
		string dummyLine;
		getline(in, dummyLine);
	}
	MinHeap tL(total + 1);
	while (k < total + 1)
	{
		list<HospitalData> data;
		string line;
		getline(in, line);

		istringstream iss(line);
		string n;
		iss >> n;
		if (n == "UN") {
			HospitalData  h(n, 0);
			tL.Insert(h);
			data.push_back(h);
		}
		else {
			HospitalData  h(n, INT_MAX);
			tL.Insert(h);
			data.push_back(h);
		}
		int t;
		while (!iss.eof()) {
			iss >> n;
			iss >> t;
			HospitalData  h(n, t);
			data.push_back(h);
		}
		complete.push_back(data);
		k++;
	}
	mypair *pL=new mypair[total+1];
	int i = 0;
	for (auto& item1 : complete)
	{
		if (!item1.empty()) {
			pL[i].current = item1.front().name;
			pL[i].prev = "-1";
			i++;
		}
	}
	ofstream opt_d_in("optimalDistance.txt");
	while (!tL.isEmpty())
	{
		string n;
		int c = tL.getMin(n);
		opt_d_in << n << " " << c << endl;
		for (auto& item1 : complete)
		{
			if (!item1.empty()) {
				if (item1.front().name == n)
				{
					for (auto& item2 : item1)
					{
						tL.changeVal(item2.name, item2.Time, c, n, pL);
						
					}
				}

			}
		}

		tL.DeleteMin();
	}

	
	
	x:	int opt;
		cout << "Select any of the following options :\n1.Optimal time for specific hospital\n2.Optimal time for all hospitals\n3.Previose location of specific hospital\n4.Previous location of all hospitals\n5.Exit ";
		cin >> opt;
		if (opt == 1) {
	
			ifstream i_n("optimalDistance.txt");
			string input;
			cout << "Enter the hospital : ";
			cin.ignore();
			getline(cin, input);
			string a;
			int b;
			while (!i_n.eof())
			{
				i_n >> a;
				i_n >> b;
				if (a == input)
					cout << "Optimal time : " << b << endl;
			}
			cout << endl;
			goto x;
		}
		if (opt == 2)
		{
			ifstream i_nn("optimalDistance.txt");
			string aa;
			int bb;
			while (!i_nn.eof())
			{
				i_nn >> aa;
				i_nn >> bb;
				cout << "UN->" << aa << " Time : " << bb << endl;
			}
			cout << endl;
			goto x;
		}
		if (opt == 3)
		{
			string input;
			cout << "Enter the hospital: ";
			cin.ignore();
			getline(cin, input);
			for (int i = 0; i < total + 1; i++)
			{
				if (pL[i].current == input) {
					cout << pL[i].prev << " -> " << pL[i].current << endl;
				}
			}
			cout << endl;
			goto x;
		}
		if (opt == 4)
		{
			for (int i = 0; i < total + 1; i++)
			{

				cout << pL[i].prev << " -> " << pL[i].current << endl;

			}
			goto x;

		}
		if (opt == 5)
		{
			cout << "YOU EXITED" << endl;
			return 0;
		}


}


