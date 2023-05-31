#include "our_classes.h"
vector<string> all_func_2={"ln", "sin", "cos", "tg", "ctg", "sqrt", "arcsin", "arccos", "arctg", "arcctg", "abs", "-1", "X"};

extern char graphColor[3];

void GraphWidget::coord_console(QPaintEvent* event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);

    int null_x = prevWidth/2 + (width()-prevWidth)/2;
    int null_y = prevHeight/2 + (height() - prevHeight)/2;

    painter.drawLine(0, null_y, width(), null_y);  //здесь ось х
    painter.drawLine(null_x, 0, null_x, height());  //здесь ось y

    for (int x=null_x; x<width(); x+=20){
        painter.drawLine(x, null_y-5, x, null_y+5); //захерачили штришки вправо
    }
    for (int x=null_x; x>0; x-=20){
        painter.drawLine(x, null_y-5, x, null_y+5); //захерачили штришки влево
    }
    for (int y=null_y; y<height(); y+=20){
        painter.drawLine(null_x-5, y, null_x+5, y); //захерачли штришки вниз
    }
    for (int y=null_y; y>0; y-=20){
        painter.drawLine(null_x-5, y, null_x+5, y); //захерачили штришки вверх
    }

    painter.drawText(QPoint(null_x-10, null_y+15), "0");
    painter.drawText(QPoint(width()-10, null_y+20), "X");
    painter.drawText(QPoint(null_x-15, 15), "Y");

    prevHeight=height();
    prevWidth=width();
}

void GraphWidget::draw_graphic(std::vector<console_point>& all_values, int num_points, char color){

    QPainter painter(this);
    if (color=='r') painter.setPen(QPen(Qt::red, 2));
    else if (color=='g') painter.setPen(QPen(Qt::green, 2));
    else painter.setPen(QPen(Qt::blue, 2));
    painter.translate(width() / 2, height() / 2);

    int x=0;
    int y=0;
    int x1=0;
    int y1=0;
    for (int i=0; i<num_points-1; i++){
        x=all_values[i].x*20;
        y=(-1)*all_values[i].y*20;
        x1=all_values[i+1].x*20;
        y1=(-1)*all_values[i+1].y*20;

        if (abs(y1-y)<height()/2 and abs(x1-x)<20) painter.drawLine(x,y,x1,y1);
    }
    all_values.clear();
}

void fill_value(std::list<std::string>& All_op, std::vector<console_point> &all_value, int Y, int X, int& num_points){

    std::list<std::string>::iterator iter;
    std::string expr;
    for (double i = - 40; i < 40; i+=0.05){
        double X_res = i;
        bool point_exist = true;
        for (iter=All_op.begin(); iter!=All_op.end(); ++iter){
            expr=(*iter);
            if (find(all_func_2.begin(), all_func_2.end(), expr) != all_func_2.end()){
                if (expr=="ln") X_res = X_res>0 ? X_res = log(X_res):point_exist = false;
                else if (expr=="-1") X_res = -1;
                else if (expr=="cos") X_res = cos(X_res);
                else if (expr=="sin") X_res = sin(X_res);
                else if (expr=="sqrt"){
                    if (X_res==0) X_res=0;
                    else if (X_res>0) X_res = pow(X_res, 0.5);
                    else point_exist = false;
                }
                else if (expr=="tg") X_res = tan(X_res);
                else if (expr=="ctg") X_res = cos(X_res)/sin(X_res);
                else if (expr=="arcsin") X_res = (X_res <= 1 and X_res >= -1) ? X_res = asin(X_res):point_exist = false;
                else if (expr=="arccos") X_res = (X_res <= 1 and X_res >= -1) ? X_res = acos(X_res):point_exist = false;
                else if (expr=="arctg") X_res = atan(X_res);
                else if (expr=="arcctg") X_res = 3.14159/2-atan(X_res);
                else if (expr=="abs") X_res = abs(X_res);
                else if (expr=="X"); X_res = X_res;
            }
            else{
                int pos = expr.find("x");
                while (pos != std::string::npos) {  //заменяем все х на значения аргумента в данной точке
                    expr.replace(pos, 1, std::to_string(i));
                    pos = expr.find("x", pos + 1);
                }
                pos = expr.find("X");
                while (pos != std::string::npos) {   //заменяем все Х на значения вычисленное в предыдущем итераторе
                    expr.replace(pos, 1, std::to_string(X_res));
                    pos = expr.find("X", pos + 1);
                }
                X_res = evaluate_expression(expr); //вычислили значение
            }
        }
        if (X_res<21 and X_res>-21 and point_exist){   //ПРОВЕРКА
            all_value.push_back(console_point(i, X_res)); //занесли значение
            num_points+=1;
        }
    }
}

void GraphWidget::paintEvent(QPaintEvent* event){
    GraphWidget::coord_console(event);
    std::vector<console_point> all_value;
    int num_points=0;

    std::vector<console_point> all_value_2;
    int num_points_2=0;

    std::vector<console_point> all_value_3;
    int num_points_3=0;

    fill_value(All_op, all_value, height(), width(), num_points);
    if (!All_op_2.empty()) fill_value(All_op_2, all_value_2, height(), width(), num_points_2);
    if (!All_op_3.empty()) fill_value(All_op_3, all_value_3, height(), width(), num_points_3);

    GraphWidget::draw_graphic(all_value, num_points, graphColor[0]);
    GraphWidget::draw_graphic(all_value_2, num_points_2, graphColor[1]);
    GraphWidget::draw_graphic(all_value_3, num_points_3, graphColor[2]);

    all_value.clear();
    all_value_2.clear();
    all_value_3.clear();
}


void show_list_2(std::list<std::string> All_op){
    std::list<std::string>::iterator iter;
    for (iter=All_op.begin(); iter!=All_op.end(); ++iter){
        std::cout<<*iter<<std::endl;
    }
}

void show_vector(std::vector<console_point> all_value, int n){
    for (int i=0; i<n; i++){
        std::cout<<all_value[i].x<<"-"<<all_value[i].y<<std::endl;
    }
}
