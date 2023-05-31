#include "mainwindow.h"
#include "./ui_mainwindow.h"

char graphColor[3] = {'r', 'g', 'b'};

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked__2);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
    connect(ui->changeColorButton, &QPushButton::clicked, this, &MainWindow::onChangeColorClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int num_func=1;
std::list<std::string> All_op;
std::list<std::string> All_op_2;
std::list<std::string> All_op_3;
void MainWindow::on_pushButton_clicked()
{
    QString function1 = ui->lineEdit->text();
    QString function2 = "";
    QString function3 = "";
    if (secondLineEdit) {
        function2 = secondLineEdit->text();
        num_func+=1;
    }
    if (thirdLineEdit) {
        function3 = thirdLineEdit->text();
        num_func+=1;
    }

    /*function1.replace(" ", "");
    function1=function1.mid(2);
    function1.replace("pi", "3.14159");
    function1.replace("e", "2.71828");

    int j=0;
    while (j<function1.length()-1){
        if (isdigit(function1.at(j).toLatin1()) and function1.at(j+1)=='x'){
            function1.insert(j+1, '*');
            j++;
        }
        j++;
    }

    int i=0;
    if (function1.at(0)=='-'){
        function1.insert(0,'0');
        i+=1;
    }
    while (i<function1.length()-1){
        if (function1.at(i)=='-'){
            if (function1.at(i-1)=='(' or i==0){
                function1.replace(i,1,"(-1)*");
            }
            else function1.replace(i,1,"+(-1)*");
            i+=2;
        }
        i+=1;
    }
    //function1.replace("-", "(-1)*") ;
    //make_easier(function1);*/

    if (function1!="") transformation(function1);
    if (function2!="") transformation(function2);
    if (function3!="") transformation(function3);

    int n=0;
    int n2=0;
    int n3=0;

    if (function1!="") get_all_op_2(All_op, function1, n);
    if (function2!="") get_all_op_2(All_op_2, function2, n2);
    if (function3!="") get_all_op_2(All_op_3, function3, n3);
    //show_list(All_op);
}


void MainWindow::on_pushButton_clicked__2(){
    GraphWidget *graphWidget = new GraphWidget(nullptr, All_op, All_op_2, All_op_3, num_func);
    //else if (num_func==2) GraphWidget *graphWidget = new GraphWidget(nullptr, All_op, All_op_2, num_func);
    //else GraphWidget *graphWidget = new GraphWidget(nullptr, All_op, All_op_2, All_op_3, num_func);
    //graphWidget->paintEvent(All_op);
    graphWidget->show();
    All_op.clear(); //очищаем чтобы при повторном вызове функция не искажалась
    All_op_2.clear();
    All_op_3.clear();
}

int m_counter=0;
void MainWindow::onAddButtonClicked(){
    if (m_counter == 0) {
        secondLineEdit = new QLineEdit(this);
        secondLineEdit->setFixedSize(QSize(491, 42));
        ui->verticalLayout_2->addWidget(secondLineEdit);
        QFont font("Segoe", 9);
        font.setItalic(true);
        secondLineEdit->setStyleSheet("background-color: white;");
        secondLineEdit->setFont(font);
        secondLineEdit->setPlaceholderText("Введите функцию...");
        secondLineEdit->setClearButtonEnabled(true);
        ui->pushButton->move(ui->pushButton->pos().x(), ui->pushButton->pos().y() + 20);
        m_counter++;
    } else if (m_counter == 1) {
        thirdLineEdit = new QLineEdit(this);
        thirdLineEdit->setFixedSize(QSize(491, 42));
        ui->verticalLayout_3->addWidget(thirdLineEdit);
        QFont font("Segoe", 9);
        font.setItalic(true);
        thirdLineEdit->setStyleSheet("background-color: white;");
        thirdLineEdit->setFont(font);
        thirdLineEdit->setPlaceholderText("Введите функцию...");
        thirdLineEdit->setClearButtonEnabled(true);
        ui->pushButton->move(ui->pushButton->pos().x(), ui->pushButton->pos().y() + 35);
        ui->addButton->hide();
    }
}


void MainWindow::onChangeColorClicked() {
    for(int i = 0; i < 3; i++) {
        if (graphColor[i] == 'r')
            graphColor[i] = 'g';
        else if (graphColor[i] == 'g')
            graphColor[i] = 'b';
        else
            graphColor[i] = 'r';
    }
}


