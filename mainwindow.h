#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QGraphicsPathItem>
#include <QColorDialog>
#include "our_classes.h"

//#include "parsing.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_clicked__2();
    void onAddButtonClicked();
    void onChangeColorClicked();
private:
    Ui::MainWindow *ui;
    QLineEdit* secondLineEdit = nullptr;
    QLineEdit* thirdLineEdit = nullptr;
};
#endif // MAINWINDOW_H

