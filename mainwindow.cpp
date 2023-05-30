#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMimeData>
#include <QFileInfo>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QDir>
#include <QMessageBox>

#include "Plugins/ImageProcessPluginInterface.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    getPluginList();
    getImageViewPlugin();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    QStringList acceptedFileTypes;
    acceptedFileTypes.append("bmp");
    acceptedFileTypes.append("png");
    acceptedFileTypes.append("jpg");
    acceptedFileTypes.append("jpeg");

    if (event->mimeData()->hasUrls() && event->mimeData()->urls().count() == 1)
    {
        QFileInfo file(event->mimeData()->urls().at(0).toLocalFile());
        if (acceptedFileTypes.contains(file.suffix().toLower()))
            event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QFileInfo file(event->mimeData()->urls().at(0).toLocalFile());
    QImage image(file.absoluteFilePath());
    if (!image.isNull())
    {
        // 图片加入列表
        image.convertTo(QImage::Format_BGR888);
        imageList.clear();
        imageList.push_back(image);

        // 显示最新的图片
        if (imageViewPlugin)
            imageViewPlugin->showImage(image);
    }
}

void MainWindow::getPluginList()
{
    QDir filtersDir(qApp->applicationDirPath() + "/Plugins/MMPosePlugin");
    QFileInfoList filters = filtersDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files, QDir::Name);
    for (QFileInfo &filter : filters)
    {
        if(QLibrary::isLibrary(filter.absoluteFilePath()))
        {
            QPluginLoader pluginLoader(filter.absoluteFilePath(), this);
            if(dynamic_cast<ImageProcessPluginInterface*>(pluginLoader.instance()))
            {
                ui->listWidget->addItem(filter.fileName());
                pluginLoader.unload();
            }
            else
            {
                QMessageBox::warning(this, tr("Warning"), QString(tr("Make sure only plugins exist in plugins folder.<br>%1 is not a plugin.")).arg(filter.fileName()));
            }
        }
    }
    if(ui->listWidget->count() <= 0)
    {
        QMessageBox::critical(this, tr("No Plugins"), tr("This application cannot work without plugins!<br>Make sure the filter_plugins folder exists in the same folder as the application<br>and that there are some filter plugins inside it"));
        this->setEnabled(false);
    }
}

void MainWindow::getImageViewPlugin()
{
    QString plugin_path = "Plugins/ImageViewPlugin/libImageViewPlugin.so";
    if (QLibrary::isLibrary(plugin_path))
    {
        QPluginLoader plugin_loader(plugin_path, this);
        imageViewPlugin = dynamic_cast<ImageViewPluginInterface*>(plugin_loader.instance());
        if (imageViewPlugin)
        {
            QWidget *new_widget = imageViewPlugin->createWidget();
            ui->gridLayout_4->addWidget(new_widget);
        }
        else
        {
            QMessageBox::critical(this, tr("Warning"), QString(tr("%1 is not a plugin")).arg(plugin_path));
        }
    }
    else
    {
        QMessageBox::critical(this, tr("No Plugins"), tr("This application cannot work without plugins!<br>Make sure that there are view plugins inside it"));
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->listWidget->currentRow() >= 0)
    {
        QPluginLoader pluginLoader(qApp->applicationDirPath() + "/Plugins/MMPosePlugin/" + ui->listWidget->currentItem()->text());
        ImageProcessPluginInterface *plugin = dynamic_cast<ImageProcessPluginInterface*>(pluginLoader.instance());
        if (plugin)
        {
            if (!imageList.empty())
            {
                QImage output;
                plugin->processImage(imageList[0], output);

                if (imageViewPlugin)
                    imageViewPlugin->showImage(output);
            }
            else
            {
                QMessageBox::warning(this, tr("Warning"), QString(tr("No image")));
            }
        }
        else
        {
            QMessageBox::warning(this, tr("Warning"), QString(tr("Make sure plugin %1 exists and is usable.")).arg(ui->listWidget->currentItem()->text()));
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Warning"), QString(tr("First select a filter plugin from the list.")));
    }
}

