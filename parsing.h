#ifndef PARSING_H
#define PARSING_H

#include <QString>
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <math.h>
#include <cctype>
using namespace std;

bool is_operator(char c);
//bool is_operand(char c);
bool is_operand(char c, char prev);
double apply_operator(char op, double a, double b);
bool check_op(char a, char prev);
double evaluate_expression(string& expression);
bool is_contains_alpha(const string str);
void make_easier(QString& function);
map<int, int> find_matching_brackets(const QString& str);

void get_all_op(list<string>& All_op, QString function, int& n);
void get_all_op_2(list<string>& All_op, QString function, int& n);
void show_list(list<string> All_op);
void replaceSubstrings(string& str);
void transformation(QString& function);

#endif // PARSING_H

