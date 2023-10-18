#include "laba2gui.h"
#include "ui_laba2gui.h"

Laba2Gui::Laba2Gui(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Laba2Gui), table(new QTableWidget(0, 5))
{
    ui->setupUi(this);

    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *menu = new QMenu("Open..", this);
    QAction* opFile = new QAction("Open File(s)", this);
    QAction* opDir = new QAction("Open Directory", this);
    menu->addAction(opFile);
    menu->addAction(opDir);
    connect(opFile, SIGNAL(triggered(bool)), this, SLOT(openFile(bool)));
    connect(opDir, SIGNAL(triggered(bool)), this, SLOT(openDirectory(bool)));

    menuBar->addMenu(menu);
    this->setMenuBar(menuBar);
}

Laba2Gui::~Laba2Gui()
{
    delete ui;
}

void Laba2Gui::drawTable(QVector<QString> vec)
{
    delete table;
    table = new QTableWidget(0,5);

    QStringList headerLabels;
    headerLabels << "Name" << "Resloution" << "DPI" << "Color Deep" << "Compression";
    table->setHorizontalHeaderLabels(headerLabels);

    for (auto& name: vec)
    {
        QImage image;
        image.load(name);
        QString fileName = name.split('/').back();
        QTableWidgetItem* temp = new QTableWidgetItem();
        table->insertRow(table->rowCount());
        temp->setText(QString::number(image.width()) + "x" + QString::number(image.height()));
        table->setItem(table->rowCount() - 1, 1, temp);

        QTableWidgetItem* temp2 = new QTableWidgetItem();
        temp2->setText(fileName);
        table->setItem(table->rowCount() - 1, 0, temp2);

        QTableWidgetItem* temp3 = new QTableWidgetItem();
        qreal dpi = (image.logicalDpiX() + image.logicalDpiY()) / 2;
        temp3->setText(QString::number(dpi));
        table->setItem(table->rowCount() - 1, 2, temp3);

        QTableWidgetItem* temp4 = new QTableWidgetItem();
        temp4->setText(QString::number(image.bitPlaneCount()));
        table->setItem(table->rowCount() - 1, 3, temp4);

        QTableWidgetItem* temp5 = new QTableWidgetItem();
        QImageWriter imwr(name);
        temp5->setText(QString::number(imwr.compression()));
        table->setItem(table->rowCount() - 1, 4, temp5);
    }

    this->setCentralWidget(table);
}

void Laba2Gui::openFile(bool)
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setFileMode(QFileDialog::AnyFile);
    QStringList fileName = fileDialog->getOpenFileNames(this, tr("Open Image"), "C:/", tr("Image Files (*.png *.jpg *.bmp *.gif *.tiff *.pcx)"));
    QVector<QString> vec;
    for (auto& item: fileName)
    {
        vec.append(item);
    }

    drawTable(vec);
}

void Laba2Gui::openDirectory(bool)
{
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setFileMode(QFileDialog::Directory);
    QString path = fileDialog->getExistingDirectory(this, tr("Choose directory"), "C:/");
    QVector<QString> vec;
    QDirIterator it(path, {"*.png",  "*.jpg",  "*.bmp", "*.gif",  "*.tiff", "*.pcx"} , QDir::Files);

    while (it.hasNext())
    {
        QString filePath = it.next();
        vec.append(filePath);
    }


    drawTable(vec);
}

