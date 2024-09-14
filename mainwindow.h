#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <String>
#include <QMessageBox>
#include <QString>
#include <iostream>
#include <vector>

#include <chrono>
#include <Windows.h>
#include <thread>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool flag_step = false;
    int count_step = 0;
    int param_count_columns = 0;

    void boyerMooreStep(QString pattern, int pattern_size);
    void boyerMoore(char* text, int text_size, char* pattern, int pattern_size);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_search_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
