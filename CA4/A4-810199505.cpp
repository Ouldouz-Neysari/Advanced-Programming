#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<list>
#include<sstream>

using namespace std;

#define INK_FULL_VALUE 1000
#define PAPER_FULL_VALUE 100

class Order {
public:
	Order(vector<int>ink, int page, string pro, int num) {
		needed_colors = ink;
		needed_paper = page;
		priority = pro;
		number = num;
		lefted_paper = needed_paper;
	}
	int get_status() {
		return status;
	}
	vector<int> get_ink() {
		return needed_colors;
	}
	void change_paper(int speed) {
		lefted_paper -= speed;
		if (lefted_paper < 0)
			lefted_paper = 0;
	}
	int get_paper() {
		return needed_paper;
	}
	void set_needing_time(int time) {
		needing_time = time;
	}
	int get_needing_time() {
		return needing_time;
	}
	int get_lefted_paper() {
		return lefted_paper;
	}
	void change_status(int completing_time) {
		if (completing_time <= 1)
			status = 1;
		else
			status = 0;
	}
	int get_number() {
		return number;
	}
private:
	vector<int>needed_colors;
	int needed_paper;
	string priority;
	int number;
	int lefted_paper = needed_paper;
	int status = -1;
	int needing_time = 0;

};
class printer {
public:
	printer(int spd, int num, vector<int>inks, int ppr) {
		speed = spd;
		number = num;
		lefted_ink = inks;
		lefted_paper = ppr;
	}
	int get_next_ink() {
		return next_time_full_ink;
	}
	int get_next_paper() {
		return next_time_full_paper;
	}
	int get_ink_repair_time() {
		return time_for_ink_repair;
	}
	int get_paper_repair_time() {
		return time_for_paper_repair;
	}
	string get_status() {
		return status;
	}
	int get_complete_time() {
		return time_for_completer_order;
	}
	vector<int>get_lefted_ink() {
		return lefted_ink;
	}
	int get_lefted_paper() {
		return lefted_paper;
	}
	void make_full_ink() {
		time_for_ink_repair = 9;
		status = "not_available";
	}
	void make_full_paper() {
		time_for_paper_repair = 4;
		status = "not_available";
	}
	void ekhtesas_order(Order* matching_order) {
		order_ptr = matching_order;
	}
	void change_status(string state) {
		status = state;
	}
	int calculate_completeing_time() {
		float needing_time_fl = float(order_ptr->get_paper()) / float(speed);
		int needing_time_int = (order_ptr->get_paper()) / (speed);
		if (needing_time_fl != needing_time_int)
			needing_time_int += 1;
		time_for_completer_order = needing_time_int;
		order_ptr->set_needing_time(time_for_completer_order);
		return time_for_completer_order;
	}
	void change_complete_time(int i) {
		time_for_completer_order += i;
	}
	Order* get_order() {
		return order_ptr;
	}
	void change_ink_repair_time(int i) {
		time_for_ink_repair += i;
	}
	void charge_paper() {
		lefted_paper = PAPER_FULL_VALUE;
	}
	void charge_ink() {
		lefted_ink[0] = INK_FULL_VALUE;
		lefted_ink[1] = INK_FULL_VALUE;
		lefted_ink[1] = INK_FULL_VALUE;
		lefted_ink[1] = INK_FULL_VALUE;
	}
	void change_paper_repair_time(int i) {
		time_for_paper_repair += i;
	}
	void change_ink(vector<int>ink, int order_lefted_paper) {
		if (order_lefted_paper < speed) {
			lefted_ink[0] -= order_lefted_paper*ink[0];
			lefted_ink[1] -= order_lefted_paper*ink[1];
			lefted_ink[2] -= order_lefted_paper*ink[2];
			lefted_ink[3] -= order_lefted_paper*ink[3];

		}
		else {
			lefted_ink[0] -= speed*ink[0];
			lefted_ink[1] -= speed*ink[1];
			lefted_ink[2] -= speed*ink[2];
			lefted_ink[3] -= speed*ink[3];
		}
		if (lefted_ink[0] < 0)
			lefted_ink[0] = 0;
		if (lefted_ink[1] < 0)
			lefted_ink[1] = 0;
		if (lefted_ink[2] < 0)
			lefted_ink[2] = 0;
		if (lefted_ink[3] < 0)
			lefted_ink[3] = 0;


	}
	void change_paper(int order_lefted_paper) {
		if (order_lefted_paper < speed)
			lefted_paper -= order_lefted_paper;
		else
			lefted_paper -= speed;
		if (lefted_paper < 0)
			lefted_paper = 0;

	}
	int get_speed() {
		return speed;
	}
	int get_number() {
		return number;
	}
	int get_completing_time() {
		return time_for_completer_order;
	}
	void set_next_full_paper(int i) {
		next_time_full_paper = i;
	}
	void set_next_full_ink(int i) {
		next_time_full_ink = i;
	}

private:
	int next_time_full_paper = 0;
	int next_time_full_ink = 0;
	int number;
	int time_for_ink_repair = 0;
	int time_for_paper_repair = 0;
	string status = "idle";
	int speed;
	Order* order_ptr = NULL;
	int time_for_completer_order = 0;
	int lefted_paper = PAPER_FULL_VALUE;
	vector<int>lefted_ink = { INK_FULL_VALUE,INK_FULL_VALUE,INK_FULL_VALUE,INK_FULL_VALUE };
};
class Printing_house {
public:
	void add_printers(int speed) {
		int number = printers.size();
		vector<int>lefted_ink;
		lefted_ink.push_back(INK_FULL_VALUE);
		lefted_ink.push_back(INK_FULL_VALUE);
		lefted_ink.push_back(INK_FULL_VALUE);
		lefted_ink.push_back(INK_FULL_VALUE);
		printers.push_back(printer(speed, number + 1, lefted_ink, PAPER_FULL_VALUE));
		cout << "printer added successfully" << endl;
	}
	void add_order(int r, int g, int b, int x, int page_num, string priority) {
		int number = orders.size();
		orders.push_back(Order({ r,g,b,x }, page_num, priority, number + 1));
		cout << "order added successfully" << endl;
		if (priority == "regular")
			regular_que.push_back(Order({ r,g,b,x }, page_num, priority, number + 1));
		else
			vip_que.push_back(Order({ r,g,b,x }, page_num, priority, number + 1));
	}
	void advance_time(int time_step) {
		duration += time_step;
		passed_time += time_step;
	}
	int checking_printer_suitableness(int index) {
		vector<int>inks = printers[index].get_lefted_ink();
		int unwellness_checker = 0;
		if (inks[0] <= 0 || inks[1] <= 0 || inks[2] <= 0 || inks[3] <= 0)
			unwellness_checker += 2;

		if (printers[index].get_lefted_paper() <= 0)
			unwellness_checker += 1;

		return unwellness_checker;
	}
	void make_changes(int i) {
		vector<int>needed_ink = printers[i].get_order()->get_ink();
		printers[i].change_ink(needed_ink, printers[i].get_order()->get_lefted_paper());
		printers[i].change_paper(printers[i].get_order()->get_lefted_paper());
		printers[i].get_order()->change_paper(printers[i].get_speed());

	}
	void taking_order(int i) {
		int j = 0;
		while (j < vip_que.size()) {
			if (vip_que[j].get_status() == -1)
				break;
			j++;
		}
		if (j == vip_que.size()) {
			int k = 0;
			while (k < regular_que.size()) {
				if (regular_que[k].get_status() == -1)
					break;
				k++;
			}
			if (k < regular_que.size()) {
				printers[i].ekhtesas_order(&regular_que[k]);
				printers[i].change_status("busy");
				int completeing_time = printers[i].calculate_completeing_time();
				regular_que[k].change_status(completeing_time);
				make_changes(i);
			}

		}
		else {
			printers[i].ekhtesas_order(&vip_que[j]);
			printers[i].change_status("busy");
			int completeing_time = printers[i].calculate_completeing_time();
			vip_que[j].change_status(completeing_time);
			make_changes(i);
		}

	}
	void analyze_idle(int i) {
		taking_order(i);

	}
	int checking_printer_ink(int i) {
		vector<int>printer_inks = printers[i].get_lefted_ink();
		vector<int>order_ink = printers[i].get_order()->get_ink();
		int spd = printers[i].get_speed();
		if (printer_inks[0] < order_ink[0] * spd || printer_inks[1] < order_ink[1] * spd || printer_inks[2] < order_ink[2] * spd || printer_inks[3] < order_ink[3] * spd)
			return 1;
		else
			return 0;

	}
	void analyze_busy(int i) {
		if (printers[i].get_lefted_paper() < printers[i].get_speed()) {
			printers[i].make_full_paper();
			printers[i].change_status("not_available");
		}
		int ink_checker = checking_printer_ink(i);
		if (ink_checker == 1) {
			printers[i].make_full_ink();
			printers[i].change_status("not_available");
		}
		if (printers[i].get_status() == "busy") {
			if(printers[i].get_complete_time() <= 2)
				printers[i].get_order()->change_status(1);
			if (printers[i].get_complete_time() <= 1) {
				printers[i].change_complete_time(-1);
				make_changes(i);
				Order* matching_ord = printers[i].get_order();
				printers[i].change_status("idle");
				matching_ord->change_status(1);
				printers[i].ekhtesas_order(NULL);
			}
			else {
				printers[i].change_complete_time(-1);
				make_changes(i);
			}
		}
	}
	void analyze_unvailable(int i) {
		if (printers[i].get_next_ink() == 1) {
			printers[i].charge_ink();
			printers[i].change_status("busy");
			analyze_busy(i);
		}
		else if (printers[i].get_next_paper() == 1) {
			printers[i].charge_paper();
			printers[i].change_status("busy");
			analyze_busy(i);
		}
		else {
			int ink_repair = printers[i].get_ink_repair_time();
			int paper_repair = printers[i].get_paper_repair_time();
			if (ink_repair == 1 && paper_repair == 0) {
				printers[i].change_ink_repair_time(-1);
				printers[i].set_next_full_ink(1);
			}
			else if (paper_repair == 1 && ink_repair == 0) {
				printers[i].change_paper_repair_time(-1);
				printers[i].set_next_full_paper(1);
			}
			else if (ink_repair>0)
				printers[i].change_ink_repair_time(-1);
			else
				printers[i].change_paper_repair_time(-1);

		}


	}
	void analyze_printer(int i) {
		if (printers[i].get_status() == "idle")
			analyze_idle(i);
		else if (printers[i].get_status() == "busy")
			analyze_busy(i);
		else
			analyze_unvailable(i);

	}
	void advance_one_step() {
		for (int i = 0; i < printers.size(); i++)
			analyze_printer(i);
	}
	void advance() {
		for (int i = 0; i < duration; i++)
			advance_one_step();
	}
	void print_vip_que() {
		cout << "VIP orders queue: " << endl;
		for (int i = 0; i < vip_que.size(); i++) {
			if (vip_que[i].get_status() == -1)
				cout << vip_que[i].get_number() << " " << vip_que[i].get_paper() << endl;
		}
		cout << endl;
	}
	void print_reg_que() {
		cout << "regular orders queue: " << endl;
		for (int i = 0; i < regular_que.size(); i++) {
			if (regular_que[i].get_status() == -1)
				cout << regular_que[i].get_number() << " " << regular_que[i].get_paper() << endl;
		}
		cout << endl;
	}
	void print_printers() {
		cout << "printers:" << endl;
		for (int i = 0; i < printers.size(); i++) {
			cout << "printer ID: " << printers[i].get_number() << endl;
			cout << "status: " << printers[i].get_status() << endl;
			if (printers[i].get_order() != NULL) {
				cout << "current order: " << printers[i].get_order()->get_number() << " ";
				if (printers[i].get_order()->get_lefted_paper() <= 0)
					cout << "0" << endl;
				else
					cout << printers[i].get_order()->get_lefted_paper() << endl;
			}
			cout << "ink left:" << endl;
			cout << "red: " << printers[i].get_lefted_ink()[0] << endl;
			cout << "green: " << printers[i].get_lefted_ink()[1] << endl;
			cout << "blue: " << printers[i].get_lefted_ink()[2] << endl;
			cout << "black: " << printers[i].get_lefted_ink()[3] << endl;
			cout << "papers left: " << printers[i].get_lefted_paper() << endl << endl;
		}
	}
	void finish() {
		cout << passed_time;
	}
	void sorting(vector<vector<int>>&vec) {
		int a, b;
		for (int i = 0; i < vec.size(); i++) {
			for (int j = 0; j < vec.size() - 1; j++) {
				if (vec[j][0] > vec[j + 1][0]) {
					a = vec[j][0];
					vec[j][0] = vec[j + 1][0];
					vec[j + 1][0] = a;
					b = vec[j][1];
					vec[j][1] = vec[j + 1][1];
					vec[j + 1][1] = b;
				}
			}

		}
	}
	void print_printeds() {
		vector<vector<int>>printeds;
		cout << "orders finished: " << endl;
		for (int i = 0; i < vip_que.size(); i++) {
			if (vip_que[i].get_status() == 1)
				printeds.push_back({ vip_que[i].get_number(),vip_que[i].get_needing_time() });
			//
		}
		for (int j = 0; j < regular_que.size(); j++) {
			if (regular_que[j].get_status() == 1)
				printeds.push_back({ regular_que[j].get_number(),regular_que[j].get_needing_time() });
		}
		sorting(printeds);
		for (int k = 0; k < printeds.size(); k++) {
			cout << printeds[k][0] << " " << printeds[k][1] << endl;
		}
		cout << endl;

	}
	void showing_information() {
		cout << "passed time: " << passed_time << endl;
		print_vip_que();
		print_reg_que();
		print_printers();
		print_printeds();
	}
	void set_duration(int num) {
		duration = num;
	}

private:
	int duration = 0;
	int passed_time = 0;
	vector < printer >printers;
	vector < Order > orders;
	vector<Order>regular_que;
	vector<Order>vip_que;
};



