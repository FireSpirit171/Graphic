#ifndef OUR_CLASSES_H
#define OUR_CLASSES_H

#include <QStack>
#include <QString>
#include <QWidget>
#include <QPainter>
#include <QRegularExpression>
#include <QStringList>
#include <QPushButton>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <cstring>

#include "parsing.h"

class console_point{
private:
    double x;
    double y;
public:
    console_point() : x(0), y(0) {}
    console_point(double a, double b): x(a), y(b){}
    console_point(const console_point& other) : x(other.x), y(other.y) {}
    console_point& operator=(const console_point& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
        }
        return *this;
    }
    friend void fill_value(std::list<std::string>& All_op, std::vector<console_point> &all, int Y, int X, int& num_points);
    friend void show_vector(std::vector<console_point> all_value, int n);
    friend class GraphWidget;
};

class GraphWidget : public QWidget {
    Q_OBJECT
private:
    int prevWidth;
    int prevHeight;
    std::list<std::string> All_op;
    std::list<std::string> All_op_2;
    std::list<std::string> All_op_3;
    int num_func;

protected:
    void coord_console(QPaintEvent* event);

public:
    GraphWidget(QWidget* parent=nullptr, const std::list<std::string> All_op = std::list<std::string>(), const std::list<std::string> All_op_2 = std::list<std::string>(), const std::list<std::string> All_op_3 = std::list<std::string>(),
                int prevWidth=0, int prevHeight=0): QWidget(parent), All_op(All_op), All_op_2(All_op_2), All_op_3(All_op_3), prevWidth(prevWidth), prevHeight(prevHeight), num_func(num_func) {}
    void draw_graphic(std::vector<console_point>& all_values, int num_points, char color);
    void paintEvent(QPaintEvent* event);
};

void show_list_2(std::list<std::string> All_op);
void show_vector(std::vector<console_point> all_value, int n);

#endif // OUR_CLASSES_H

