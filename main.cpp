#include "mainwindow.h"
#include <QApplication>

uint8_t mass[3][406] = {SYNCHRO, 0x01, 0x96, UART_ADDR, ADC_CONT_1SEC
                         , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x02, 0xF7, 0x04, 0xA7, 0x02, 0xA7, 0x05, 0xA7, 0x02, 0x37, 0x06, 0xA7, 0x01, 0xE7, 0x05, 0xA7, 0x01, 0x67, 0x04, 0xA7
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96,
                         0x00,
                        SYNCHRO, 0x01, 0x96, UART_ADDR, ADC_CONT_1SEC
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x03, 0x90, 0x03, 0x96, 0x07, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x02, 0xF7, 0x04, 0xA7, 0x02, 0xA7, 0x05, 0xA7, 0x02, 0x37, 0x06, 0xA7, 0x01, 0xE7, 0x05, 0xA7, 0x01, 0x67, 0x04, 0xA7
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96,
                        0x00,
                        SYNCHRO, 0x01, 0x96, UART_ADDR, ADC_CONT_1SEC
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x02, 0xF7, 0x04, 0xA7, 0x02, 0xA7, 0x05, 0xA7, 0x02, 0x37, 0x06, 0xA7, 0x01, 0xE7, 0x05, 0xA7, 0x01, 0x67, 0x04, 0xA7
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                        , 0x03, 0x90, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x97, 0x03, 0x94, 0x03, 0xA1, 0x03, 0x96, 0x03, 0x96, 0x03, 0x8F, 0x03, 0x93
                        , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96,
                        0x00};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