vector<string> input_getting() {
	string temp_str;
	vector<string>commands;
	while (getline(cin, temp_str))
		commands.push_back(temp_str);
	return commands;
}
vector<vector<string>> splitting_input(vector<string>commands) {
	vector<vector<string>> splitted_input;
	vector<string>temp_vec;
	string token;
	for (int i = 0; i < commands.size(); i++) {
		stringstream S(commands[i]);
		while (getline(S, token, ' ')) {
			temp_vec.push_back(token);
		}
		splitted_input.push_back(temp_vec);
		temp_vec.clear();

	}
	return splitted_input;
}
void doing_commands(vector<vector<string>>splitted_commands, int current_time) {
	Printing_house my_printing_house;
	for (int i = 0; i < splitted_commands.size(); i++) {
		if (splitted_commands[i][0] == "add_printer")
			my_printing_house.add_printers(stoi(splitted_commands[i][1]));
		else if (splitted_commands[i][0] == "add_order") {
			my_printing_house.add_order(stoi(splitted_commands[i][1]), stoi(splitted_commands[i][2])
				, stoi(splitted_commands[i][3]), stoi(splitted_commands[i][4]), stoi(splitted_commands[i][5]),
				(splitted_commands[i][6]));
		}
		else if (splitted_commands[i][0] == "advance_time") {
			cout << "ok" << endl;
			my_printing_house.advance_time(stoi(splitted_commands[i][1]));
			my_printing_house.advance();

		}

		else if (splitted_commands[i][0] == "show_press_info") {
			my_printing_house.showing_information();
			my_printing_house.set_duration(0);
		}
		else if (splitted_commands[i][0] == "finish")
			my_printing_house.finish();

	}

}

int main() {
	string temp_str;
	vector<string>commands = input_getting();
	
	vector<vector<string>>splitted_commands = splitting_input(commands);
	doing_commands(splitted_commands, 0);
	return 0;
}
