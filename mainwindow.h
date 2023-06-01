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

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    // 图片显示插件
    ImageViewPluginInterface *imageViewPlugin;
    void setImageViewPlugin();

    // 图像处理插件
    void getPluginList();
 };
#endif // MAINWINDOW_H
