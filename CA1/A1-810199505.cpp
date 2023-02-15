#include<iostream>
#include<vector>
#include<algorithm>
#include <sstream> 
#include<string>


using namespace std;

vector<string> primitive_input_getting() {
	vector<string>primitive_get;
	string temp_input;
	char c,garbage;
	vector<char>temp;
	do {
		getline(std::cin, temp_input);
		primitive_get.push_back(temp_input);
	} while (!temp_input.empty());
	return primitive_get;
}
void name_spliting(vector<string>& names, string name_str) {
	stringstream check1(name_str);
	string temp;
	while (getline(check1, temp, ' '))
	{
		names.push_back(temp);
	}
}
vector<vector<string>> spliting_inputs1(vector<string>primitive_get) {
	int input_num = primitive_get.size();
	vector<vector<string>>primitive_table;
	for (int i = 0; i <input_num; i++) {
		vector <string> tokens;
		stringstream check1(primitive_get[i]);
		string temp_save;
		while (getline(check1, temp_save, '|'))
		{
			tokens.push_back(temp_save);
		}
		primitive_table.push_back(tokens);
	}
	return primitive_table;
}
vector<vector<string>> spliting_inputs2(vector<vector<string>>primitive_table, vector<string>&names) {
	int c = primitive_table.size();
	for (int i = 0; i <c; i++) {
		vector <string> tokens;
		stringstream check1(primitive_table[i][0]);
		string temp_save;
		while (getline(check1, temp_save, ':'))
		{
			tokens.push_back(temp_save);
		}
		names.push_back(tokens[0]);
		primitive_table[i][0] = tokens[1];
	}
	return primitive_table;
}
vector<vector<int>> data_table_initillizing(int n) {
	vector<vector<int>>data_table(n);
	for (int i = 0; i < n; i++) {
		data_table[i].push_back(i);
		for (int j = 0; j < 3; j++) {
			data_table[i].push_back(0);
		}
	}
	return data_table;
}

vector<vector<int>> info_determine(string number, string status, vector<vector<int>>data_table) {
	int n = stoi(number);
	if (status == "YES")
		data_table[n][1] += 1;
	else if (status == "NO")
		data_table[n][2] += 1;
	else
		data_table[n][3] += 1;
	return data_table;
}

vector<vector<int>> info_extracing(vector<vector<int>>data_table, vector<vector<string>>table) {
	int c = table.size();
	for (int i = 0; i < c; i++) {
		int length = table[i].size();
		for (int j = 0; j < length; j++) {
			vector<string>temp_tokens;
			stringstream check1(table[i][j]);
			string temp_save;
			while (getline(check1, temp_save, ' ')) {
				temp_tokens.push_back(temp_save);
			}
			data_table = info_determine(temp_tokens[0], temp_tokens[1], data_table);
		}
	}
	return data_table;
}

vector<vector<int>> data_table_fixing(int n, int member_num, vector<vector<int>>data_table) {
	for (int i = 0; i < n; i++) {
		int if_fixer = member_num - (data_table[i][1] + data_table[i][2]);
		data_table[i][3] = if_fixer;
	}
	return data_table;
}

void completing_names(vector<string>all_names, vector<string>&input_names) {
	int member_num = all_names.size();
	int length = input_names.size();
	for (int i = 0; i < member_num; i++) {
		int existence_check = 0;
		for (int j = 0; j < length; j++) {
			if (input_names[j] == all_names[i])
				existence_check += 1;
		}
		if (existence_check == 0)
			input_names.push_back(all_names[i]);
	}
}
vector<vector<int>> replacing(vector<vector<int>>data_table, int i, int j) {
	int a = data_table[i][j];
	data_table[i][j] = data_table[i + 1][j];
	data_table[i + 1][j] = a;
	return data_table;
}

