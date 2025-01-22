#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QLineEdit>

#include "datagetter.h"

#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    QLabel* cityNameLbl;
    QLabel* weatherDescrLbl;
    QLabel* weatherImageLbl;
    QLabel* currentTempLbl;
    QLabel* feelLikeLbl;
    QLabel* windLbl;

    QPushButton* findBtn;
    QLineEdit* locationField;

    DataGetter* dataManager;

    void updateData(DataGetter* dataManager);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

};
#endif // MAINWINDOW_H
