#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::requestFromServer()
{
    QNetworkRequest networkRequest;
    QUrl url;

    // connect the networkManager to an SLOT, this SLOT is triggered when the network request finish
    connect(&networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(receiveFromServer(QNetworkReply*)));
    url.setUrl(ui->lineEdit->text());
    networkRequest.setUrl(QUrl(url));  // url for the network file, a text file in this case
    networkManager.get(networkRequest);  // make the request to server using the POST method
}

void MainWindow::receiveFromServer(QNetworkReply *networkReply)
{
    QByteArray postData; // store the data returned on the networkReply
    QPixmap pixmap;

    // the networkReply contains returned data from the server when the network request is finished
    postData=networkReply->readAll(); // put received QByteArray data into postData object
    pixmap.loadFromData(postData); // copy to the pixmap object
    ui->labelPixmap->setPixmap(pixmap);  // show the picture content in labelPixmap
}

void MainWindow::on_pushButton_clicked()
{
    requestFromServer();
}
