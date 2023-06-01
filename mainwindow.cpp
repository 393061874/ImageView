#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMimeData>
#include <QFileInfo>
#include <QLabel>
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
    setImageViewPlugin();
    getPluginList();
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
        imageViewPlugin->append(image);
    }
}

void MainWindow::setImageViewPlugin()
{
    QString plugin_path = "Plugins/ImageViewPlugin/libImageViewPlugin.so";
    if (QLibrary::isLibrary(plugin_path))
    {
        QPluginLoader plugin_loader(plugin_path, this);
        imageViewPlugin = dynamic_cast<ImageViewPluginInterface*>(plugin_loader.instance());
        if (imageViewPlugin)
        {
            // 替换占位组件
            ui->gridLayout->removeWidget(ui->widget);
            delete ui->widget;
            ui->gridLayout->addWidget(imageViewPlugin->toWidget(), 0, 1, 1, 1);
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

    // 准备控件

    //tab_Source = new QWidget();
    //tab_Source->setObjectName("tab_Source");
    //gridLayout_Source = new QGridLayout(tab_Source);
    //gridLayout_Source->setObjectName("gridLayout_Source");
    //label_Image = new QLabel(tab_Source);
    //label_Image->setObjectName("label_Image");

    //gridLayout_Source->addWidget(label_Image, 0, 0, 1, 1);

    //tabWidget_ImageView->addTab(tab_Source, QString());


//    QPixmap image("image.jpeg");
//    QLabel *label_Source = new QLabel(ui->tab_Source);
//    label_Source->setObjectName("label_Source");
//    ui->gridLayout_Source->addWidget(label_Source, 0, 0, 1, 1);

//    QSize show_size = label_Source->size();
//    label_Source->setPixmap(image.scaled(image.size() / 3));
//    label_Source->setScaledContents(true);
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


void MainWindow::on_pushButton_clicked()
{
    if(ui->listWidget->currentRow() >= 0)
    {
        QPluginLoader pluginLoader(qApp->applicationDirPath() + "/Plugins/MMPosePlugin/" + ui->listWidget->currentItem()->text());
        ImageProcessPluginInterface *plugin = dynamic_cast<ImageProcessPluginInterface*>(pluginLoader.instance());
        if (plugin)
        {
            //if (!imageList.empty())
            {
                QImage output;
                //plugin->processImage(imageList[0], output);

                //if (imageViewPlugin)
                //    imageViewPlugin->showImage(output);
            }
            //else
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

