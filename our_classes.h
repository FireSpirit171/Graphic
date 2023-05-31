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















































/*
class Function {
public:
    virtual ~Function()=default;
    virtual double evaluate(double x) const = 0;
    using FunctionPtr = std::unique_ptr<Function>;
};

class LinearFunction : public Function {
private:
    double k, b;
public:
    LinearFunction(double k, double b) : k(k), b(b) {}
    double evaluate(double x) const override { return k * x + b; }
};

class Token {
public:
    enum Type {
        Invalid,
        Plus,
        Minus,
        Multiply,
        Divide,
        Power,
        Function,
        Number,
        Variable
    };

    Type type;
    QString value;
    int precedence;

    Token() : type(Invalid), precedence(0) {}
    Token(Type type, const QString& value = "") : type(type), value(value), precedence(0) {}
    Type getType() const {
        return type;
    }

};

class Tokenizer {
public:
    Tokenizer(const QString& expression) : expression(expression.toStdString()) {}
    Tokenizer(const std::string& expression) : expression(expression) {}
    std::vector<Token> tokenize();

private:
    std::string expression;
};


class Ln : public Function {
public:
    double evaluate(double x) const override {
        if (x <= 0) {
            throw std::domain_error("Ln argument must be positive");
        }
        return log(x);
    }
};


class FactoryFunction {
public:
    virtual std::unique_ptr<Function> createFunction(const Token& token) const = 0;
};


class LnFactory : public FactoryFunction {
public:
    std::unique_ptr<Function> createFunction(const Token& token) const override {
        if (token.type != Token::Function || token.value != "ln") {
            return nullptr;
        }
        return std::make_unique<Ln>();
    }
};

class Sin : public Function {
public:
    double evaluate(double x) const override {
        return sin(x);
    }
};

class SinFactory : public FactoryFunction {
public:
    std::unique_ptr<Function> createFunction(const Token& token) const override {
        return std::make_unique<Sin>();
    }
};

class Cos : public Function {
public:
    double evaluate(double x) const override {
        return cos(x);
    }
};

class CosFactory : public FactoryFunction {
public:
    std::unique_ptr<Function> createFunction(const Token& token) const override {
        return std::make_unique<Cos>();
    }
};*/
















































/*
class Function {
public:
    virtual ~Function()=default;
    virtual double evaluate(double x) const = 0;
    using FunctionPtr = std::unique_ptr<Function>;
};

class LinearFunction : public Function {
private:
    double k, b;
public:
    LinearFunction(double k, double b) : k(k), b(b) {}
    double evaluate(double x) const override { return k * x + b; }
};

class Token {
public:
    enum Type {
        Invalid,
        Plus,
        Minus,
        Multiply,
        Divide,
        Power,
        Function,
        Number,
        Variable
    };

    Type type;
    QString value;
    int precedence;

    Token() : type(Invalid), precedence(0) {}
    Token(Type type, const QString& value = "") : type(type), value(value), precedence(0) {}
    Type getType() const {
        return type;
    }

};

class Tokenizer {
public:
    Tokenizer(const QString& expression) : expression(expression.toStdString()) {}
    Tokenizer(const std::string& expression) : expression(expression) {}
    std::vector<Token> tokenize();

private:
    std::string expression;
};


class Ln : public Function {
public:
    double evaluate(double x) const override {
        if (x <= 0) {
            throw std::domain_error("Ln argument must be positive");
        }
        return log(x);
    }
};


class FactoryFunction {
public:
    virtual std::unique_ptr<Function> createFunction(const Token& token) const = 0;
};


class LnFactory : public FactoryFunction {
public:
    std::unique_ptr<Function> createFunction(const Token& token) const override {
        if (token.type != Token::Function || token.value != "ln") {
            return nullptr;
        }
        return std::make_unique<Ln>();
    }
};

class Sin : public Function {
public:
    double evaluate(double x) const override {
        return sin(x);
    }
};

class SinFactory : public FactoryFunction {
public:
    std::unique_ptr<Function> createFunction(const Token& token) const override {
        return std::make_unique<Sin>();
    }
};

class Cos : public Function {
public:
    double evaluate(double x) const override {
        return cos(x);
    }
};

class CosFactory : public FactoryFunction {
public:
    std::unique_ptr<Function> createFunction(const Token& token) const override {
        return std::make_unique<Cos>();
    }
};*/
