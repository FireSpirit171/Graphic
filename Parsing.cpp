#include "parsing.h"
vector<string> all_func={"ln", "sin", "cos", "tg", "ctg", "sqrt", "arcsin", "arccos", "arctg", "arcctg", "abs", "X"};
const string operators = "+-/*^";

bool is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool is_operand(char c, char prev) {
    return isdigit(c) || (c == '-' && (prev == '(' || is_operator(prev)));
}

double apply_operator(char op, double a, double b) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
        default: return 0;
    }
}

bool check_op(char a, char prev){
    int zn, zn_prev;

    if (a=='+') zn=1;
    else if (a=='-') zn=2;
    else if(a=='*' or a=='/') zn=3;
    else zn=4;

    if (prev=='+') zn_prev=1;
    else if (prev=='-') zn_prev=2;
    else if(prev=='*' or prev=='/') zn_prev=3;
    else zn_prev=4;

    if (zn<zn_prev) return true;
    return false;
}

double evaluate_expression(string& expression) {
    stack<double> values;
    stack<char> operators;

    replaceSubstrings(expression);

    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        char prev = (i == 0) ? '(' : expression[i - 1];
        if (is_operand(c, prev)) {
            int sign = 1;
            if (c == '-') {
                sign = -1;
                i++;
                c = expression[i];
            }
            double operand = 0;
            double decimal = 0.1;
            bool is_decimal = false;
            while (i < expression.length() && (isdigit(expression[i]) || expression[i] == '.')) {
                if (expression[i] == '.') {
                    is_decimal = true;
                } else {
                    if (is_decimal) {
                        operand += (expression[i] - '0') * decimal;
                        decimal *= 0.1;
                    } else {
                        operand = operand * 10 + (expression[i] - '0');
                    }
                }
                i++;
            }
            i--;
            values.push(sign * operand);  //ЗДЕСЬ
        }
        else if (is_operator(c)) {
            while (!operators.empty() && operators.top() != '(' && c!='^' && check_op(c, operators.top())){
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                double result = apply_operator(op, a, b);
                values.push(result);   //ЗДЕСЬ
            }
            operators.push(c);  //ЗДЕСЬ
        }
        else if (c == '(') {
            operators.push(c);  //ЗДЕСЬ
        }
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = operators.top(); operators.pop();
                double result = apply_operator(op, a, b);
                values.push(result);   //ЗДЕСЬ
            }
            if (!operators.empty()) operators.pop();
        }
    }

    while (!operators.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = operators.top(); operators.pop();
        double result = apply_operator(op, a, b);
        values.push(result);    //ЗДЕСЬ
    }

    return values.top();
}


bool is_contains_alpha(const string str) {
    bool is_contains=false;
    for (char c : str) {
        if (isalpha(c) and c!='X' and c!= 'x') {
            is_contains = true;
        }
    }
    return is_contains;
}

std::map<int, int> find_matching_brackets(const QString& str) {
    std::stack<int> st;
    std::map<int, int> result;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(') {
            st.push(i);
        }
        else if (str[i] == ')') {
            if (!st.empty()) {
                int open_pos = st.top();
                st.pop();
                QString sub_str = str.mid(open_pos + 1, i - open_pos - 1);
                if (sub_str != "-1") {
                    result[open_pos] = i;
                }
            }
        }
    }
    return result;
}

void make_easier(QString& func)
{
    string may_short;
    int i=0;
    while (i<func.length()-1){
        int j=i+1;
        while (j<func.length()){
            if (func.at(i).isDigit() and func.at(j).isDigit()){
                may_short = func.toStdString().substr(i, j-i+1);

                bool have_alpha = false;
                for (char c : may_short) {
                    if (isalpha(c) or c=='(' or c==')' or may_short.find_first_of(operators) == std::string::npos) have_alpha = true;
                }

                if (!have_alpha){
                    may_short = to_string(evaluate_expression(may_short));
                    func.replace(i, j-i+1, QString::fromStdString(may_short));
                    j=i+1;
                }
            }
            j++;
        }
        i++;
    }
}



