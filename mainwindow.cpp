#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDateTime>

void callResult(MainWindow* ptr,int randomNumber);
void clearButtons(QMainWindow *ptr);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    setFixedSize(600, 470);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint); // Disable maximize button
    ui->setupUi(this);
    LabelTurn=1;
    QPushButton *numButton [10];
    for(int i=0; i<10;i++){
        QString butname = "pushButton_" + QString::number(i); // get buttons by
        numButton[i] = MainWindow::findChild<QPushButton *>(butname); // name
        connect(numButton[i],SIGNAL(released()), this, SLOT(numPressed()));
    }

    gameover=false;
    win=false;
    generate_random_number();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numPressed(){
    if (gameover) return;
    QPushButton *button = (QPushButton*) sender();
    QString buttonname = button->text();
    button->setEnabled(false);
    button->setStyleSheet("background-color: grey;");
    QString labelname = "label_" + QString::number(LabelTurn);
    QLabel* label =   MainWindow::findChild<QLabel *>(labelname);
    label->setText(buttonname);
    if (LabelTurn%4==0) {
        clearButtons(this); // enable the 4 buttons back
        showResult();
    }



    if (win){
        start_new_game();
    } else if (LabelTurn==32 || gameover){ // show the final results. Win or lose
        callResult(this,randomNumber);
        start_new_game();
    }else
        LabelTurn ++;
}


void MainWindow::showResult(){
    QString answer="";
    QString labelresnameName  = "res" + QString::number(LabelTurn / 4); // get the result label name
    QString labelthousandsName = "label_" + QString::number(LabelTurn-3);
    QString labelhundredsName = "label_" + QString::number(LabelTurn-2);
    QString labeltensName = "label_" + QString::number(LabelTurn-1);
    QString labelonesName = "label_" + QString::number(LabelTurn);

    QLabel *labelresname = MainWindow::findChild<QLabel *>(labelresnameName);
    QLabel *labelthousands = MainWindow::findChild<QLabel *>(labelthousandsName);
    QLabel *labelhundreds = MainWindow::findChild<QLabel *>(labelhundredsName);
    QLabel *labeltens = MainWindow::findChild<QLabel *>(labeltensName);
    QLabel *labelones = MainWindow::findChild<QLabel *>(labelonesName);

    int thousands = randomNumber/1000;
    int hundreds = (randomNumber%1000) / 100;
    int tens = (randomNumber%100) / 10;
    int ones = randomNumber%10;
    // manage pluses

    if (labelthousands->text().toInt() == thousands )
        answer= answer + "+";

    if (labelhundreds->text().toInt() == hundreds )
        answer= answer + "+";

    if (labeltens->text().toInt() == tens )
        answer= answer + "+";

    if (labelones->text().toInt() == ones )
        answer= answer + "+";


    // manage minuses
    if (labelthousands->text().toInt() == hundreds  || labelthousands->text().toInt() == tens
        || labelthousands->text().toInt() == ones)
        answer= answer + "-";

    if (labelhundreds->text().toInt() == thousands || labelhundreds->text().toInt() == tens ||
         labelhundreds->text().toInt() == ones)
        answer = answer + "-";


    if (labeltens->text().toInt() == thousands   || labeltens->text().toInt() == hundreds ||
        labeltens->text().toInt() == ones)
        answer = answer + "-";


    if (labelones->text().toInt() == thousands  || labelones->text().toInt() == hundreds || labelones->text().toInt()== tens)
        answer = answer + "-";


    // show the results in the dedicated label
    labelresname->setText(answer);

    if (answer=="++++"){
        QMessageBox::information(this, "", "You win!\n The number is " + QString::number( randomNumber));
        win=true;
    }
}

void MainWindow:: generate_random_number(){
    int  Thousands, hundreds, tens, ones;
    do { // generate a number. if any of the numbers is duplicated, repeat the random process
        QRandomGenerator randomGenerator;
        qint64 seed = QDateTime::currentMSecsSinceEpoch();
        randomGenerator.seed(seed);
        randomNumber = randomGenerator.bounded(10000);
        Thousands = randomNumber/1000;
        hundreds= (randomNumber%1000)/ 100;
        tens = (randomNumber%100)/10;
        ones = (randomNumber%10);
    } while (Thousands==hundreds || Thousands==tens || Thousands == ones || hundreds==tens || hundreds==ones || tens==ones);
}

void callResult(MainWindow *ptr,int randomNumber){
    QMessageBox::information(ptr, "", "Game is Over.\n You Lost.\n The number is " + QString::number(randomNumber) );
}

void MainWindow::clearScreen() {
    for (int i=1;i<33;i++){
        QString labelname = "label_" + QString::number(i);
        QLabel* label =   MainWindow::findChild<QLabel *>(labelname);
        label->setText("");
    }

    for (int i=1;i<9;i++){
        QString labelname = "res" + QString::number(i);
        QLabel* label =   MainWindow::findChild<QLabel *>(labelname);
        label->setText("");
    }

    LabelTurn=1;
}



void MainWindow::start_new_game()
{
    QMessageBox::information(this,"MasterMind", "Guess the number in 8 attempts. Good Luck!");
    generate_random_number();
    clearScreen();
    clearButtons(this);
    gameover= false;
    win=false;
}


void MainWindow::on_pushButton_released()
{
    start_new_game();
}


void MainWindow::on_pushButton_10_released()
{
    QMessageBox::information(this, "About","Programmed by Maan Haj Rachid");
}

void clearButtons(QMainWindow *ptr){
    for(int i=0; i<10;i++){
        QPushButton *numButton[10];
        QString butname = "pushButton_" + QString::number(i); // get buttons by
        numButton[i] = ptr->findChild<QPushButton *>(butname);
        numButton[i]->setStyleSheet( " QPushButton {border-radius: 10px;background-color: #00008B;font: 900 10pt \"Segoe UI\";color: yellow; } ");
        numButton[i]->setEnabled(true);
    }
}



