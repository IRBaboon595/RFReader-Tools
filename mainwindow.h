#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QTextEdit>
#include <iostream>
#include <windows.h>
#include <iostream>
#include <math.h>
#include <QtMath>
#include <time.h>
#include <locale.h>
#include <string.h>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <cstring>
#include <string>
#include <Shlwapi.h>
#include <iomanip>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QDialog>
#include <QTabWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <QTimer.h>
#include <qwt_plot.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>
#include <QFile>
#include <QTime>
#include <QTimer>
#include <QElapsedTimer>
#include <QMouseEvent>
#include <QLabel>
#include <QDataStream>
#include <QGroupBox>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
//#include <fftw3.h>

#define	SYNCHRO                     0x79
#define UART_ADDR                   0x0A
#define SERVICE_BITS_LEN            0x06

#define ECHO                        0x00
#define ADC_CONT_1SEC               0x01
#define GENERATION_CTRL             0x02
#define OUTPUT_SWITCH           	0x03
#define SET_ATT                 	0x04
#define AMP_MANAGE              	0x05
#define ADC_ECHO                    0x06
#define CRYSTAL_EN                  0x07
#define AD5932_CTR                  0x08
#define ADF4360_CTR                 0x09
#define SEND_FREQ_PARAM             0x0A
#define SEND_FREQ_PARAM_TOTAL       0x0B
#define MODE_SELECT                 0x0C


#define ON                          0x01
#define OFF                         0x00

#define MAXSIZE                     0x09

#define STOPPER                 	400                                      /* Smaller than any datum */
#define MEDIAN_FILTER_SIZE          (3)

#define LOW_PASS_FILTER_SIZE        (4)

#define AVERAGE_FILTER_SIZE         (3)

/******************************************* SWEEP DEFINES *******************************************/

#define SWEEP_LEN                   5000
#define RAW_AMMOUNT                 5

/******************************************* ADF4360 DEFINES ******************************************/

#define PRESC_8_9                   0
#define PRESC_16_17                 1
#define PRESC_32_33                 2

#define OUT_13                      0
#define OUT_11                      1
#define OUT_8                       2
#define OUT_6                       3

#define SINGLE_MODE                 0
#define AUTO_MODE                   1


extern              uint8_t mass[3][406];

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void mouseReleaseEvent(QMouseEvent *e);
    ~MainWindow();
    QSerialPort *COM;
    QPalette *pal;
    QwtPlot *plot;
    QwtPlotCurve *curve; // Кривая
    QwtPlotCurve *curve_DFT; // Кривая
    QPolygonF points;
    QPolygonF points_DFT;
    QwtPlot *spectre_graph;
    QwtPlotCurve *spectre_spurs; // Кривая
    QPolygonF spectre_points;
    QFile *File;
    QTime *Timer_Data;
    QTabWidget *TabS;
    QLabel  *out_message;
    QLineEdit *in_message;
    QWidget *first_tab;
    QWidget *second_tab;
    QWidget *third_tab;
    QWidget *fourth_tab;
    QWidget *fifth_tab;
    QDataStream fileStream;
    QGroupBox *crystal_group;
    QCheckBox *crystal_status;
    QPushButton *crystal_send;
    QGroupBox *ad5932_group;
    QCheckBox *msb_status;
    QCheckBox *signal_type_status;
    QCheckBox *ctrl_type_status;
    QLabel *freq_start_label;
    QLabel *freq_delta_label;
    QLabel *n_increment_label;
    QLabel *time_interval_label;
    QLineEdit *freq_start;
    QLineEdit *freq_delta;
    QLineEdit *n_increment;
    QLineEdit *time_interval;
    QPushButton *ad5932_send;
    QGroupBox *adf4360_group;
    QLabel              *a_counter_label;
    QLabel              *b_counter_label;
    QLabel              *r_counter_label;
    QLabel              *power_level_label;
    QLabel              *p_prescaler_label;
    QLineEdit           *a_counter;
    QLineEdit           *b_counter;
    QLineEdit           *r_counter;
    QComboBox           *power_level;
    QComboBox           *p_prescaler;
    QPushButton         *adf4360_send;
    QCheckBox           *test_radio_button;
    QCheckBox           *signal_type;
    uint8_t             signal_type_mode;

    QString file_string;
    QByteArray file_byte_array;
    quint32 file_log_number;

    QGroupBox *centerFreq;
    QGroupBox *deltaFreq;
    QGroupBox *stepFreq;
    QLineEdit *centerFreq_edit;
    QLineEdit *deltaFreq_edit;
    QLineEdit *stepFreq_edit;
    QPushButton *sendparamFreq;

    QGroupBox *antenna_1;
    QGroupBox *centerFreq_1;
    QGroupBox *deltaFreq_1;
    QGroupBox *stepFreq_1;
    QLineEdit *centerFreq_edit_1;
    QLineEdit *deltaFreq_edit_1;
    QLineEdit *stepFreq_edit_1;
    QComboBox *tag_select_1;

    QGroupBox *antenna_2;
    QGroupBox *centerFreq_2;
    QGroupBox *deltaFreq_2;
    QGroupBox *stepFreq_2;
    QLineEdit *centerFreq_edit_2;
    QLineEdit *deltaFreq_edit_2;
    QLineEdit *stepFreq_edit_2;
    QComboBox *tag_select_2;

    QGroupBox *antenna_3;
    QGroupBox *centerFreq_3;
    QGroupBox *deltaFreq_3;
    QGroupBox *stepFreq_3;
    QLineEdit *centerFreq_edit_3;
    QLineEdit *deltaFreq_edit_3;
    QLineEdit *stepFreq_edit_3;
    QComboBox *tag_select_3;

    uint64_t tag_frequency[18];
    uint64_t band_frequency[18];
    uint64_t sweep_step_frequency[18];

    uint16_t tag_number;

    QPushButton *addParamFreq_tag;
    QPushButton *sendparamFreq_total;

    QPushButton *Parcel_test;

    QTabWidget          *Peak_Tabs;
    QWidget             *derivative_graph;
    QWidget             *peak_graph;
    QwtPlot             *derivative_plot;
    QwtPlot             *peak_plot;
    QwtPlotCurve        *derivative_curve;
    QwtPlotCurve        *peak_curve;
    QPolygonF           derivative_points;
    QPolygonF           peak_points;
    uint64_t            temperature_points;
    QGroupBox           *a_coef_groupbox;
    QGroupBox           *b_coef_groupbox;
    QGroupBox           *c_coef_groupbox;
    QLineEdit           *a_coefficient;
    QLineEdit           *b_coefficient;
    QLineEdit           *c_coefficient;
    double              a;
    double              b;
    double              c;

    double              temperature_interf_threshold;
    uint8_t             temperature_interf_counter;
    double              temperature_interf_mass[3];
    double              temperature_interf_derivative;
    uint8_t             temperature_interf_event;

    uint8_t             test_mass_coounter;

    QLabel              *service_message;
    QCheckBox           *auto_mode;
    QPushButton         *get_data;
    uint8_t             auto_mode_test;
    uint16_t            message_counter;


