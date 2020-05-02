#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <list>
#include <vector> 
#include <iterator>

//g++11 -o runthisc intelligent_agent/Link_list.cpp intelligent_agent/Link_list.h intelligent_agent/main.cpp 
using namespace std;


struct Url_list_member{

	string url_str;
	list<list<float>> a_list;
	list<list<int>> temp_list;
	list<list<int>> b_list;
	list<list<int>> c_list;
	int jump_score;
	int path_score;
	};

int removeDupWord(string str){
int return_out;
return_out = 1;
string word = ""; 
for (auto x : str) 
{ 
if (x == ' ') 
{
   return_out++; 
} 
}  
return return_out;
}

int get_optimized(string str) 
{
list<string> opt_list;
string this_num;
for(std::string::iterator it = str.end()-1; it != str.begin(); --it) {
	char this_char;
	this_char = *it;
	if(!isspace(this_char)){

		if (this_char == ':'){
			break;
			}
		else{
			this_num.insert(this_num.begin(), this_char);
			}
		}
	}
	int return_val = std::stoi(this_num);
	return return_val; 
}

int main(int argc, char** argv) {
		
	string line;
	std::list<string> url_list;
	std::list<string>::iterator it;

	
	//ifstream myfile ("example_nlp_output");
	ifstream myfile (argv[1]);
	
	if (myfile.is_open())
	{
	while ( getline (myfile,line) )
	{

	url_list.push_back(line);

	}
	myfile.close();																											   
	}

	else cout << "Unable to open file";


	int countlog;
	int first_url = 1;
	int query_end = 0;
	int halt_pos = 0;
	int next_url = 0;
	int kill_switch = 0;
	float special = 0.0;
	it=url_list.begin();
	string last_url = "";
	string temp_str;
	list<Url_list_member> member_list;
	list<Url_list_member>::iterator url_it;
	url_it = member_list.begin();
	Url_list_member new_member;

	int last_webpage_pos;
	int webpage_pos;
	int query_pos;
	string url_str;
	float nlp_comp;


	list<list<float>>::iterator a_it;
	list<list<int>>::iterator b_it;
	list<list<int>>::iterator c_it;


	list<float>::iterator a_x_it;
	list<float> new_list;

	for (int countlog = 0; countlog < url_list.size(); countlog++){
		//url_str = *it;
		++it;
		countlog++;
		temp_str = *it;
		query_pos = std::stoi(temp_str);
		++it;
		countlog++;
		temp_str = *it;
		last_webpage_pos = webpage_pos;	
		webpage_pos = std::stoi(temp_str);  

		++it;
		countlog++;
		temp_str = *it;

		nlp_comp = std::stof(temp_str);  
		
		countlog++;
		if (countlog < url_list.size()){
			++it;
			}
		if (first_url == 0 && query_pos == 0){
			query_end = 1;
		}
		
		if(first_url == 1){
			//last_url = url_str;	
			first_url = 0;
			
			new_list.clear();
			new_list.push_back(nlp_comp);
				
			new_member.a_list.push_back(new_list);
		}
		else if(query_end == 0){
			halt_pos++;
			new_list.clear();
			new_list.push_back(nlp_comp);
			new_member.a_list.push_back(new_list);
		}

		else if(last_webpage_pos <= webpage_pos){


			a_it = new_member.a_list.begin();
			
			for(int i = 0; i < query_pos; i++){

			a_it++;
			}
			new_list.clear();
			new_list = *a_it;
			new_list.push_back(nlp_comp);
			*a_it = new_list;				


		}
		
		else{

			std::advance(it,-8);
			url_str = *it;
			std::advance(it,8);
			new_member.url_str = url_str;
			//cout<< "URL  " << url_str << " \n";
			//cout<< "Memebers  " << new_member.a_list.size() << " \n";
			a_it = new_member.a_list.begin();
			new_list.clear();
			new_list = *a_it;
			if(next_url == 1){
				//cout<< "POP! \n";
				new_list.push_front(special);
				*a_it = new_list;
				}
			/*
			cout<< "List  " << new_list.size() << " \n";
			cout<< "Front " << new_list.front() << " \n";
			cout<< "Last  " << new_list.back() << " \n";
			++a_it;
			new_list = *a_it;
			cout<< "List  " << new_list.size() << " \n";
			cout<< "Front " << new_list.front() << " \n";
			cout<< "Last  " << new_list.back() << " \n";
			++a_it;
			new_list = *a_it;
			cout<< "List  " << new_list.size() << " \n";
			cout<< "Front " << new_list.front() << " \n";
			cout<< "Last  " << new_list.back() << " \n";
			*/
			
			member_list.push_back(new_member);
			a_it = new_member.a_list.begin();
			
			list<float> newer_list;
			
			for (int i = 0; i<= halt_pos; i++){
				newer_list = *a_it;
				newer_list.clear();
				*a_it = newer_list;
				a_it++;
			}
				
			
			last_url = url_str;	
			
			special = nlp_comp;
			
			next_url = 1;
			/*	
			kill_switch++;
			if (kill_switch > 0){
				break;
				}
			*/
		}
		
	
	}

	//cout<< "URL List  " << member_list.size() << " \n";
	url_it = member_list.begin();
	std::list<float>::iterator f_it;
	for (int i = 0; i< member_list.size(); i++){
		Url_list_member this_member = *url_it;
		//cout << "This mem size " << this_member.a_list.size() << " \n";
		a_it = this_member.a_list.begin();
		list<list<int>> hit_matrix;
		for (int j = 0; j < this_member.a_list.size(); j++){
			list<float> sub_list = *a_it;
			//cout << "This sub mem size " << sub_list.size() << " \n";

			float k_var = 0;
			float x_var = 0;
			float y_var = 0;
			float z_var = 0;
			f_it = sub_list.begin();
			list<int> pos_hit_locs;
			int hit_loc = 0;
			for(int k = 0; k < sub_list.size(); k++){
				k_var = *f_it;
				/*
				if(k_var > 0.0){
					x_var++;
				}
				*/
				y_var += k_var;
				++f_it;
				}
			float raw_ave = 0.5;
			//raw_ave = (raw_ave + 0.5)/2;
			f_it = sub_list.begin();
			
			for(int k = 0; k < sub_list.size(); k++){
				k_var = *f_it;
				if(k_var > raw_ave){
					pos_hit_locs.push_back(hit_loc);
					z_var++;
				}
				hit_loc++;
				++f_it;
				}
			//cout<< " Positive comps :: "<< x_var << " \n";
			//cout<< " sum :: "<< y_var << " \n";
			//cout<< " ave :: "<< raw_ave << " \n";
			
			//cout<< " Positive ave :: "<< y_var/x_var << " \n";
			//cout<< " Positive ave hits :: "<< z_var << " \n";
			hit_matrix.push_back(pos_hit_locs);	
		//cout<<" \n";
		a_it++;
		
		}
		this_member.temp_list = hit_matrix;
		*url_it = this_member;
		++url_it;
		
		}
	url_it = member_list.begin();
	std::list<list<int>>::iterator temp_it_0;
	std::list<list<int>>::iterator temp_it_1;

	std::list<int>::iterator sub_it_0;
	std::list<int>::iterator sub_it_1;

	for (int i = 0; i< member_list.size(); i++){
		Url_list_member this_member = *url_it;
		temp_it_0 = this_member.temp_list.begin();
		temp_it_1 = this_member.temp_list.begin();
		++temp_it_1;

		for (int j = 1; j < this_member.temp_list.size(); j++){
			list<int> temp_b_list;
			list<int> sub_temp_0 = *temp_it_0;

			sub_it_0 = sub_temp_0.begin();

			for (int sub_0 = 0; sub_0 < sub_temp_0.size(); sub_0++){
				int int_0 = *sub_it_0;
				list<int> sub_temp_1 = *temp_it_1;
				sub_it_1 = sub_temp_1.begin();
				for (int sub_1 = 0; sub_1 < sub_temp_1.size(); sub_1++){
					int int_1 = *sub_it_1;
					if (int_0 < int_1){
						temp_b_list.push_back(int_0);
						temp_b_list.push_back(int_1);
						temp_b_list.push_back(int_1-int_0);
						break;
					}
					++sub_it_1;
	
				}

				++sub_it_0; 
				}
			this_member.b_list.push_back(temp_b_list);	
			++temp_it_0;	
			++temp_it_1;		
			}
		temp_it_0 = this_member.temp_list.begin();
		temp_it_1 = this_member.temp_list.begin();
		++temp_it_1;
		++temp_it_1;
		for (int j = 2; j < this_member.temp_list.size(); j++){
			list<int> temp_b_list;
			list<int> sub_temp_0 = *temp_it_0;

			sub_it_0 = sub_temp_0.begin();

			for (int sub_0 = 0; sub_0 < sub_temp_0.size(); sub_0++){
				int int_0 = *sub_it_0;
				list<int> sub_temp_1 = *temp_it_1;
				sub_it_1 = sub_temp_1.begin();
				for (int sub_1 = 0; sub_1 < sub_temp_1.size(); sub_1++){
					int int_1 = *sub_it_1;
					if (int_0 < int_1){
						temp_b_list.push_back(int_0);
						temp_b_list.push_back(int_1);
						temp_b_list.push_back(int_1-int_0);
						break;
					}
					++sub_it_1;
	
				}

				++sub_it_0; 
				}
			this_member.c_list.push_back(temp_b_list);	
			++temp_it_0;	
			++temp_it_1;		
			}
		*url_it = this_member;
		++url_it;
		}

	url_it = member_list.begin();
	char node_s[2250];
	std::list<int>::iterator b_sub_it;
	std::list<int>::iterator c_sub_it;
	char node_e[50];
	char dis_nodes[50];
	
	string asp_run = argv[1];
	string asp_output = argv[1];
	asp_run = asp_run+".lp";
	asp_output = asp_output + "_log";		
	for (int i = 0; i< member_list.size(); i++){
		Url_list_member this_member = *url_it;

		b_it = this_member.b_list.begin();
		c_it = this_member.b_list.begin();
		int start_flag;
		int end_flag_b;
		int end_flag_c;
		int score_1;
		int score_2;
		this_member.jump_score = 0;
		this_member.path_score = 0;
		start_flag = 0;
		end_flag_b = 0;
		end_flag_c = 0;
		for (int j = 0; j < this_member.b_list.size(); j++){
			list<int> this_b_list = *b_it;
			b_sub_it = this_b_list.begin();
			if(this_b_list.size() > 0){
				end_flag_b = j;
				}
			++b_it;
			}
		for (int j = 0; j < this_member.c_list.size(); j++){
			list<int> this_b_list = *c_it;
			c_sub_it = this_b_list.begin();
			if(this_b_list.size() > 0){
				end_flag_c = j;
				}
			++c_it;
			}
		b_it = this_member.b_list.begin();
		c_it = this_member.c_list.begin();
		string command_1, command_2;
		command_1 = "rm " + asp_run;
		system(command_1.c_str());
		command_2 = "rm " + asp_output;		
		system(command_2.c_str());
		std::ofstream asp_file(asp_run);
		sprintf(node_s, "#include <incmode>. ");
		asp_file << node_s  <<endl;
		sprintf(node_s, "#program base. ");
		asp_file << node_s  <<endl;
		sprintf(node_s, "location(node_start).");
		asp_file << node_s <<endl;
		sprintf(node_s, "location(node_end)." );
		asp_file << node_s <<endl;
		if(asp_file.is_open()){	
			for (int j = 0; j < this_member.b_list.size(); j++){
				list<int> this_b_list = *b_it;
				start_flag++;
				b_sub_it = this_b_list.begin();
				for (int k = 0; k < this_b_list.size(); k++){
					int node_1 = *b_sub_it;
					++b_sub_it;
					k++;
					int node_2 = *b_sub_it;
					++b_sub_it;
					k++;
					int node_d = *b_sub_it;
					++b_sub_it;
					
					sprintf(node_s, "location(node_%i).", node_1);
					asp_file << node_s <<endl;
					sprintf(node_s, "location(node_%i).", node_2);
					asp_file << node_s <<endl;
					if (start_flag ==1){
						sprintf(node_s, "connection(node_start, node_%i, 1, 1).", node_1 );
						asp_file << node_s <<endl;
						}

					sprintf(node_s, "connection(node_%i, node_%i, %i, 1).", node_1, node_2, node_d );
					asp_file << node_s <<endl;
					if (end_flag_b ==j){
						sprintf(node_s, "connection(node_%i, node_end, 1, 1).", node_2 );
						asp_file << node_s <<endl;
						}
					}
	sprintf(node_s, " " );
	asp_file << node_s <<endl;
				++b_it;
				}
			for (int j = 0; j < this_member.c_list.size(); j++){
				list<int> this_c_list = *c_it;
				start_flag++;
				c_sub_it = this_c_list.begin();
				for (int k = 0; k < this_c_list.size(); k++){
					int node_1 = *c_sub_it;
					++c_sub_it;
					k++;
					int node_2 = *c_sub_it;
					++c_sub_it;
					k++;
					int node_d = *c_sub_it;
					++c_sub_it;
					
					sprintf(node_s, "location(node_%i).", node_1);
					asp_file << node_s <<endl;
					sprintf(node_s, "location(node_%i).", node_2);
					asp_file << node_s <<endl;
					if (start_flag ==1){
						sprintf(node_s, "connection(node_start, node_%i, 1, 2).", node_1 );
						asp_file << node_s <<endl;
						}

					sprintf(node_s, "connection(node_%i, node_%i, %i, 2).", node_1, node_2, node_d );
					asp_file << node_s <<endl;
					if (end_flag_c ==j){
						sprintf(node_s, "connection(node_%i, node_end, 1, 2).", node_2 );
						asp_file << node_s <<endl;
						}
					}
	sprintf(node_s, " " );
	asp_file << node_s <<endl;
				++c_it;
				}

			sprintf(node_s, "location(X) :- block(X).");
			asp_file << node_s  <<endl;
			sprintf(node_s, "holds(F,0) :- init(F). ");
			asp_file << node_s  <<endl;
			sprintf(node_s, "#program step(t). ");
			asp_file << node_s  <<endl;
			sprintf(node_s, "{ move(X,M,Y,t,W,C) : block(X), location(Y), location(M) } :- holds(on(X,M),t-1), connection(M, Y, W, C). ");
			asp_file << node_s  <<endl;
			sprintf(node_s, ":- move(X,M,Y,t,W,C), holds(on(A,X),t-1). ");
			asp_file << node_s  <<endl;
			sprintf(node_s, ":- move(X,M,Y,t,W,C), holds(on(B,Y),t-1), B != X, Y != node_a. ");
			asp_file << node_s  <<endl;
			sprintf(node_s, ":- move(X,M,Y,t,W,C), connection(M, Y, W1, C), connection(M1, Y, W2, C1), C > C1. ");
			asp_file << node_s  <<endl;
			sprintf(node_s, "moved(X,t) :- move(X,M,Y,t,W,C). ");
			asp_file << node_s  <<endl;
			sprintf(node_s, "holds(on(X,Y),t) :- move(X,M,Y,t,W,C). ");
			asp_file << node_s  <<endl;
			sprintf(node_s, "holds(on(X,Z),t) :- holds(on(X,Z),t-1), not moved(X,t). ");
			asp_file << node_s  <<endl;
			sprintf(node_s, "#program check(t). ");
			asp_file << node_s  <<endl;
			sprintf(node_s, ":- query(t), goal(F), not holds(F,t). ");
			asp_file << node_s  <<endl;
			sprintf(node_s, "#minimize { W: move(X,M,Y,t,W,C)}. ");
			asp_file << node_s  <<endl;
			sprintf(node_s, "#show move/6. ");
			asp_file << node_s  <<endl;
			sprintf(node_s, "#program base. ");
			asp_file << node_s  <<endl;
			sprintf(node_s, "block(b0). ");
			asp_file << node_s  <<endl;
			sprintf(node_s, "init(on(b0,node_start)). ");
			asp_file << node_s  <<endl;
			sprintf(node_s, "goal(on(b0,node_end)). ");
			asp_file << node_s  <<endl;
			asp_file.close();
			//asp_file << " "<< this_member.url_str << endl;
			std::ofstream out(asp_output);
			out << "#"+this_member.url_str;
			out.close();
			string rate_line;
			std::list<string> rate_list;
			system(("clingo --time-limit=4 " + asp_run + ">> "+ asp_output).c_str() );
			std::ifstream rate_out (asp_output);

			if (rate_out.is_open()){
			while ( std::getline(rate_out, rate_line) )
			

			rate_list.push_back(rate_line);

			}
			rate_out.close();
			it = rate_list.begin();

			score_1 = 0;
			score_2 = 0;
			for(int i = 0; i < rate_list.size(); i++){
				rate_line = *it;
				std::string sub_rate = rate_line.substr(0,3);
				std::string opt_rate = rate_line.substr(0,6);
				if(sub_rate.compare("mov") ==0 &&score_1 == 0 ){
					score_1 = removeDupWord(rate_line);
					printf("YES!! %i \n", score_1);
					}
				if(opt_rate.compare("Optimi") ==0 && score_2 == 0){
					score_2 = get_optimized(rate_line);
					printf("YES!! %i \n", score_2);
					}	
				++it;	
				}
						

			}
			this_member.jump_score = score_1;
			this_member.path_score = score_2;
			*url_it = this_member;
			++url_it;
			
		}
	
	url_it = member_list.begin();
	system(("rm " + asp_output ).c_str() );
	std::ofstream final_out(asp_output);
	
	for (int i = 0; i< member_list.size(); i++){
		Url_list_member this_member = *url_it;
		final_out << this_member.url_str << endl;
		final_out << this_member.jump_score << endl;
		final_out << this_member.path_score << endl;
		url_it++;
		}
	final_out.close();
	return 0;
	
	}			

