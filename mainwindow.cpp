#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("BoyerMoor");
    ui->lineEdit_result->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

const int MAX_CHAR = 256;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int div_up(int x, int y)
{
    return (x + y - 1) / y;
}

void MainWindow::boyerMooreStep(QString pattern, int pattern_size){
    QString search_value = "";
    for (int i = 0; i < pattern_size; i++){
        search_value += pattern[i];
    }

    if (ui->tableWidget->item(0, count_step)->text() == search_value){
        ui->tableWidget->item(0, count_step)->setBackground(Qt::green);
    } else{
        ui->tableWidget->item(0, count_step)->setBackground(Qt::red);
    }
    ui->lineEdit_step->setText(QString::number(count_step));
    count_step++;
}

void MainWindow::boyerMoore(char* text, int text_size, char* pattern, int pattern_size) {
    string positions = "";
    int count_column = 0;

    int shiftTable[256];

    for (int i = 0; i < 256; i++) {
        shiftTable[i] = pattern_size;
    }

    for (int i = 0; i < pattern_size - 1; i++) {
        shiftTable[(int)pattern[i]] = pattern_size - 1 - i;
    }

    int i = 0;
    while (i <= text_size - pattern_size) {
        int j = pattern_size - 1;

        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }
        if (j < 0) {
            positions += to_string(i) + " ";
            i += shiftTable[(int)text[i + pattern_size]];
        } else {
            i += shiftTable[(int)text[i + j]];
        }

        count_column++;
    }

    param_count_columns = count_column;

    ui->lineEdit_result->setText(QString::fromStdString(positions));

    ui->lineEdit_result->setText(QString::fromStdString(positions));
    ui->lineEdit_result->setVisible(true);

    ui->tableWidget->setColumnCount(count_column);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    // Разрешаем выделение построчно
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Ресайзим колонки по содержимому
    ui->tableWidget->resizeColumnsToContents();

    i = 0;
    int ind_column = 0;
    while (i <= text_size - pattern_size) {
        int j = pattern_size - 1;

        while (j >= 0 && pattern[j] == text[i + j]) {
            j--;
        }

        string value = "";
        for (int ind = i; ind < i + pattern_size; ind++){
            value += text[ind];
        }
        QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(value));
        ui->tableWidget->setItem(0, ind_column, item);


        if (j < 0) {
            if(flag_step == false){
                ui->tableWidget->item(0, ind_column)->setBackground(Qt::green);
            }
            i += shiftTable[(int)text[i + pattern_size]];
        } else {
            if(flag_step == false){
                ui->tableWidget->item(0, ind_column)->setBackground(Qt::red);
            }
            i += shiftTable[(int)text[i + j]];
        }

        ind_column++;
    }
    if (flag_step == true){
        QString search_;
        for (int i = 0; i < pattern_size; i++){
            search_ += QString::fromStdString(std::string(1, pattern[i]));
        }
        if (count_step < count_column){
            MainWindow::boyerMooreStep(search_, pattern_size);
        } else{
            QMessageBox::critical(this, "Error", "Index out of range");
            return;
        }
    }

}


void MainWindow::on_pushButton_search_clicked()
{
    char text[MAX_CHAR];
    int text_size;
    int now_index = 0;
    for (auto now_char : (ui->lineEdit_text->text()).toStdString()){
        text[now_index] = now_char;
        now_index++;
    }
    text_size = now_index;

    now_index = 0;
    char pattern[MAX_CHAR];
    int pattern_size;
    for (auto now_char : (ui->lineEdit_pattern->text()).toStdString()){
        pattern[now_index] = now_char;
        now_index++;
    }
    pattern_size = now_index;

    if(text_size == 0 || pattern_size == 0) {
        QMessageBox::critical(this, "Error", "Text and pattern cannot be empty");
        return;
    }

    MainWindow::boyerMoore(text, text_size, pattern, pattern_size);
}


void MainWindow::on_pushButton_clicked()
{
    flag_step = true;

    char text[MAX_CHAR];
    int text_size;
    int now_index = 0;
    for (auto now_char : (ui->lineEdit_text->text()).toStdString()){
        text[now_index] = now_char;
        now_index++;
    }
    text_size = now_index;

    now_index = 0;
    char pattern[MAX_CHAR];
    int pattern_size;
    for (auto now_char : (ui->lineEdit_pattern->text()).toStdString()){
        pattern[now_index] = now_char;
        now_index++;
    }
    pattern_size = now_index;

    boyerMoore(text, text_size, pattern, pattern_size);
}
