#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int LabelTurn;
    int randomNumber;
    bool gameover;
    bool win;
    void showResult();
    void clearScreen();
    void generate_random_number();

private slots:
    void numPressed();
    void start_new_game();
    void on_pushButton_released();
    void on_pushButton_10_released();
    void on_pushButton_1_clicked();
};
#endif // MAINWINDOW_H