void get_all_op_2(list<string> &All_op, QString function, int& n){
    string func = function.toStdString();
    func = "("+func+")";

    for (int i=0; i<func.length(); i++){
        if (func[i]==' ') func.erase(i,1);
    }

    map<int, int> matching_brackets = find_matching_brackets(QString::fromStdString(func));
    map<int, int>::reverse_iterator iter = matching_brackets.rbegin();
    int sdvig=0;

    while (iter!=matching_brackets.rend()){
        if (func=="(x)" or func=="(X)" or func=="(-1)"){
            if (func=="(x)") All_op.push_back("x");
            else if (func=="(X)") All_op.push_back("X");
            else All_op.push_back("-1");
            break;
        }
        int first = iter->first; // первый элемент пары
        int second = iter->second-sdvig; // второй элемент пары
        string str = func.substr(first+1, second - first - 1);
        if (str != "X" and str!="x") {
            if (is_contains_alpha(str)) {
                get_all_op(All_op, QString::fromStdString(str), n);
            } else {
                All_op.push_back(str);
                n += 1;
                func.replace(first+1, second - first - 1, "X");
                sdvig+=second-first-1-1;
            }
        } else {
            bool we_found=false;
            for (int i=0; i<first; i++) { // ищем ближайшую функцию
                string may_func = func.substr(i, first-i);
                if (find(all_func.begin(), all_func.end(), may_func) != all_func.end()) {
                    All_op.push_back(may_func); // добавляем в список
                    n += 1;
                    func.replace(i, second-i+1, "X"); // заменили на x
                    sdvig+=second-i;
                    ++iter;
                    we_found=true;
                    break;
                }
            }
            if (!we_found){
                func.replace(first,second-first+1,"X");
                sdvig+=second-first;
                ++iter;
                //break;
            }
        }
    }

    if (func[0]=='(') func.erase(0,1);
    if  (func[func.length()-1]==')') func.erase(func.length()-1);
    if (All_op.back()!=func) All_op.push_back(func);
}
void get_all_op(list<string> &All_op, QString function, int& n){
    string func = function.toStdString();

    //здесь уберем пробелы из строки
    for (int i=0; i<func.length(); i++){
        if (func[i]==' ') func.erase(i,1);
    }

    int pos_x=0;
    int pos_left = -1;
    int pos_right = func.length()+1;
    int pos_znak_left, pos_znak_right;
    bool is_func=false;

    while (func!="X"){
        pos_x = func.find("X");  //нашли x
        for (int i1=pos_x; i1>=0; i1--){ //если есть ( то нашли её, иначе она -1
            if (func[i1]=='('){
                pos_left=i1;
                break;
            }
        }
        for (int i2=pos_x; i2<func.length(); i2++){ //если есть ) то нашли её, иначе она func.length()
            if (func[i2]==')'){
                pos_right=i2;
                break;
            }
        }

        if (func.substr(pos_left+1, pos_right-pos_left-1)=="X" or func.substr(pos_left+1, pos_right-pos_left-1)=="x") is_func = true; //определяем, внешняя функция или внутренняя операция

        if(is_func){ //если это функция
            for (int i=0; i<pos_left; i++){ //ищем ближайшую функцию
                string may_func = func.substr(i, pos_left-i);
                if (find(all_func.begin(), all_func.end(), may_func)!=all_func.end()){
                    All_op.push_back(may_func); //добавляем в список
                    n+=1;
                    func.replace(i, pos_right+1, "X"); //заменили на x
                    break;
                }
            }
        }

        else{
            string left = func.substr(pos_left+1, pos_x-pos_left-1);
            if (left.find_first_of("+-")==string::npos) pos_znak_left=pos_left;
            else pos_znak_left = left.find_first_of("+-")+pos_left+1;
            string right = func.substr(pos_x+1, pos_right-pos_x-1);
            if (right.find_first_of("+-")==string::npos) pos_znak_right=pos_right;
            else pos_znak_right = right.find_first_of("+-")+pos_x+1;

            if (func.substr(pos_znak_left+1, (pos_znak_right-1)-(pos_znak_left+1)+1)!="X"){
                pos_right=pos_znak_right-1;
                pos_left=pos_znak_left+1;
            }

            if (func[pos_x+1]=='^' or func[pos_x-1]=='^'){  //Возведение в степень
                if (func[pos_x-1]=='^'){
                    All_op.push_back(func.substr(pos_left, pos_x-pos_left));
                    func.replace(pos_left, pos_x-pos_left+1, "X");
                }
                else{
                    All_op.push_back(func.substr(pos_x+1, pos_right-pos_x));
                    func.replace(pos_x, pos_right-pos_x+1, "X");
                }
                n+=1;
            }
            else if (func[pos_x+1]=='*' or func[pos_x-1]=='*'){  //Умножение
                if (func[pos_x-1]=='*'){
                    All_op.push_back(func.substr(pos_left, pos_x-pos_left));
                    func.replace(pos_left, pos_right-pos_left+1, "X");
                }
                else{
                    All_op.push_back(func.substr(pos_x+1, pos_right-pos_x));
                    func.replace(pos_x, pos_right-pos_x+1, "X");
                }
                n+=1;
            }
            else if (func[pos_x+1]=='/' or func[pos_x-1]=='/'){  //Деление
                if (func[pos_x-1]=='/'){
                    All_op.push_back(func.substr(pos_left, pos_x-pos_left));
                    func.replace(pos_left, pos_right-pos_left+1, "X");
                }
                else{
                    All_op.push_back(func.substr(pos_x+1, pos_right-pos_x));
                    func.replace(pos_x, pos_right-pos_x+1, "X");
                }
                n+=1;
            }
            else if (func[pos_x+1]=='+' or func[pos_x-1]=='+'){  //Сложение
                if (func[pos_x-1]=='+'){
                    All_op.push_back(func.substr(pos_left+1, pos_x-pos_left-1));
                }
                else{
                    All_op.push_back(func.substr(pos_x+1, pos_right-pos_x-1));
                }
                n+=1;
                func.replace(pos_left+1, pos_right-pos_left-1, "X");
            }
            else if (func[pos_x+1]=='-' or func[pos_x-1]=='-'){  //Умножение
                if (func[pos_x-1]=='-'){
                    All_op.push_back(func.substr(pos_left+1, pos_x-pos_left-1));
                }
                else{
                    All_op.push_back(func.substr(pos_x+1, pos_right-pos_x-1));
                }
                n+=1;
                func.replace(pos_left+1, pos_right-pos_left-1, "X");
            }
        }

        pos_x=0;
        pos_left = -1;
        pos_right = func.length()+1;
        is_func=false;
    }
}


