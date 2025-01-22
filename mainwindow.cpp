#include "mainwindow.h"

void MainWindow::updateData(DataGetter* dataManager)
{
    cityNameLbl->setText(dataManager->getValue("name"));

    weatherDescrLbl->setText("\n" + dataManager->getValue("weatherdescription"));

    QPixmap pixmap(dataManager->getValue("weathericon"));
    weatherImageLbl->setPixmap(pixmap);

    currentTempLbl->setText(dataManager->getValue("temperature") + "℃");

    feelLikeLbl->setText("Feels like : " + dataManager->getValue("feelslike") + "℃");

    windLbl->setText("Wind : " + dataManager->getValue("windspeed") + " m/s, " +
                     dataManager->getValue("winddir"));

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(300, 400);
    setMaximumWidth(300);
    setMinimumWidth(300);
    setMaximumHeight(400);
    setMinimumHeight(400);

    dataManager = new DataGetter(this);

    QWidget* mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);
    setWindowTitle("Weather app");

    QVBoxLayout* vMainLayout = new QVBoxLayout();
    QHBoxLayout* hLevel1Layout = new QHBoxLayout();

    findBtn = new QPushButton("Find");
    locationField = new QLineEdit();
    locationField->setPlaceholderText("Enter location");

    hLevel1Layout->addWidget(locationField);
    hLevel1Layout->addWidget(findBtn);

    cityNameLbl = new QLabel("None");
    cityNameLbl->setAlignment(Qt::AlignCenter);
    QFont font = cityNameLbl->font();
    font.setPointSize(12);
    cityNameLbl->setFont(font);

    weatherDescrLbl = new QLabel("\nNone");
    weatherDescrLbl->setAlignment(Qt::AlignCenter);
    weatherDescrLbl->setFont(font);

    weatherImageLbl = new QLabel("");
    QPixmap pixmap(":/images/default.png");
    weatherImageLbl->setPixmap(pixmap);
    weatherImageLbl->setAlignment(Qt::AlignCenter);

    font.setPointSize(25);
    currentTempLbl = new QLabel("-℃");
    currentTempLbl->setAlignment(Qt::AlignCenter);
    currentTempLbl->setFont(font);

    feelLikeLbl = new QLabel("Feels like : -℃");
    feelLikeLbl->setAlignment(Qt::AlignCenter);
    font.setPointSize(12);
    feelLikeLbl->setFont(font);

    font.setPointSize(12);
    windLbl = new QLabel("Wind : - m/s, -");
    windLbl->setAlignment(Qt::AlignCenter);
    windLbl->setFont(font);

    vMainLayout->addWidget(cityNameLbl);
    vMainLayout->addWidget(weatherDescrLbl);
    vMainLayout->addWidget(weatherImageLbl);
    vMainLayout->addWidget(currentTempLbl);
    vMainLayout->addWidget(feelLikeLbl);
    vMainLayout->addWidget(windLbl);

    vMainLayout->addLayout(hLevel1Layout);
    mainWidget->setLayout(vMainLayout);

    connect(findBtn, &QPushButton::clicked, [this](){dataManager->requestInfo(locationField->text());});

    connect(dataManager, &DataGetter::gotData, [this](){updateData(dataManager);});
}

MainWindow::~MainWindow() {}
