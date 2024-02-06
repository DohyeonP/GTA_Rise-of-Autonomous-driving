#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 * UDP 통신 IP Address / Port 설정
 *
 * 영상 수신
 * video1 : 10.10.15.aa / 1111
 * video2 : 10.10.15.bb / 2222
 * video3 : 10.10.15.cc / 3333
 *
 * 조이스틱 조종 송신
 * control1 : 10.10.15.aa / 4444
 * control2 : 10.10.15.bb / 5555
 * control3 : 10.10.15.cc / 6666
 *
 * 조이스틱 조종 수신
 * joyStick1 : 20.20.40.aa / 7777
 * joyStick2 : 20.20.40.bb / 8888
 * joyStick3 : 20.20.40.cc / 9999
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // video 1
    video1_socket = new QUdpSocket(this);
    bool video1_result = video1_socket->bind(QHostAddress::AnyIPv4, 1111);
    qDebug() << video1_result;
    if (video1_result) qDebug() << "V1 PASS";
    else qDebug() << "V1 FAIL";
    connect(video1_socket, SIGNAL(video1_receive()), this, SLOT(video1_receive()));

    // video 2
    video2_socket = new QUdpSocket(this);
    bool video2_result = video2_socket->bind(QHostAddress::AnyIPv4, 2222);
    qDebug() << video2_result;
    if (video2_result) qDebug() << "V2 PASS";
    else qDebug() << "V2 FAIL";
    connect(video2_socket, SIGNAL(video2_receive()), this, SLOT(video2_receive()));

    // video 3
    video3_socket = new QUdpSocket(this);
    bool video3_result = video3_socket->bind(QHostAddress::AnyIPv4, 3333);
    qDebug() << video3_result;
    if (video3_result) qDebug() << "V3 PASS";
    else qDebug() << "V3 FAIL";
    connect(video3_socket, SIGNAL(video3_receive()), this, SLOT(video3_receive()));

    // control 1
    control1_socket = new QUdpSocket(this);
    bool control1_result = control1_socket->bind(QHostAddress::AnyIPv4, 4444);
    qDebug() << control1_result;
    if (control1_result) qDebug() << "C1 PASS";
    else qDebug() << "C1 FAIL";
    connect(control1_socket, SIGNAL(control1_send()), this, SLOT(control1_send()));

    // control 2
    control2_socket = new QUdpSocket(this);
    bool control2_result = control2_socket->bind(QHostAddress::AnyIPv4, 5555);
    qDebug() << control2_result;
    if (control2_result) qDebug() << "C2 PASS";
    else qDebug() << "C2 FAIL";
    connect(control2_socket, SIGNAL(control2_send()), this, SLOT(control2_send()));

    // control 3
    control3_socket = new QUdpSocket(this);
    bool control3_result = control3_socket->bind(QHostAddress::AnyIPv4, 6666);
    qDebug() << control3_result;
    if (control3_result) qDebug() << "C3 PASS";
    else qDebug() << "C3 FAIL";
    connect(control3_socket, SIGNAL(control3_send()), this, SLOT(control3_send()));

    // joy stick 1
    joyStick1_socket = new QUdpSocket(this);
    bool joyStick1_result = joyStick1_socket->bind(QHostAddress::AnyIPv4, 7777);
    qDebug() << joyStick1_result;
    if (joyStick1_result) qDebug() << "J1 PASS";
    else qDebug() << "J1 FAIL";
    connect(joyStick1_socket, SIGNAL(joyStick1_receive()), this, SLOT(joyStick1_receive()));

    // joy stick 2
    joyStick2_socket = new QUdpSocket(this);
    bool joyStick2_result = joyStick2_socket->bind(QHostAddress::AnyIPv4, 8888);
    qDebug() << joyStick2_result;
    if (joyStick2_result) qDebug() << "J2 PASS";
    else qDebug() << "J2 FAIL";
    connect(joyStick2_socket, SIGNAL(joyStick2_receive()), this, SLOT(joyStick2_receive()));

    // joy stick 3
    joyStick3_socket = new QUdpSocket(this);
    bool joyStick3_result = joyStick3_socket->bind(QHostAddress::AnyIPv4, 9999);
    qDebug() << joyStick3_result;
    if (joyStick3_result) qDebug() << "J3 PASS";
    else qDebug() << "J3 FAIL";
    connect(joyStick3_socket, SIGNAL(joyStick3_receive()), this, SLOT(joyStick3_receive()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void  MainWindow::video1_receive()
{
    QByteArray Buffer;
    QHostAddress sender; // 송신자의 IP
    quint16 senderPort; // 송신자의 SW PORT

    QImage *img = new QImage();
    QPixmap *px_buf = new QPixmap();

    Buffer.resize(video1_socket->pendingDatagramSize());
    video1_socket->readDatagram(Buffer.data(), Buffer.size(), &sender, &senderPort);

    if(img->loadFromData(Buffer))
    {
        *px_buf = QPixmap::fromImage(*img);
        *px_buf = px_buf->scaled(img->width(), img->height());
        ui->labelCam1->setPixmap(*px_buf);
        ui->labelCam1->resize(px_buf->width(), px_buf->height());
        ui->labelCam1->show();
    }
}

void MainWindow::video2_receive()
{
    QByteArray Buffer;
    QHostAddress sender; // 송신자의 IP
    quint16 senderPort; // 송신자의 SW PORT

    QImage *img = new QImage();
    QPixmap *px_buf = new QPixmap();

    Buffer.resize(video2_socket->pendingDatagramSize());
    video2_socket->readDatagram(Buffer.data(), Buffer.size(), &sender, &senderPort);

    if(img->loadFromData(Buffer))
    {
        *px_buf = QPixmap::fromImage(*img);
        *px_buf = px_buf->scaled(img->width(), img->height());
        ui->labelCam2->setPixmap(*px_buf);
        ui->labelCam2->resize(px_buf->width(), px_buf->height());
        ui->labelCam2->show();
    }
}

void MainWindow::video3_receive()
{
    QByteArray Buffer;
    QHostAddress sender; // 송신자의 IP
    quint16 senderPort; // 송신자의 SW PORT

    QImage *img = new QImage();
    QPixmap *px_buf = new QPixmap();

    Buffer.resize(video3_socket->pendingDatagramSize());
    video3_socket->readDatagram(Buffer.data(), Buffer.size(), &sender, &senderPort);

    if(img->loadFromData(Buffer))
    {
        *px_buf = QPixmap::fromImage(*img);
        *px_buf = px_buf->scaled(img->width(), img->height());
        ui->labelCam3->setPixmap(*px_buf);
        ui->labelCam3->resize(px_buf->width(), px_buf->height());
        ui->labelCam3->show();
    }
}

void MainWindow::control1_send(QByteArray data)
{
    // receiver 는 video1 의 IP 주소, port 는 4444
    // control1_socket->writeDatagram(data.data(), &receiver, &receiverPort);
    control1_socket->writeDatagram(data, QHostAddress("10.10.15.00"), 4444);
}

void MainWindow::control2_send(QByteArray data)
{
    // receiver 는 video2 의 IP 주소, port 는 5555
    // control1_socket->writeDatagram(data.data(), &receiver, &receiverPort);
    control2_socket->writeDatagram(data, QHostAddress("10.10.15.00"), 5555);
}

void MainWindow::control3_send(QByteArray data)
{
    // receiver 는 video3 의 IP 주소, port 는 6666
    // control1_socket->writeDatagram(data.data(), &receiver, &receiverPort);
    control3_socket->writeDatagram(data, QHostAddress("10.10.15.00"), 6666);
}


QByteArray MainWindow::joyStick1_receive()
{
    QByteArray Buffer;
    QHostAddress sender; // 송신자의 IP
    quint16 senderPort; // 송신자의 SW PORT

    Buffer.resize(joyStick1_socket->pendingDatagramSize());
    joyStick1_socket->readDatagram(Buffer.data(), Buffer.size(), &sender, &senderPort);

    return Buffer;
}

QByteArray MainWindow::joyStick2_receive()
{
    QByteArray Buffer;
    QHostAddress sender; // 송신자의 IP
    quint16 senderPort; // 송신자의 SW PORT

    Buffer.resize(joyStick2_socket->pendingDatagramSize());
    joyStick2_socket->readDatagram(Buffer.data(), Buffer.size(), &sender, &senderPort);

    return Buffer;
}

QByteArray MainWindow::joyStick3_receive()
{
    QByteArray Buffer;
    QHostAddress sender; // 송신자의 IP
    quint16 senderPort; // 송신자의 SW PORT

    Buffer.resize(joyStick3_socket->pendingDatagramSize());
    joyStick3_socket->readDatagram(Buffer.data(), Buffer.size(), &sender, &senderPort);

    return Buffer;
}

void MainWindow::on_pushButtonControl1_clicked()
{
    QByteArray receive_data = joyStick1_receive();

    // 여기 수정해야 함
    // 조이스틱에서 어떤 데이터가 오는 지 모르기 때문에 임시로 설정 함
    // 데이터에 맞게 변환해서 보내야 함
    if (receive_data == "up") control1_send("up");
    else if (receive_data == "down") control1_send("down");

}

void MainWindow::on_pushButtonControl2_clicked()
{
    QByteArray receive_data = joyStick2_receive();

    // 여기 수정해야 함
    // 조이스틱에서 어떤 데이터가 오는 지 모르기 때문에 임시로 설정 함
    // 데이터에 맞게 변환해서 보내야 함
    if (receive_data == "up") control2_send("up");
    else if (receive_data == "down") control2_send("down");
}

void MainWindow::on_pushButtonControl3_clicked()
{
    QByteArray receive_data = joyStick3_receive();

    // 여기 수정해야 함
    // 조이스틱에서 어떤 데이터가 오는 지 모르기 때문에 임시로 설정 함
    // 데이터에 맞게 변환해서 보내야 함
    if (receive_data == "up") control3_send("up");
    else if (receive_data == "down") control3_send("down");
}
