#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QDragEnterEvent>
#include <QDropEvent>

#include <QPluginLoader>
#include "Plugins/ImageViewPluginInterface.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QList<QImage> imageList;

    // 显示有关的内容
    void getImageViewPlugin();
    ImageViewPluginInterface *imageViewPlugin;

    // 图像处理插件
    void getPluginList();
 };
#endif // MAINWINDOW_H