private:
    Ui::MainWindow *ui;

    typedef union{
        uint16_t 	istd;
        uint8_t 	cstd[2];
    }std_union;

    typedef union{
        uint32_t 	listd;
        uint16_t 	istd[2];
        uint8_t 	cstd[4];
    }long_std_union;

    typedef union{
        uint64_t 	llistd;
        uint32_t 	listd[2];
        uint16_t 	istd[4];
        uint8_t 	cstd[8];
    }long_long_std_union;

    typedef struct
    {
        double      *module;
        double      *real;
        double      *image;
    }DFT_result;

    typedef struct
    {
        uint16_t    RAW_SIZE;
        double      RAW_MASSIVE[RAW_AMMOUNT][1000];
    }RAW_DATA;

    char            CRC = 0;

    uint8_t         com_mode;
    uint8_t         uart_command;
    uint8_t         antenna_selected;
    uint8_t         path_selected;
    uint8_t         data_check_box;
    uint8_t         timer_2_mode;
    uint8_t         UART_RECEIVE_BUFFER[10000];

    uint16_t        adc_call_command_counter;
    uint16_t        adc_global_counter;
    uint16_t        attenuation_selected;
    uint16_t        X_DATA_BUFFER[1000];

    uint64_t        time;
    QTimer          *timer_1;
    QElapsedTimer   *timer_2;
    QTimer          *timer_3;
    QPixmap         *echo_pix;
    QByteArray      ba;

    std_union       len;

    double          ADC_DATA_BUFFER[1000];
    double          zero[1000];

    DFT_result      Fourier;
    DFT_result      Fourier_1;
    DFT_result      Fourier_2;

    RAW_DATA        READER_DATA;

    QLabel          *current_temperature;
    QString         *cur_temp;
private slots:
    void readData(void);
    void getEcho(void);
    void getADC(void);
    void setSwtich(void);
    void setAttenuation(void);
    void connectCOM(void);
    void selectPath(void);
    void selectAnt(void);
    void selectAtt(void);
    void writeAtt(void);
    void setup_the_plot(void);
    void clear_graph(void);
    void paint_curve(uint16_t counter);
    uint16_t median_filter(uint16_t datum);
    uint16_t lowpass_filter(uint16_t datum);
    double lowpass_filter_double_1(double datum);
    double lowpass_filter_double_2(double datum);
    uint16_t average_filter(uint16_t datum);
    void through_filters_test(void);
    void generation_maintain(void);
    void send_accept(void);
    void not_received(void);
    void sigma_filter(void);
    DFT_result discrete_FourierTransform(double *massive_re, double *massive_im, char dir, uint16_t N);
    void FFT(short int dir,long m,double *x,double *y);
    void ad5932_send_data(void);
    void adf4360_send_data(void);
    void crystal_send_data(void);
    void send_freq_param(void);
    void send_freq_param_total(void);
    void add_freq_tag(void);
    void test_mode_toggle(void);
    void signal_type_toggle(void);
    uint16_t peak_search(DFT_result *data, uint16_t len);
    uint16_t peak_search_1(DFT_result *data, uint16_t len);
    void get_ready_test_parcel(void);
    double calc_temperature(uint16_t index);
    void get_a_coef(void);
    void get_b_coef(void);
    void get_c_coef(void);
    void change_adc_mode(void);

signals:
    void data_received(void);
};

#endif // MAINWINDOW_H