vector<vector<int>> sorting(vector<vector<int>>data_table, int n) {
	for (int i = 0; i < n; i++) {
		for (int i = 0; i < n - 1; i++) {
			if (data_table[i][2] > data_table[i + 1][2]) {
				data_table = replacing(data_table, i, 0);
				data_table = replacing(data_table, i, 1);
				data_table = replacing(data_table, i, 2);
				data_table = replacing(data_table, i, 3);
			}
			else if (data_table[i][2] == data_table[i + 1][2] && data_table[i][3] > data_table[i + 1][3]) {
				data_table = replacing(data_table, i, 0);
				data_table = replacing(data_table, i, 1);
				data_table = replacing(data_table, i, 2);
				data_table = replacing(data_table, i, 3);
			}
		}
	}
	return data_table;
}
vector<vector<int>> name_printting_checker(int n, int member_num) {
	vector<vector<int>>print_checker(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < member_num; j++) {
			print_checker[i].push_back(0);
		}
	}
	return print_checker;

}
vector<vector<int>> yes_no_printing(vector<vector<string>>table, vector<string>all_names, vector<string>names, vector<vector<int>>& print_checker, string determiner, int slot_number) {
	int length = table.size();
	vector<string>temp_names;
	for (int i = 0; i < length; i++) {
		int len = table[i].size();
		for (int j = 0; j < len; j++) {
			if (table[i][j] == determiner) {
				temp_names.push_back(names[i]);
				print_checker[slot_number][i] = 1;
			}
		}
	}
	for (int j = 0; j < all_names.size(); j++) {
		int exist_check = 0;
		for (int k = 0; k < temp_names.size(); k++) {
			if (all_names[j] == temp_names[k])
				exist_check += 1;
		}
		if (exist_check != 0)
			cout << " " << all_names[j] ;
	}
	cout << endl;
	return print_checker;
}
void if_printing(vector < string > all_names, vector<string>input_names, vector<vector<int>>print_checker, int n, int number) {
	vector<string>if_names;
	for (int i = 0; i < all_names.size(); i++) {
		if (print_checker[number][i] == 0) {
			if_names.push_back(input_names[i]);
		}
	}
	for (int j = 0; j < all_names.size(); j++) {
		int exist_check = 0;
		for (int k = 0; k < if_names.size(); k++) {
			if (all_names[j] == if_names[k])
				exist_check += 1;
		}
		if (exist_check != 0)
			cout << " " << all_names[j];
	}
	cout << endl;
}
vector<vector<int>> printing_output(vector<vector<int>>data_table, vector<vector<string>>table, vector<string>names, vector<string>all_names, int n, int row_number) {
	int member_num = names.size();
	vector<vector<int>>print_checker = name_printting_checker(n, member_num);
	cout << "Time slot " << data_table[row_number][0] << ":" << endl;
	string slot_num = to_string(data_table[row_number][0]);
	string yes_str = slot_num + " " + "YES";
	string no_str = slot_num + " " + "NO";
	cout << "YES:";
	yes_no_printing(table, all_names, names, print_checker, yes_str, data_table[row_number][0]);
	cout << "NO:";
	yes_no_printing(table, all_names, names, print_checker, no_str, data_table[row_number][0]);
	cout << "IF_NECESSARY:";
	if_printing(all_names, names, print_checker, n, data_table[row_number][0]);
	cout << "###" << endl;
	return print_checker;
}
void three_best_finder(vector<vector<int>>data_table, vector<vector<string>>table, vector<vector<int>>print_checker, vector<string>names, vector<string>all_names, int n) {
	data_table = sorting(data_table, n);
	print_checker = printing_output(data_table, table, names, all_names, n, 0);
	print_checker = printing_output(data_table, table, names, all_names, n, 1);
	print_checker = printing_output(data_table, table, names, all_names, n, 2);
}

int main() {
	string temp_str;
	int slot_num;
	getline(cin, temp_str);
	slot_num = stoi(temp_str);
	getline(cin, temp_str);
	vector<string>all_names;
	vector<string>input_names;
	name_spliting(all_names, temp_str);
	vector<vector<int>>print_checker;
	vector<string>primitive_get = primitive_input_getting();
	vector<vector<string>>primitive_table = spliting_inputs1(primitive_get);
	primitive_table.pop_back();
	primitive_table = spliting_inputs2(primitive_table, input_names);
	vector<vector<int>>data_table = data_table_initillizing(slot_num);
	data_table = info_extracing(data_table, primitive_table);
	data_table = data_table_fixing(slot_num, all_names.size(), data_table);
	completing_names(all_names, input_names);
	three_best_finder(data_table, primitive_table, print_checker, input_names, all_names, slot_num);
}