void show_list(list<string> All_op){
    list<string>::iterator iter;
    for (iter=All_op.begin(); iter!=All_op.end(); ++iter){
        cout<<*iter<<endl;
    }
}

void replaceSubstrings(string& str) {
    size_t pos = 0;
    while ((pos = str.find("++", pos)) != std::string::npos) {
        str.replace(pos, 2, "+");
        pos++;
    }
    pos = 0;
    while ((pos = str.find("--", pos)) != std::string::npos) {
        str.replace(pos, 2, "+");
        pos++;
    }
    pos = 0;
    while ((pos = str.find("+-", pos)) != std::string::npos) {
        str.replace(pos, 2, "-");
        pos++;
    }
    pos = 0;
    while ((pos = str.find("-+", pos)) != std::string::npos) {
        str.replace(pos, 2, "-");
        pos++;
    }
    pos = 0;
    while ((pos = str.find("+-+-", pos)) != std::string::npos) {
        str.replace(pos, 4, "-");
        pos++;
    }
}


void transformation(QString& function){
    function.replace(" ", "");
    function=function.mid(2);
    function.replace("pi", "3.14159");
    function.replace("e", "2.71828");

    int j=0;
    while (j<function.length()-1){
        if (isdigit(function.at(j).toLatin1()) and function.at(j+1)=='x'){
            function.insert(j+1, '*');
            j++;
        }
        j++;
    }

    int i=0;
    if (function.at(0)=='-'){
        function.insert(0,'0');
        i+=1;
    }
    while (i<function.length()-1){
        if (function.at(i)=='-'){
            if (function.at(i-1)=='(' or i==0){
                function.replace(i,1,"(-1)*");
            }
            else if (!isdigit(function.at(i+1).toLatin1())) function.replace(i,1,"+(-1)*");
            i+=2;
        }
        i+=1;
    }
}
