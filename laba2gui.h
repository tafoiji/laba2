#ifndef LABA2GUI_H
#define LABA2GUI_H

#include <QMainWindow>
#include <QWidget>
#include <QImage>
#include <QMenu>
#include <QAction>
#include <QMenuBar>
#include <QTableWidget>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QDirIterator>
#include <QImageWriter>

QT_BEGIN_NAMESPACE
namespace Ui { class Laba2Gui; }
QT_END_NAMESPACE

class Laba2Gui : public QMainWindow
{
    Q_OBJECT

public:
    Laba2Gui(QWidget *parent = nullptr);
    ~Laba2Gui();

    void drawTable(QVector<QString>);

private:
    Ui::Laba2Gui *ui;
    QTableWidget *table;

public slots:
    void openFile(bool);
    void openDirectory(bool);
};
#endif // LABA2GUI_H
