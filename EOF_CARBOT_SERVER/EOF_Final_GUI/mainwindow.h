#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket> // ADD for Communication
#include <QDebug> // ADD for Debug
#include <QTextStream> // ADD for message handling
#include <QString> // ADD for String

#include <QImage> // ADD for Image
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots: // call back function public slots --> QT 에서 정의된 기능
    void video1_receive();
    void video2_receive();
    void video3_receive();

    void control1_send(QByteArray data);
    void control2_send(QByteArray data);
    void control3_send(QByteArray data);

    QByteArray joyStick1_receive();
    QByteArray joyStick2_receive();
    QByteArray joyStick3_receive();

private slots:
    void on_pushButtonControl1_clicked();
    void on_pushButtonControl2_clicked();
    void on_pushButtonControl3_clicked();

private:
    QUdpSocket *video1_socket;
    QUdpSocket *video2_socket;
    QUdpSocket *video3_socket;
    QUdpSocket *control1_socket;
    QUdpSocket *control2_socket;
    QUdpSocket *control3_socket;
    QUdpSocket *joyStick1_socket;
    QUdpSocket *joyStick2_socket;
    QUdpSocket *joyStick3_socket;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
