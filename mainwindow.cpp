#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    data_check_box = ON;
    TabS = new QTabWidget;
    File = new QFile("log.txt");
    File->open(QIODevice::ReadWrite);
    fileStream.setDevice(File);
    out_message = new QLabel;
    in_message = new QLineEdit;
    in_message->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    out_message->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    //in_message->setFixedHeight(
    first_tab = new QWidget;
    second_tab = new QWidget;
    third_tab = new QWidget;
    fourth_tab = new QWidget;
    fifth_tab = new QWidget;
    Timer_Data = new QTime;
    timer_1 = new QTimer;
    timer_1->setInterval(200);
    timer_3 = new QTimer;
    timer_3->setInterval(1500);
    echo_pix = new QPixmap("reddot.png");
    plot = new QwtPlot(this);
    curve = new QwtPlotCurve();
    curve_DFT = new QwtPlotCurve();
    spectre_graph = new QwtPlot(this);
    spectre_spurs = new QwtPlotCurve();
    Parcel_test = new QPushButton("Test Parcel");
    Peak_Tabs = new QTabWidget();
    derivative_graph = new QWidget();
    peak_graph = new QWidget();
    derivative_plot =  new QwtPlot();
    peak_plot =  new QwtPlot();
    derivative_curve = new QwtPlotCurve();
    peak_curve = new QwtPlotCurve();
    a_coef_groupbox = new QGroupBox("Коэффициент a");
    b_coef_groupbox = new QGroupBox("Коэффициент b");
    c_coef_groupbox = new QGroupBox("Коэффициент c");
    a_coefficient = new QLineEdit();
    b_coefficient = new QLineEdit();
    c_coefficient = new QLineEdit();
    cur_temp = new QString;
    a = 0;
    b = 0;
    c = 0;
    temperature_points = 0;
    com_mode = 0;
    attenuation_selected = 0;
    antenna_selected = 1;
    path_selected = 1;
    timer_2_mode = 0;
    adc_call_command_counter = 0;
    ui->comstate_label->setText("<FONT COLOR=red>Closed</FONT>");
    //ui->data_lcdnumber->setHexMode();
    //ui->data_lcdnumber->setSegmentStyle(QLCDNumber::Flat);
    adc_call_command_counter = 0;
    adc_global_counter = 0;
    CRC = 0;
    ba.clear();
    for(int i = 0; i < 1000; i++)
    {
        zero[i] = 0;
    }
    READER_DATA.RAW_SIZE = 0;
    file_log_number = 0;

    temperature_interf_counter = 0;
    temperature_interf_threshold = 10;
    temperature_interf_derivative = 0;
    temperature_interf_event = 0;
    memset(temperature_interf_mass, 0, 3);

    test_mass_coounter = 0;

    signal_type_mode = 0;

    auto_mode_test = SINGLE_MODE;

    message_counter = 0;
    /************************************** Third Tab Widgets *************************************/
    /*    QGroupBox *crystal_group;
    QCheckBox *crystal_status;
    QPushButton *crystal_send;
    QGroupBox *ad5932_group;
    QCheckBox *msb_status;
    QCheckBox *signal_type_status;
    QCheckBox *ctrl_type_status;
    QLabel *freq_start;
    QLabel *freq_delta;
    QLabel *n_increment;
    QLabel *time_interval;
    QPushButton *ad5932_send;
    QGroupBox *adf4360_group;
    QLabel *a_counter;
    QLabel *b_counter;
    QLabel *r_counter;
    QComboBox *power_level;
    QComboBox *p_prescaler;*/

    crystal_group = new QGroupBox("Опорный генератор");
    crystal_status = new QCheckBox("Вкл./Выкл.");
    crystal_send = new QPushButton("Отправить");
    QVBoxLayout *crystal_VLayout = new QVBoxLayout;
    crystal_VLayout->addWidget(crystal_status);
    crystal_VLayout->addWidget(crystal_send);
    crystal_group->setLayout(crystal_VLayout);

    ad5932_group = new QGroupBox("AD5932");
    msb_status = new QCheckBox("MSB");
    signal_type_status = new QCheckBox("Синус/Треугольник");
    ctrl_type_status = new QCheckBox("Внешнее/Таймер");
    freq_start_label = new QLabel("Стартовая частота");
    freq_delta_label = new QLabel("Частотный шаг");
    n_increment_label = new QLabel("Количество шагов");
    time_interval_label = new QLabel("Временной интервал");
    freq_start = new QLineEdit();
    freq_delta = new QLineEdit();
    n_increment = new QLineEdit();
    time_interval = new QLineEdit();
    ad5932_send = new QPushButton("Отправить");
    QVBoxLayout *ad5932_VLayout = new QVBoxLayout;
    ad5932_VLayout->addWidget(msb_status);
    ad5932_VLayout->addWidget(signal_type_status);
    ad5932_VLayout->addWidget(ctrl_type_status);
    QHBoxLayout *freq_start_HLayout = new QHBoxLayout;
    freq_start_HLayout->addWidget(freq_start);
    freq_start_HLayout->addWidget(freq_start_label);
    ad5932_VLayout->addLayout(freq_start_HLayout);
    QHBoxLayout *freq_delta_HLayout = new QHBoxLayout;
    freq_delta_HLayout->addWidget(freq_delta);
    freq_delta_HLayout->addWidget(freq_delta_label);
    ad5932_VLayout->addLayout(freq_delta_HLayout);
    QHBoxLayout *n_increment_HLayout = new QHBoxLayout;
    n_increment_HLayout->addWidget(n_increment);
    n_increment_HLayout->addWidget(n_increment_label);
    ad5932_VLayout->addLayout(n_increment_HLayout);
    QHBoxLayout *time_interval_HLayout = new QHBoxLayout;
    time_interval_HLayout->addWidget(time_interval);
    time_interval_HLayout->addWidget(time_interval_label);
    ad5932_VLayout->addLayout(time_interval_HLayout);
    ad5932_VLayout->addWidget(ad5932_send);
    ad5932_group->setLayout(ad5932_VLayout);

    adf4360_group = new QGroupBox("ADF4360-0");
    a_counter = new QLineEdit();
    b_counter = new QLineEdit();
    r_counter = new QLineEdit();
    a_counter_label = new QLabel("А счётчик");
    b_counter_label = new QLabel("В счётчик");
    r_counter_label = new QLabel("R счётчик");
    power_level_label = new QLabel("Уровень сигнала");
    p_prescaler_label = new QLabel("P предделитель");
    power_level = new QComboBox();
    power_level->addItem("-13дБм");
    power_level->addItem("-11дБм");
    power_level->addItem("-8дБм");
    power_level->addItem("-6дБм");
    p_prescaler = new QComboBox();
    p_prescaler->addItem("8/9");
    p_prescaler->addItem("16/17");
    p_prescaler->addItem("32/33");
    adf4360_send = new QPushButton("Отправить");
    QVBoxLayout *adf4360_VLayout = new QVBoxLayout;
    QHBoxLayout *a_counter_HLayout = new QHBoxLayout;
    a_counter_HLayout->addWidget(a_counter);
    a_counter_HLayout->addWidget(a_counter_label);
    QHBoxLayout *b_counter_HLayout = new QHBoxLayout;
    b_counter_HLayout->addWidget(b_counter);
    b_counter_HLayout->addWidget(b_counter_label);
    QHBoxLayout *r_counter_HLayout = new QHBoxLayout;
    r_counter_HLayout->addWidget(r_counter);
    r_counter_HLayout->addWidget(r_counter_label);
    QHBoxLayout *adf_comboboxes = new QHBoxLayout;
    QHBoxLayout *power_level_HLayout = new QHBoxLayout;
    power_level_HLayout->addWidget(power_level);
    power_level_HLayout->addWidget(power_level_label);
    QHBoxLayout *p_prescaler_HLayout = new QHBoxLayout;
    p_prescaler_HLayout->addWidget(p_prescaler);
    p_prescaler_HLayout->addWidget(p_prescaler_label);
    adf_comboboxes->addLayout(power_level_HLayout);
    adf_comboboxes->addLayout(p_prescaler_HLayout);
    adf4360_VLayout->addLayout(adf_comboboxes);
    adf4360_VLayout->addLayout(a_counter_HLayout);
    adf4360_VLayout->addLayout(b_counter_HLayout);
    adf4360_VLayout->addLayout(r_counter_HLayout);
    adf4360_VLayout->addWidget(adf4360_send);
    adf4360_group->setLayout(adf4360_VLayout);

    centerFreq = new QGroupBox("Центральная частота");
    deltaFreq = new QGroupBox("Полоса");
    stepFreq = new QGroupBox("Шаг");
    centerFreq_edit = new QLineEdit();
    deltaFreq_edit = new QLineEdit();
    stepFreq_edit = new QLineEdit();
    sendparamFreq = new QPushButton("Отправить параметры");
    QVBoxLayout *centerFreq_layout = new QVBoxLayout;
    centerFreq_layout->addWidget(centerFreq_edit);
    QVBoxLayout *deltaFreq_layout = new QVBoxLayout;
    deltaFreq_layout->addWidget(deltaFreq_edit);
    QVBoxLayout *stepFreq_layout = new QVBoxLayout;
    stepFreq_layout->addWidget(stepFreq_edit);
    centerFreq->setLayout(centerFreq_layout);
    deltaFreq->setLayout(deltaFreq_layout);
    stepFreq->setLayout(stepFreq_layout);


    QHBoxLayout *frequency_parameters = new QHBoxLayout;
    frequency_parameters->addWidget(centerFreq);
    frequency_parameters->addWidget(deltaFreq);
    frequency_parameters->addWidget(stepFreq);
    QVBoxLayout *vertical_1 = new QVBoxLayout;
    vertical_1->addWidget(plot);
    vertical_1->addWidget(ui->clearGraph_button);
    vertical_1->addLayout(frequency_parameters);
    vertical_1->addWidget(sendparamFreq);
    ui->Graphs->setLayout(vertical_1);
    QVBoxLayout *vertical_2 = new QVBoxLayout;
    test_radio_button = new QCheckBox("Выключить/включить тестовый режим");
    signal_type = new QCheckBox("Тип Сигнала");
    service_message = new QLabel;
    current_temperature = new QLabel;
    auto_mode = new QCheckBox("Auto request");
    get_data = new QPushButton("Get Data");
    vertical_2->addWidget(ui->Controls_group);
    QHBoxLayout *buttons_vertical_layout = new QHBoxLayout;
    buttons_vertical_layout->addWidget(get_data);
    buttons_vertical_layout->addWidget(auto_mode);
    vertical_2->addWidget(current_temperature);
    vertical_2->addLayout(buttons_vertical_layout);
    vertical_2->addWidget(service_message);
    vertical_2->addWidget(test_radio_button);
    vertical_2->addWidget(signal_type);
    QHBoxLayout *horizontal_5 = new QHBoxLayout;
    horizontal_5->addLayout(vertical_2);
    horizontal_5->addWidget(ui->Graphs);
    first_tab->setLayout(horizontal_5);

    TabS->addTab(first_tab, "Главная");

    QVBoxLayout *vertical_3 = new QVBoxLayout;
    vertical_3->addWidget(in_message);
    vertical_3->addWidget(out_message);
    vertical_3->addWidget(Parcel_test);

    QVBoxLayout *vertical_4 = new QVBoxLayout;
    vertical_4->addWidget(spectre_graph);

    QHBoxLayout *horizontal_1 = new QHBoxLayout;
    horizontal_1->addLayout(vertical_3);
    horizontal_1->addLayout(vertical_4);
    second_tab->setLayout(horizontal_1);

    TabS->addTab(second_tab, "Проверка Фильтров");

    QVBoxLayout *vertical_5 = new QVBoxLayout;
    vertical_5->addWidget(ad5932_group);

    QVBoxLayout *vertical_6 = new QVBoxLayout;
    vertical_6->addWidget(adf4360_group);

    QVBoxLayout *vertical_7 = new QVBoxLayout;
    vertical_7->addWidget(crystal_group);

    QHBoxLayout *horizontal_2 = new QHBoxLayout;
    horizontal_2->addLayout(vertical_5);
    horizontal_2->addLayout(vertical_6);
    horizontal_2->addLayout(vertical_7);
    third_tab->setLayout(horizontal_2);

    TabS->addTab(third_tab, "Режим тестирования");

    QStringList tags_list = {"tag_1", "tag_2", "tag_3", "tag_4", "tag_5", "tag_6"};

    antenna_1 = new QGroupBox("Антенна 1");
    centerFreq_1 = new QGroupBox("Центральная частота");
    deltaFreq_1 = new QGroupBox("Полоса");
    stepFreq_1 = new QGroupBox("Шаг");
    centerFreq_edit_1 = new QLineEdit();
    deltaFreq_edit_1 = new QLineEdit();
    stepFreq_edit_1 = new QLineEdit();
    tag_select_1 = new QComboBox();
    tag_select_1->addItems(tags_list);

    antenna_2 = new QGroupBox("Антенна 2");
    centerFreq_2 = new QGroupBox("Центральная частота");
    deltaFreq_2 = new QGroupBox("Полоса");
    stepFreq_2 = new QGroupBox("Шаг");
    centerFreq_edit_2 = new QLineEdit();
    deltaFreq_edit_2 = new QLineEdit();
    stepFreq_edit_2 = new QLineEdit();
    tag_select_2 = new QComboBox();
    tag_select_2->addItems(tags_list);

    antenna_3 = new QGroupBox("Антенна 3");
    centerFreq_3 = new QGroupBox("Центральная частота");
    deltaFreq_3 = new QGroupBox("Полоса");
    stepFreq_3 = new QGroupBox("Шаг");
    centerFreq_edit_3 = new QLineEdit();
    deltaFreq_edit_3 = new QLineEdit();
    stepFreq_edit_3 = new QLineEdit();
    tag_select_3 = new QComboBox();
    tag_select_3->addItems(tags_list);

    addParamFreq_tag = new QPushButton("Добавить метку");
    sendparamFreq_total = new QPushButton("Отправить параметры");

    QVBoxLayout *centerFreq_layout_1 = new QVBoxLayout;
    centerFreq_layout_1->addWidget(centerFreq_edit_1);
    QVBoxLayout *deltaFreq_layout_1 = new QVBoxLayout;
    deltaFreq_layout_1->addWidget(deltaFreq_edit_1);
    QVBoxLayout *stepFreq_layout_1 = new QVBoxLayout;
    stepFreq_layout_1->addWidget(stepFreq_edit_1);
    centerFreq_1->setLayout(centerFreq_layout_1);
    deltaFreq_1->setLayout(deltaFreq_layout_1);
    stepFreq_1->setLayout(stepFreq_layout_1);

    QHBoxLayout *antenna_1_layout = new QHBoxLayout;
    antenna_1_layout->addWidget(tag_select_1);
    antenna_1_layout->addWidget(centerFreq_1);
    antenna_1_layout->addWidget(deltaFreq_1);
    antenna_1_layout->addWidget(stepFreq_1);
    antenna_1->setLayout(antenna_1_layout);

    QVBoxLayout *centerFreq_layout_2 = new QVBoxLayout;
    centerFreq_layout_2->addWidget(centerFreq_edit_2);
    QVBoxLayout *deltaFreq_layout_2 = new QVBoxLayout;
    deltaFreq_layout_2->addWidget(deltaFreq_edit_2);
    QVBoxLayout *stepFreq_layout_2 = new QVBoxLayout;
    stepFreq_layout_2->addWidget(stepFreq_edit_2);
    centerFreq_2->setLayout(centerFreq_layout_2);
    deltaFreq_2->setLayout(deltaFreq_layout_2);
    stepFreq_2->setLayout(stepFreq_layout_2);

    QHBoxLayout *antenna_2_layout = new QHBoxLayout;
    antenna_2_layout->addWidget(tag_select_2);
    antenna_2_layout->addWidget(centerFreq_2);
    antenna_2_layout->addWidget(deltaFreq_2);
    antenna_2_layout->addWidget(stepFreq_2);
    antenna_2->setLayout(antenna_2_layout);

    QVBoxLayout *centerFreq_layout_3 = new QVBoxLayout;
    centerFreq_layout_3->addWidget(centerFreq_edit_3);
    QVBoxLayout *deltaFreq_layout_3 = new QVBoxLayout;
    deltaFreq_layout_3->addWidget(deltaFreq_edit_3);
    QVBoxLayout *stepFreq_layout_3 = new QVBoxLayout;
    stepFreq_layout_3->addWidget(stepFreq_edit_3);
    centerFreq_3->setLayout(centerFreq_layout_3);
    deltaFreq_3->setLayout(deltaFreq_layout_3);
    stepFreq_3->setLayout(stepFreq_layout_3);

    QHBoxLayout *antenna_3_layout = new QHBoxLayout;
    antenna_3_layout->addWidget(tag_select_3);
    antenna_3_layout->addWidget(centerFreq_3);
    antenna_3_layout->addWidget(deltaFreq_3);
    antenna_3_layout->addWidget(stepFreq_3);
    antenna_3->setLayout(antenna_3_layout);

    QVBoxLayout *fourth_tab_layout = new QVBoxLayout;
    fourth_tab_layout->addWidget(antenna_1);
    fourth_tab_layout->addWidget(antenna_2);
    fourth_tab_layout->addWidget(antenna_3);
    fourth_tab_layout->addWidget(addParamFreq_tag);
    fourth_tab_layout->addWidget(sendparamFreq_total);
    fourth_tab->setLayout(fourth_tab_layout);

    TabS->addTab(fourth_tab, "Настройка меток");

    QVBoxLayout *main_graphs_layout = new QVBoxLayout;
    Peak_Tabs->addTab(derivative_graph, "График производной");
    Peak_Tabs->addTab(peak_graph, "График температуры");
    QVBoxLayout *deriv_tab_layout = new QVBoxLayout;
    deriv_tab_layout->addWidget(derivative_plot);
    derivative_graph->setLayout(deriv_tab_layout);
    QHBoxLayout *peak_tab_layout = new QHBoxLayout();
    QVBoxLayout *peak_coef_layout = new QVBoxLayout;
    peak_coef_layout->setSizeConstraint(QLayout::SetMinimumSize);
    a_coefficient->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    b_coefficient->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    c_coefficient->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    QVBoxLayout *peak_coef_layout_a = new QVBoxLayout;
    peak_coef_layout_a->addWidget(a_coefficient);
    peak_coef_layout_a->setSizeConstraint(QLayout::SetMinimumSize);
    QVBoxLayout *peak_coef_layout_b = new QVBoxLayout;
    peak_coef_layout_b->addWidget(b_coefficient);
    peak_coef_layout_b->setSizeConstraint(QLayout::SetMinimumSize);
    QVBoxLayout *peak_coef_layout_c = new QVBoxLayout;
    peak_coef_layout_c->addWidget(c_coefficient);
    peak_coef_layout_c->setSizeConstraint(QLayout::SetMinimumSize);
    a_coef_groupbox->setLayout(peak_coef_layout_a);
    b_coef_groupbox->setLayout(peak_coef_layout_b);
    c_coef_groupbox->setLayout(peak_coef_layout_c);
    peak_coef_layout->addWidget(a_coef_groupbox);
    peak_coef_layout->addWidget(b_coef_groupbox);
    peak_coef_layout->addWidget(c_coef_groupbox);
    peak_tab_layout->addLayout(peak_coef_layout);

    peak_tab_layout->addWidget(peak_plot);
    peak_graph->setLayout(peak_tab_layout);
    main_graphs_layout->addWidget(Peak_Tabs);
    fifth_tab->setLayout(main_graphs_layout);

    TabS->addTab(fifth_tab, "Графики пика и температуры");


    QHBoxLayout *main = new QHBoxLayout;
    main->addWidget(TabS);
    ui->centralWidget->setLayout(main);


    COM = new QSerialPort(this);
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
            ui->com_combobox->addItem(info.portName());

    echo_pix->scaled(ui->echo_label->size());
    ui->echo_label->setPixmap(*echo_pix);
    ui->echo_label->setScaledContents(true);

    setup_the_plot();

    /********************* Проверка выгрузки в файл ********************/
    /*double test_mass[6] = {123.12, 34.201, 0, 3, 2, 22.1111};

    QString test_string;
    QByteArray test_byte_array;
    //qDebug() << (*test_mass);
    //fileStream << "Start";
    //fileStream << QString::number((double)*test_mass, 'f', 3);
    for(int i = 0; i < 6; i++)
    {
        qDebug() << test_mass[i];
        test_string.append(QString::number(test_mass[i], 'f', 3));
        qDebug() << test_string;
        test_string.append("\n");
    }
    test_byte_array.append(test_string);
    qDebug() << test_string;
    qDebug() << test_byte_array;
    File->write("Start");
    File->write("\n");
    File->write(test_byte_array);
    File->close();
    File->close();
    File->setFileName("log_" + QString::number(file_log_number)+".txt");
    File->open(QIODevice::ReadWrite);
    file_log_number++;
    File->close();
    File->setFileName("log_" + QString::number(file_log_number)+".txt");
    File->open(QIODevice::ReadWrite);*/

    connect(test_radio_button, SIGNAL(clicked(bool)), this, SLOT(test_mode_toggle()));
    connect(auto_mode, SIGNAL(clicked(bool)), this, SLOT(change_adc_mode()));
    connect(signal_type, SIGNAL(clicked(bool)), this, SLOT(signal_type_toggle()));
    connect(ui->com_button, SIGNAL(clicked(bool)), this, SLOT(connectCOM()));
    //connect(ui->echo_button, SIGNAL(clicked(bool)), this, SLOT(getEcho()));
    connect(get_data, SIGNAL(clicked(bool)), this, SLOT(getADC()));
    /*connect(ui->switch_button, SIGNAL(clicked(bool)), this, SLOT(setSwtich()));
    connect(ui->att_button, SIGNAL(clicked(bool)), this, SLOT(setAttenuation()));
    connect(ui->path_dial, SIGNAL(sliderReleased()), this, SLOT(selectPath()));
    connect(ui->antenna_dial, SIGNAL(sliderReleased()), this, SLOT(selectAnt()));
    connect(ui->att_slider, SIGNAL(valueChanged(int)), this, SLOT(selectAtt()));
    connect(ui->att_lineedit, SIGNAL(editingFinished()), this, SLOT(writeAtt()));
    connect(ui->setgenButton, SIGNAL(clicked(bool)), this, SLOT(generation_maintain()));*/
    connect(in_message, SIGNAL(returnPressed()), this, SLOT(through_filters_test()));
    connect(ui->clearGraph_button, SIGNAL(clicked(bool)), this, SLOT(clear_graph()));
    connect(timer_1, SIGNAL(timeout()), this, SLOT(send_accept()));
    connect(timer_3, SIGNAL(timeout()), this, SLOT(not_received()));
    //connect(this, SIGNAL(data_received()), this, SLOT(getADC()));
    connect(COM, SIGNAL(readyRead()), this, SLOT(readData()));
    connect(ad5932_send, SIGNAL(clicked(bool)), this, SLOT(ad5932_send_data()));
    connect(adf4360_send, SIGNAL(clicked(bool)), this, SLOT(adf4360_send_data()));
    connect(crystal_send, SIGNAL(clicked(bool)), this, SLOT(crystal_send_data()));
    connect(sendparamFreq, SIGNAL(clicked(bool)), this, SLOT(send_freq_param()));
    connect(addParamFreq_tag, SIGNAL(clicked(bool)), this, SLOT(add_freq_tag()));
    connect(sendparamFreq_total, SIGNAL(clicked(bool)), this, SLOT(send_freq_param_total()));
    connect(Parcel_test, SIGNAL(clicked(bool)), this, SLOT(get_ready_test_parcel()));
    connect(a_coefficient, SIGNAL(returnPressed()), this, SLOT(get_a_coef()));
    connect(b_coefficient, SIGNAL(returnPressed()), this, SLOT(get_b_coef()));
    connect(c_coefficient, SIGNAL(returnPressed()), this, SLOT(get_c_coef()));
}

/*************************************** DATA TRANSFER FUNCTIONS **********************************************/

void MainWindow::readData(void)
{
    char temp = 0;
    std_union temp_1;
    temp_1.istd = 0;
    uint16_t len_effective = 0;
    long_std_union data_temp;
    data_temp.listd = 0;
    //uint16_t window = 360;
    qDebug() << "ReadyRead_Got";
    ba.append(COM->readAll());
    qDebug() << ba.size();
    /*if(ba.size() < 806)
    {
        ba.push_back(COM->readAll());
    }*/

    int idx = ba.indexOf(SYNCHRO, 0);
    if(idx >= 0)
    {
        qDebug() << "Synchro byte found";
        if(idx > 0)
        {
            ba.remove(0,idx);
            idx = 0;
        }
        if(ba.size() > 2)
        {
            qDebug() << "Potential parcel";
            len.cstd[1] = ba[1];
            len.cstd[0] = ba[2];
            qDebug() << len.istd;
            if(len.istd > 3000)
            {
                ba.clear();
                /*COM->close();

                COM->open(QSerialPort::ReadWrite);*/
            }
            if(ba.size() >= len.istd)
            {
                qDebug() << "Potential parcel len achieved";
                temp = ba[3];
                if(temp == UART_ADDR)
                {
                    qDebug() << "Address achieved";
                    for(int i = 0; i < len.istd; i++)
                    {
                        CRC ^= ba[i];
                    }
                    if(CRC == 0)
                    {
                        qDebug() << "XOR approved";
                        temp = ba[4];
                        switch (temp)
                        {
                        case ECHO:
                            echo_pix->load("greendot.jpg");
                            echo_pix->scaled(ui->echo_label->size());
                            ui->echo_label->setPixmap(*echo_pix);
                            ui->echo_label->setScaledContents(true);
                            get_data->setEnabled(TRUE);
                            uart_command = 0;
                            break;
                        case ADC_CONT_1SEC:
                            if(data_check_box == OFF)
                            {
                                len_effective = (len.istd - SERVICE_BITS_LEN)/2;
                                //qDebug() << "reading...";
                                for (int i = 0; i < len_effective; i++)
                                {
                                    data_temp.cstd[1] = ba[i*2 + 5];
                                    data_temp.cstd[0] = ba[i*2 + 6];
                                    ADC_DATA_BUFFER[i] = (((data_temp.istd[0])));//average_filter median_filter lowpass_filter
                                    adc_call_command_counter++;
                                }

                                Fourier.module = new double[adc_call_command_counter];
                                Fourier.real = new double[adc_call_command_counter];
                                Fourier.image = new double[adc_call_command_counter];
                                Fourier_1.module = new double[adc_call_command_counter];
                                Fourier_1.real = new double[adc_call_command_counter];
                                Fourier_1.image = new double[adc_call_command_counter];
                                Fourier = discrete_FourierTransform(ADC_DATA_BUFFER, zero, 1, adc_call_command_counter);
                                /*Fourier.real[0] = 0;
                                Fourier.image[0] = 0;
                                Fourier.module[0] = 0;
                                Fourier.real[adc_call_command_counter] = 0;
                                Fourier.image[adc_call_command_counter] = 0;
                                Fourier.module[adc_call_command_counter] = 0;*/
                                /*for(uint16_t i = 0; i < adc_call_command_counter/2; i++)
                                {
                                    Fourier.real[i] = 0;
                                    Fourier.image[i] = 0;
                                    Fourier.module[i] = 0;
                                }
                                for(uint16_t i = 3*adc_call_command_counter/2; i < 2*adc_call_command_counter; i++)
                                {
                                    Fourier.real[i] = 0;
                                    Fourier.image[i] = 0;
                                    Fourier.module[i] = 0;
                                }*/



                                Fourier_1 = discrete_FourierTransform(Fourier.real, Fourier.image, -1, adc_call_command_counter);
                                for (int i = 0; i < adc_call_command_counter; i++)
                                {
                                    //qDebug() << test_mass[i];
                                    file_string.append(QString::number(Fourier_1.module[i], 'f', 6));
                                    //qDebug() << file_string;
                                    file_string.append("\n");

                                }

                                file_byte_array.append(file_string);
                                File->write("Start");
                                File->write("\n");
                                File->write(file_byte_array);
                                if(File->size() >= 0x400000)
                                {
                                    File->close();
                                    File->setFileName("log_" + QString::number(file_log_number)+".txt");
                                    File->open(QIODevice::ReadWrite);
                                    file_log_number++;
                                }
                                //File->close();

                                clear_graph();
                                paint_curve(adc_call_command_counter);

                                if(signal_type_mode)
                                {
                                    if(temperature_interf_counter == 0)
                                    {
                                        temperature_interf_mass[temperature_interf_counter] = calc_temperature(peak_search(&Fourier_1, adc_call_command_counter));
                                        current_temperature->setText(QString::number(temperature_interf_mass[temperature_interf_counter]));
                                        temperature_interf_counter++;
                                    }
                                    else if(temperature_interf_counter == 1)
                                    {
                                        temperature_interf_mass[temperature_interf_counter] = calc_temperature(peak_search(&Fourier_1, adc_call_command_counter));
                                        temperature_interf_derivative = temperature_interf_mass[temperature_interf_counter - 1] - temperature_interf_mass[temperature_interf_counter];
                                        current_temperature->setText(QString::number(temperature_interf_mass[temperature_interf_counter]));
                                        if(qFabs(temperature_interf_derivative) >= temperature_interf_threshold)
                                        {
                                            temperature_interf_event = 1;
                                            temperature_interf_counter++;
                                        }
                                        else
                                        {
                                            peak_points << QPointF(temperature_points, temperature_interf_mass[temperature_interf_counter - 1]);
                                            peak_points << QPointF(temperature_points + 1, temperature_interf_mass[temperature_interf_counter]);
                                            temperature_interf_mass[temperature_interf_counter - 1] = temperature_interf_mass[temperature_interf_counter];
                                            temperature_points += 2;
                                        }

                                    }
                                    else if(temperature_interf_counter == 2)
                                    {
                                        if(temperature_interf_event == 1)
                                        {
                                            temperature_interf_mass[temperature_interf_counter] = calc_temperature(peak_search(&Fourier_1, adc_call_command_counter));
                                            temperature_interf_derivative = temperature_interf_mass[temperature_interf_counter - 1] - temperature_interf_mass[temperature_interf_counter];
                                            current_temperature->setText(QString::number(temperature_interf_mass[temperature_interf_counter]));
                                            if(qFabs(temperature_interf_derivative) >= temperature_interf_threshold)
                                            {
                                                temperature_interf_event = 2;
                                                temperature_interf_mass[temperature_interf_counter - 1] = ((temperature_interf_mass[temperature_interf_counter] + temperature_interf_mass[temperature_interf_counter - 2]) / 2);
                                            }
                                            peak_points << QPointF(temperature_points, temperature_interf_mass[temperature_interf_counter - 2]);
                                            peak_points << QPointF(temperature_points + 1, temperature_interf_mass[temperature_interf_counter - 1]);
                                            peak_points << QPointF(temperature_points + 2, temperature_interf_mass[temperature_interf_counter]);
                                            temperature_interf_mass[temperature_interf_counter - 2] = temperature_interf_mass[temperature_interf_counter];
                                            temperature_interf_counter = 1;
                                            temperature_points += 3;
                                        }
                                    }
                                }
                                else
                                {
                                    if(temperature_interf_counter == 0)
                                    {
                                        temperature_interf_mass[temperature_interf_counter] = calc_temperature(peak_search_1(&Fourier_1, adc_call_command_counter));
                                        temperature_interf_counter++;
                                    }
                                    else if(temperature_interf_counter == 1)
                                    {
                                        temperature_interf_mass[temperature_interf_counter] = calc_temperature(peak_search_1(&Fourier_1, adc_call_command_counter));
                                        temperature_interf_derivative = temperature_interf_mass[temperature_interf_counter - 1] - temperature_interf_mass[temperature_interf_counter];
                                        if(qFabs(temperature_interf_derivative) >= temperature_interf_threshold)
                                        {
                                            temperature_interf_event = 1;
                                            temperature_interf_counter++;
                                        }
                                        else
                                        {
                                            peak_points << QPointF(temperature_points, temperature_interf_mass[temperature_interf_counter - 1]);
                                            peak_points << QPointF(temperature_points + 1, temperature_interf_mass[temperature_interf_counter]);
                                            temperature_interf_mass[temperature_interf_counter - 1] = temperature_interf_mass[temperature_interf_counter];
                                            temperature_points += 2;
                                        }

                                    }
                                    else if(temperature_interf_counter == 2)
                                    {
                                        if(temperature_interf_event == 1)
                                        {
                                            temperature_interf_mass[temperature_interf_counter] = calc_temperature(peak_search_1(&Fourier_1, adc_call_command_counter));
                                            temperature_interf_derivative = temperature_interf_mass[temperature_interf_counter - 1] - temperature_interf_mass[temperature_interf_counter];
                                            if(qFabs(temperature_interf_derivative) >= temperature_interf_threshold)
                                            {
                                                temperature_interf_event = 2;
                                                temperature_interf_mass[temperature_interf_counter - 1] = ((temperature_interf_mass[temperature_interf_counter] + temperature_interf_mass[temperature_interf_counter - 2]) / 2);
                                            }
                                            peak_points << QPointF(temperature_points, temperature_interf_mass[temperature_interf_counter - 2]);
                                            peak_points << QPointF(temperature_points + 1, temperature_interf_mass[temperature_interf_counter - 1]);
                                            peak_points << QPointF(temperature_points + 2, temperature_interf_mass[temperature_interf_counter]);
                                            temperature_interf_mass[temperature_interf_counter - 2] = temperature_interf_mass[temperature_interf_counter];
                                            temperature_interf_counter = 1;
                                            temperature_points += 3;
                                        }
                                    }
                                }



                                //peak_points << QPointF(temperature_points, calc_temperature(peak_search(&Fourier_1, adc_call_command_counter)));
                                //temperature_points++;
                                peak_curve->setSamples(peak_points);
                                peak_plot->replot();


                                //ui->data_lcdnumber->display(QString::number(adc_call_command_counter));

                                free(Fourier.module);
                                free(Fourier.real);
                                free(Fourier.image);
                                free(Fourier_1.module);
                                free(Fourier_1.real);
                                free(Fourier_1.image);
                                READER_DATA.RAW_SIZE = 0;
                                adc_call_command_counter = 0;

                                ba.remove(0, temp_1.istd);
                                service_message->setText("Data" + QString::number(message_counter) + "achieved");
                                message_counter++;
                                if(auto_mode_test == SINGLE_MODE)
                                {
                                  data_check_box = ON;
                                }
                                else if(auto_mode_test == AUTO_MODE)
                                {
                                  timer_1->start();
                                }

                                /*if(auto_mode_test == SINGLE_MODE)
                                {
                                    get_data->setEnabled(TRUE);
                                    //data_check_box = ON;
                                }
                                else if(auto_mode_test == AUTO_MODE)
                                {
                                    timer_1->start();
                                    //data_check_box = OFF;
                                }*/

                            }
                            break;
                        case GENERATION_CTRL:
                            echo_pix->load("greendot.jpg");
                            echo_pix->scaled(ui->echo_label->size());
                            ui->echo_label->setPixmap(*echo_pix);
                            ui->echo_label->setScaledContents(true);
                            uart_command = 2;
                            break;
                        case OUTPUT_SWITCH:
                            echo_pix->load("greendot.jpg");
                            echo_pix->scaled(ui->echo_label->size());
                            ui->echo_label->setPixmap(*echo_pix);
                            ui->echo_label->setScaledContents(true);
                            uart_command = 3;
                            break;
                        case SET_ATT:
                            echo_pix->load("greendot.jpg");
                            echo_pix->scaled(ui->echo_label->size());
                            ui->echo_label->setPixmap(*echo_pix);
                            ui->echo_label->setScaledContents(true);
                            uart_command = 4;
                            break;
                        case AMP_MANAGE:
                            echo_pix->load("greendot.jpg");
                            echo_pix->scaled(ui->echo_label->size());
                            ui->echo_label->setPixmap(*echo_pix);
                            ui->echo_label->setScaledContents(true);
                            uart_command = 5;
                            break;
                        case ADC_ECHO:
                            timer_1->stop();
                            ba.remove(0, temp_1.istd);
                            //COM->clear();
                            break;
                        default:
                            echo_pix->scaled(ui->echo_label->size(),
                                             Qt::KeepAspectRatioByExpanding);
                            ui->echo_label->setPixmap(QPixmap("reddot.png"));
                            ui->echo_label->setScaledContents(true);
                            uart_command = 255;
                            timer_1->start();
                            break;
                        }
                        ba.clear();
                    }
                    else
                    {
                        qDebug() << "XOR error";
                        service_message->setText("XOR error");
                        ba.remove(0, 1);
                    }
                }
                else
                {
                    qDebug() << "Address error";
                    service_message->setText("Wrong address");
                    ba.remove(0, 1);
                }
            }
            else
            {
                qDebug() << "Not enough bytes";
                service_message->setText("Not enough bytes");
            }
        }
        else
        {
            qDebug() << "Error length";
            service_message->setText("Error length");
        }
    }
    else {
        qDebug() << "No Synchro";
        service_message->setText("No Synchro");
        ba.clear();
    }
    if(auto_mode_test == SINGLE_MODE)
    {
      get_data->setEnabled(TRUE);
    }

    CRC = 0;
}

void MainWindow::connectCOM(void)
{
    if(COM->portName() != ui->com_combobox->currentText())
    {
        COM->close();
        COM->setPortName(ui->com_combobox->currentText());
    }

    COM->setBaudRate(QSerialPort::Baud115200, QSerialPort::AllDirections);
    COM->setDataBits(QSerialPort::Data8);
    COM->setParity(QSerialPort::NoParity);
    COM->setStopBits(QSerialPort::OneStop);
    COM->setFlowControl(QSerialPort::NoFlowControl);
    //COM->setReadBufferSize(10);
    if(COM->open(QSerialPort::ReadWrite))
    {
        ui->comstate_label->setText("<FONT COLOR=#008000>Opened</FONT>");
        com_mode = 1;
        //COM->setDataTerminalReady(true);
        //ui->label->setStyleSheet()
    }
    else
    {
        COM->close();
        ui->comstate_label->setText("<FONT COLOR=red>Closed</FONT>");
        com_mode = 0;
    }
}

void MainWindow::getEcho(void)
{
    QByteArray ba_1;
    char len = 0x06;
    char crc = 0;
    char echo = ECHO;
    ba_1.append(SYNCHRO);
    ba_1.append(char(0x00));
    ba_1.append(len);
    ba_1.append(UART_ADDR);
    ba_1.append(echo);
    for(int i = 0; i < ba_1.size(); i++)
    {
        crc ^= ba_1.at(i);
    }
    ba_1.append(crc);
//    qDebug() << ba_1;
    COM->write(ba_1);
    while(!COM->waitForBytesWritten(-1));           //Если слать в закрытый порт будет зависание
}

void MainWindow::getADC(void)
{
    char len = 0x07;
    char crc = 0;
    char dataTransmit[7] = {SYNCHRO, 0x00, len, UART_ADDR, ADC_CONT_1SEC, 0x00, 0x00};
    dataTransmit[5] = data_check_box;
    if(auto_mode_test == SINGLE_MODE)
    {

        get_data->setEnabled(FALSE);
        //time = 0;
        //timer_1->start();
        adc_call_command_counter = 0;
        //adc_global_counter = 0;
        //timer_2_mode = 1;
        data_check_box = OFF;
    }
    else if(auto_mode_test == AUTO_MODE)
    {
        if(data_check_box == ON)
        {
            get_data->setText("Stop");
            //time = 0;
            //timer_1->start();
            adc_call_command_counter = 0;
            //adc_global_counter = 0;
            //timer_2_mode = 1;
            data_check_box = OFF;
        }
        else if (data_check_box == OFF)
        {
            get_data->setText("Get Data");
            adc_call_command_counter = 0;
            timer_1->stop();
            //timer_2_mode = 0;
            data_check_box = ON;

        }
    }

    for(int i = 0; i < len; i++)
    {
        crc ^= dataTransmit[i];
    }
    dataTransmit[6] = crc;
    if(COM->isOpen())
    {
        COM->write(dataTransmit, len);
        while(!COM->waitForBytesWritten(2000));
    }
}

void MainWindow::change_adc_mode(void)
{
    if(auto_mode->isChecked() == TRUE)
    {
        auto_mode_test = TRUE;
    }
    else if(auto_mode->isChecked() == FALSE)
    {
        auto_mode_test = FALSE;
    }
}

void MainWindow::setSwtich(void)
{
    QByteArray ba;
    char len = 0x08;
    char crc = 0;
    char dataTransmit[8] = {SYNCHRO, 0x00, len, UART_ADDR, OUTPUT_SWITCH, 0x00, 0x00, 0x00};
    dataTransmit[5] = antenna_selected;
    dataTransmit[6] = path_selected;
    for(int i = 0; i < len; i++)
    {
        crc ^= dataTransmit[i];
    }
    dataTransmit[7] = crc;
    ba.append(dataTransmit);
    qDebug() << ba;
    COM->write(dataTransmit, len);
    while(!COM->waitForBytesWritten(-1));
}

void MainWindow::setAttenuation(void)
{
    QByteArray ba;
    char len = 0x08;
    char crc = 0;
    std_union att_temp;
    att_temp.istd = attenuation_selected*5;

    ba.append(SYNCHRO);
    ba.append(char(0x00));
    ba.append(len);
    ba.append(UART_ADDR);
    ba.append(SET_ATT);
    ba.append(att_temp.cstd[1]);
    ba.append(att_temp.cstd[0]);
    for(int i = 0; i < ba.size(); i++)
    {
        crc ^= ba.at(i);
    }
    ba.append(crc);
    COM->write(ba);
    while(!COM->waitForBytesWritten(-1));
}

void MainWindow::send_accept(void)
{
    char dataTransmit[7] = {SYNCHRO, 0x00, 0x07, UART_ADDR, ADC_ECHO, 0x01, 0x73};
    timer_1->stop();
    qDebug() << "Timer_slot";
    COM->write(dataTransmit, 7);
    while(!(COM->waitForBytesWritten(2000)));
}

void MainWindow::selectPath(void)
{
    //path_selected = ui->path_dial->value();
}

void MainWindow::selectAnt(void)
{
    //antenna_selected = ui->antenna_dial->value();
}

void MainWindow::selectAtt(void)
{
    /*double temp;
    attenuation_selected = ui->att_slider->value();
    temp = attenuation_selected;
    ui->att_lineedit->setText(QString::number(temp/2));*/
}

void MainWindow::writeAtt(void)
{
    /*QString string(ui->att_lineedit->text());
    double att_double_temp = string.toDouble(0);
    qDebug() << att_double_temp;
    attenuation_selected = att_double_temp*2;*/
}

void MainWindow::generation_maintain(void)
{
    QByteArray ba;
    char len = 0x09;
    char crc = 0;
    char dataTransmit[9] = {SYNCHRO, 0x00, len, UART_ADDR, GENERATION_CTRL, 0x00, 0x00, 0x00, 0x00};
    /*dataTransmit[5] = ui->genBox->isChecked();
    dataTransmit[6] = ui->refBox->isChecked();
    dataTransmit[7] = ui->synBox->isChecked();*/
    for(int i = 0; i < len; i++)
    {
        crc ^= dataTransmit[i];
    }
    dataTransmit[8] = crc;
    ba.append(dataTransmit);
    qDebug() << ba;
    COM->write(dataTransmit, len);
    while(!COM->waitForBytesWritten(-1));
}

void MainWindow::send_freq_param(void)
{
    QByteArray ba_1;
    ba_1.clear();
    char len = 0x1E;
    char crc = 0;
    long_long_std_union centerFreq_1;
    centerFreq_1.llistd = centerFreq_edit->text().toLongLong();
    long_long_std_union deltaFreq_1;
    deltaFreq_1.llistd = deltaFreq_edit->text().toLongLong();
    long_long_std_union stepFreq_1;
    stepFreq_1.llistd = stepFreq_edit->text().toLongLong();
    ba_1.append(SYNCHRO);
    ba_1.append(char(0x00));
    ba_1.append(len);
    ba_1.append(UART_ADDR);
    ba_1.append(char(SEND_FREQ_PARAM));
    for(int i = 8; i != 0; i--)
    {
        ba_1.append(centerFreq_1.cstd[i-1]);
    }
    for(int i = 8; i != 0; i--)
    {
        ba_1.append(deltaFreq_1.cstd[i-1]);
    }
    for(int i = 8; i != 0; i--)
    {
        ba_1.append(stepFreq_1.cstd[i-1]);
    }
    for(int i = 0; i < ba_1.size(); i++)
    {
        crc ^= ba_1.at(i);
    }
    ba_1.append(crc);
//    qDebug() << ba_1;
    COM->write(ba_1);
    while(!COM->waitForBytesWritten(-1));
}

void MainWindow::add_freq_tag(void)
{
   /************** Antenna 1 ***************/
   tag_number = tag_select_1->currentIndex();
   tag_frequency[tag_number] = centerFreq_edit_1->text().toLongLong();
   band_frequency[tag_number] = deltaFreq_edit_1->text().toLongLong();
   sweep_step_frequency[tag_number] = stepFreq_edit_1->text().toLongLong();
   /************** Antenna 2 ***************/
   tag_number = tag_select_2->currentIndex();
   tag_frequency[tag_number+6] = centerFreq_edit_2->text().toLongLong();
   band_frequency[tag_number+6] = deltaFreq_edit_2->text().toLongLong();
   sweep_step_frequency[tag_number+6] = stepFreq_edit_2->text().toLongLong();
   /************** Antenna 3 ***************/
   tag_number = tag_select_3->currentIndex();
   tag_frequency[tag_number+12] = centerFreq_edit_3->text().toLongLong();
   band_frequency[tag_number+12] = deltaFreq_edit_3->text().toLongLong();
   sweep_step_frequency[tag_number+12] = stepFreq_edit_3->text().toLongLong();
}

void MainWindow::send_freq_param_total(void)
{
    QByteArray ba_1;
    ba_1.clear();
    std_union len;
    len.cstd[1] = 0x01;
    len.cstd[0] = 0xB0;
    char crc = 0;
    ba_1.append(SYNCHRO);
    ba_1.append(len.cstd[1]);
    ba_1.append(len.cstd[0]);
    ba_1.append(UART_ADDR);
    ba_1.append(char(SEND_FREQ_PARAM_TOTAL));
    long_long_std_union centerFreq;
    long_long_std_union deltaFreq;
    long_long_std_union stepFreq;

    for (int i = 0; i < 3; i++)
    {  
        for (int t = 0; t < 6; t++)
        {
           centerFreq.llistd = tag_frequency[t+i*6];
           for(int n = 8; n != 0; n--)
           {
               ba_1.append(centerFreq.cstd[n-1]);
           }
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int t = 0; t < 6; t++)
        {
           deltaFreq.llistd = band_frequency[t+i*6];
           for(int n = 8; n != 0; n--)
           {
               ba_1.append(deltaFreq.cstd[n-1]);
           }
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int t = 0; t < 6; t++)
        {
           stepFreq.llistd = sweep_step_frequency[t+i*6];
           for(int n = 8; n != 0; n--)
           {
               ba_1.append(stepFreq.cstd[n-1]);
           }
        }
    }

    for(int i = 0; i < ba_1.size(); i++)
    {
        crc ^= ba_1.at(i);
    }
    ba_1.append(crc);
//    qDebug() << ba_1;
    COM->write(ba_1);
    while(!COM->waitForBytesWritten(-1));
}

void MainWindow::test_mode_toggle(void)
{
    QByteArray ba_1;
    ba_1.clear();
    std_union len;
    len.cstd[1] = char(0x00);
    len.cstd[0] = 0x07;
    char crc = 0;
    ba_1.append(SYNCHRO);
    ba_1.append(len.cstd[1]);
    ba_1.append(len.cstd[0]);
    ba_1.append(UART_ADDR);
    ba_1.append(MODE_SELECT);
    if(test_radio_button->isChecked())
    {
        ba_1.append(char(ON));
    }
    else
    {
        ba_1.append(char(OFF));
    }

    for(int i = 0; i < ba.size(); i++)
    {
        crc ^= ba_1.at(i);
    }
    ba_1.append(crc);
    qDebug() << ba_1;
    COM->write(ba_1);
    while(!COM->waitForBytesWritten(-1));          //Если слать в закрытый порт будет зависание
}

void MainWindow::signal_type_toggle(void)
{
    if(signal_type->isChecked())
    {
        signal_type_mode = 1;
    }
    else
    {
        signal_type_mode = 0;
    }
}

uint16_t MainWindow::peak_search(DFT_result *data, uint16_t len)
{
    double derivative_data[len - 1];
    double derivative_average = 0;
    double derivative_sigma = 0;
    uint16_t max_index = 0;
    uint16_t low_freq_index = 0;
    uint16_t high_freq_index = 0;
    uint16_t band_mass_index = 0;
    uint16_t total_average_index = 0;
    uint16_t temp_counter = 0;

    for(int i = 0; i < (len - 1); i++)
    {
        derivative_data[i] = qFabs(data->module[i + 1] - data->module[i]);
    }

    for(int i = 0; i < (len - 1); i++)
    {
        derivative_average += derivative_data[i];
    }
    derivative_average /= (len - 1);

    for(int i = 0; i < (len - 1); i++)
    {
        derivative_sigma += qPow((derivative_data[i] - derivative_average), 2);
    }
    derivative_sigma /= (len - 1);
    derivative_sigma = qPow((derivative_sigma), 0.5);

    for(int i = 0; i < (len - 1); i++)
    {
        if(derivative_data[i + 1] > derivative_data[max_index])
        {
            max_index = i + 1;
        }
    }

    if((derivative_data[temp_counter] < (derivative_average + 2.5*derivative_sigma)))
    {
        do
        {
            temp_counter++;
            low_freq_index = temp_counter;

        }
        while((derivative_data[temp_counter] < (derivative_average + 2.5*derivative_sigma)) && (temp_counter < (len - 1)));
    }
    else
    {
        low_freq_index = temp_counter;
    }

    temp_counter = len - 2;
    if((derivative_data[temp_counter] < (derivative_average + 2.5*derivative_sigma)))
    {
        do
        {
            temp_counter--;
            high_freq_index = temp_counter;

        }
        while((derivative_data[temp_counter] < (derivative_average + 2.5*derivative_sigma)) && (temp_counter != 0));
    }
    else
    {
        high_freq_index = temp_counter;
    }

    derivative_points.clear();
    derivative_curve->setSamples(derivative_points);
    derivative_plot->replot();
    for (int i = 0; i < len - 1; i++)
    {
        derivative_points << QPointF(i, derivative_data[i]);
    }
    derivative_curve->setSamples(derivative_points);
    derivative_plot->replot();

    band_mass_index = (high_freq_index + low_freq_index)/2;
    total_average_index = (band_mass_index + max_index)/2;
    return total_average_index;
}

uint16_t MainWindow::peak_search_1(DFT_result *data, uint16_t len)
{
    double derivative_data[len - 1];
    double derivative_average = 0;
    double derivative_sigma = 0;
    uint16_t max_index = 0;
    uint16_t low_freq_index = 0;
    uint16_t high_freq_index = 0;
    uint16_t band_mass_index = 0;
    uint16_t total_average_index = 0;
    uint16_t temp_counter = 0;

    for(int i = 0; i < (len - 1); i++)
    {
        derivative_data[i] = qFabs(data->module[i + 1] - data->module[0]);
    }

    for(int i = 0; i < (len - 1); i++)
    {
        derivative_average += derivative_data[i];
    }
    derivative_average /= (len - 1);

    for(int i = 0; i < (len - 1); i++)
    {
        derivative_sigma += qPow((derivative_data[i] - derivative_average), 2);
    }
    derivative_sigma /= (len - 1);
    derivative_sigma = qPow((derivative_sigma), 0.5);

    for(int i = 0; i < (len - 1); i++)
    {
        if(derivative_data[i + 1] > derivative_data[max_index])
        {
            max_index = i + 1;
        }
    }

    if((derivative_data[temp_counter] < (derivative_average + 2.5*derivative_sigma)))
    {
        do
        {
            temp_counter++;
            low_freq_index = temp_counter;

        }
        while((derivative_data[temp_counter] < (derivative_average + 2.5*derivative_sigma)) && (temp_counter < (len - 1)));
    }
    else
    {
        low_freq_index = temp_counter;
    }

    temp_counter = len - 2;
    if((derivative_data[temp_counter] < (derivative_average + 2.5*derivative_sigma)))
    {
        do
        {
            temp_counter--;
            high_freq_index = temp_counter;

        }
        while((derivative_data[temp_counter] < (derivative_average + 2.5*derivative_sigma)) && (temp_counter != 0));
    }
    else
    {
        high_freq_index = temp_counter;
    }

    derivative_points.clear();
    derivative_curve->setSamples(derivative_points);
    derivative_plot->replot();
    for (int i = 0; i < len - 1; i++)
    {
        derivative_points << QPointF(i, derivative_data[i]);
    }
    derivative_curve->setSamples(derivative_points);
    derivative_plot->replot();

    band_mass_index = (high_freq_index + low_freq_index)/2;
    total_average_index = (band_mass_index + max_index)/2;
    return total_average_index;
}

double MainWindow::calc_temperature(uint16_t index)
{
    double temperature = 0;
    temperature = a * qPow(index, 2) + b * index + c;
    return temperature;
}

void MainWindow::get_a_coef(void)
{
    a = a_coefficient->text().toDouble();
}

void MainWindow::get_b_coef(void)
{
    b = b_coefficient->text().toDouble();
}

void MainWindow::get_c_coef(void)
{
    c = c_coefficient->text().toDouble();
}

/************************************************* TEST DFT FUNCTION ***************************************************/

void MainWindow::get_ready_test_parcel(void)
{
    uint16_t n = 406;
    uint16_t index_max = 0;
    //uint16_t window = 199;
    long_std_union data_temp;
    uint16_t len_effective = 0;
    uint8_t CRC_1 = 0;
    QByteArray ba_test;
    /*uint8_t mass[406] = {SYNCHRO, 0x01, 0x96, UART_ADDR, ADC_CONT_1SEC
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
                             0x00};*/
    /*uint8_t mass[406] = {SYNCHRO, 0x01, 0x96, UART_ADDR, ADC_CONT_1SEC
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96
                         , 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96, 0x03, 0x96,
                         0x00};*/
    /*uint8_t mass[406] = {SYNCHRO, 0x01, 0x96, UART_ADDR, ADC_CONT_1SEC
                             , 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00};*/
    /*uint8_t mass[406] = {SYNCHRO, 0x01, 0x96, UART_ADDR, ADC_CONT_1SEC
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7, 0x0F, 0xA7
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xA7, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                             , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                             0x00};*/

    for(int i = 0; i < n-1; i++)
    {
        CRC_1 ^= mass[test_mass_coounter][i];
    }
    mass[test_mass_coounter][405] = CRC_1;
    ba_test = QByteArray((char*)mass[test_mass_coounter], n);

    ba.clear();
    ba.append(ba_test);
    qDebug() << ba;
    len_effective = (n - SERVICE_BITS_LEN)/2;
    qDebug() << "reading...";
    for (int i = 0; i < len_effective; i++)
    {
        data_temp.cstd[1] = ba[i*2 + 5];
        data_temp.cstd[0] = ba[i*2 + 6];
        ADC_DATA_BUFFER[i] = (((data_temp.istd[0])));//average_filter median_filter lowpass_filter
        adc_call_command_counter++;
        //fileStream << QString::number(ADC_DATA_BUFFER[i]);
    }

    Fourier.module = new double[adc_call_command_counter];
    Fourier.real = new double[adc_call_command_counter];
    Fourier.image = new double[adc_call_command_counter];
    Fourier_1.module = new double[adc_call_command_counter];
    Fourier_1.real = new double[adc_call_command_counter];
    Fourier_1.image = new double[adc_call_command_counter];
    Fourier = discrete_FourierTransform(ADC_DATA_BUFFER, zero, 1, adc_call_command_counter);
    /*Fourier.real[0] = 0;
    Fourier.image[0] = 0;
    Fourier.module[0] = 0;*/
    /*for(uint16_t i = 0; i < 100; i++)
    {
        Fourier.real[i] = 0;
        Fourier.image[i] = 0;
        Fourier.module[i] = 0;
    }
    for(uint16_t i = 300; i < 400; i++)
    {
        Fourier.real[i] = 0;
        Fourier.image[i] = 0;
        Fourier.module[i] = 0;
    }*/
    /*for(uint16_t i = 0; i < adc_call_command_counter; i++)
    {
        qDebug() << Fourier.real[i] ;
        //qDebug() << Fourier.image[i];
        //qDebug() << Fourier.module[i];
        Fourier.real[i] -= 600;
        Fourier.image[i] += 600;
        Fourier.module[i] -= 510;
    }*/
    /*for(uint16_t i = 0; i < adc_call_command_counter; i++)
    {
        if
        Fourier.real[i] -= 510;
        Fourier.image[i] -= 510;
        Fourier.module[i] -= 510;
    }*/


    Fourier_1 = discrete_FourierTransform(Fourier.real, Fourier.image, -1, adc_call_command_counter);
    //fileStream << "Double Fourier";
    //qDebug() << (QString::number((Fourier.module[190], 'f', 2)));
    //fileStream << QString::number((Fourier.module[190], 'f', 2));//(double)Fourier_1.module[1];
    //fileStream << "/n";
    //fileStream.operator<<(QString::number((Fourier_1.module[2], 'f', 2)));
    clear_graph();
    paint_curve(adc_call_command_counter);
    /*index_max = peak_search(&Fourier_1, adc_call_command_counter);

    peak_points << QPointF(temperature_points, calc_temperature(index_max));
    temperature_points++;
    peak_curve->setSamples(peak_points);
    peak_plot->replot();*/

    if(temperature_interf_counter == 0)
    {
        temperature_interf_mass[temperature_interf_counter] = calc_temperature(peak_search(&Fourier_1, adc_call_command_counter));
        temperature_interf_counter++;
    }
    else if(temperature_interf_counter == 1)
    {
        temperature_interf_mass[temperature_interf_counter] = calc_temperature(peak_search(&Fourier_1, adc_call_command_counter));
        temperature_interf_derivative = temperature_interf_mass[temperature_interf_counter - 1] - temperature_interf_mass[temperature_interf_counter];
        if(qFabs(temperature_interf_derivative) >= temperature_interf_threshold)
        {
            temperature_interf_event = 1;
            temperature_interf_counter++;
        }
        else
        {
            peak_points << QPointF(temperature_points, temperature_interf_mass[temperature_interf_counter - 1]);
            peak_points << QPointF(temperature_points + 1, temperature_interf_mass[temperature_interf_counter]);
            temperature_interf_mass[temperature_interf_counter - 1] = temperature_interf_mass[temperature_interf_counter];
            temperature_points += 2;
        }

    }
    else if(temperature_interf_counter == 2)
    {
        if(temperature_interf_event == 1)
        {
            temperature_interf_mass[temperature_interf_counter] = calc_temperature(peak_search(&Fourier_1, adc_call_command_counter));
            temperature_interf_derivative = temperature_interf_mass[temperature_interf_counter - 1] - temperature_interf_mass[temperature_interf_counter];
            if(qFabs(temperature_interf_derivative) >= temperature_interf_threshold)
            {
                temperature_interf_event = 2;
                temperature_interf_mass[temperature_interf_counter - 1] = ((temperature_interf_mass[temperature_interf_counter] + temperature_interf_mass[temperature_interf_counter - 2]) / 2);
            }
            peak_points << QPointF(temperature_points, temperature_interf_mass[temperature_interf_counter - 2]);
            peak_points << QPointF(temperature_points + 1, temperature_interf_mass[temperature_interf_counter - 1]);
            peak_points << QPointF(temperature_points + 2, temperature_interf_mass[temperature_interf_counter]);
            temperature_interf_mass[temperature_interf_counter - 2] = temperature_interf_mass[temperature_interf_counter];
            temperature_interf_counter = 1;
            temperature_points += 3;
        }
    }

    //peak_points << QPointF(temperature_points, calc_temperature(peak_search(&Fourier_1, adc_call_command_counter)));
    //temperature_points++;
    peak_curve->setSamples(peak_points);
    peak_plot->replot();

    free(Fourier.module);
    free(Fourier.real);
    free(Fourier.image);
    free(Fourier_1.module);
    free(Fourier_1.real);
    free(Fourier_1.image);
    READER_DATA.RAW_SIZE = 0;
    adc_call_command_counter = 0;
    if(test_mass_coounter < 2)
    {
        test_mass_coounter++;
    }
    else
    {
        test_mass_coounter = 0;
    }
}

/************************************** AD5932 TEST FUNCTIONS *************************************/
void MainWindow::ad5932_send_data(void)
{
    QByteArray ba;
    long_long_std_union temp_1;
    QString string(freq_start->text());
    temp_1.llistd = string.toULongLong(0);
    //qDebug() << temp_1.llistd;
    char len = 0x1D;
    char crc = 0;
    char temp_data_byte = 0;
    ba.append(SYNCHRO);
    ba.append(char(0x00));
    ba.append(len);
    ba.append(UART_ADDR);
    ba.append(AD5932_CTR);
    for(int i = 8; i != 0; i--)
    {
        ba.append(temp_1.cstd[i-1]);
    }
    //qDebug() << ba;
    temp_1.llistd = 0;
    string = freq_delta->text();
    temp_1.llistd = string.toULongLong(0);
    for(int i = 8; i != 0; i--)
    {
        ba.append(temp_1.cstd[i-1]);
    }
    temp_1.llistd = 0;
    string = n_increment->text();
    temp_1.llistd = string.toUInt(0);
    for(int i = 2; i != 0; i--)
    {
        ba.append(temp_1.cstd[i-1]);
    }
    temp_1.llistd = 0;
    if(msb_status->isChecked())
    {
        temp_data_byte = 0x01;
    }
    else
    {
        temp_data_byte = 0x00;
    }
    ba.append(temp_data_byte);
    if(signal_type_status->isChecked())
    {
        temp_data_byte = 0x01;
    }
    else
    {
        temp_data_byte = 0x00;
    }
    ba.append(temp_data_byte);
    if(ctrl_type_status->isChecked())
    {
        temp_data_byte = 0x01;
    }
    else
    {
        temp_data_byte = 0x00;
    }
    ba.append(temp_data_byte);
    string = time_interval->text();
    temp_1.istd[0] = string.toUInt(0);
    for(int i = 2; i != 0; i--)
    {
        ba.append(temp_1.cstd[i-1]);
    }
    temp_1.llistd = 0;
    for(int i = 0; i < ba.size(); i++)
    {
        crc ^= ba.at(i);
    }
    ba.append(crc);
    //qDebug() << ba;
    COM->write(ba);
    while(!COM->waitForBytesWritten(-1));           //Если слать в закрытый порт будет зависание
}

/************************************** CRYSTAL GEN TEST FUNCTIONS *************************************/
void MainWindow::crystal_send_data(void)
{
    QByteArray ba;
    char len = 0x07;
    char crc = 0;
    char temp_data_byte = 0;
    ba.append(SYNCHRO);
    ba.append(char(0x00));
    ba.append(len);
    ba.append(UART_ADDR);
    ba.append(CRYSTAL_EN);
    if(crystal_status->isChecked())
    {
        temp_data_byte = 0x01;
    }
    else
    {
        temp_data_byte = 0x00;
    }
    ba.append(temp_data_byte);

    for(int i = 0; i < ba.size(); i++)
    {
        crc ^= ba.at(i);
    }
    ba.append(crc);
    qDebug() << ba;
    COM->write(ba);
    while(!COM->waitForBytesWritten(-1));
}

/************************************** ADF4360-0 TEST FUNCTIONS *************************************/
void MainWindow::adf4360_send_data(void)
{
    QByteArray ba;
    std_union temp_1;
    QString string(b_counter->text());
    temp_1.istd = string.toUInt(0);
    char len = 0x0C;
    char crc = 0;
    ba.append(SYNCHRO);
    ba.append(char(0x00));
    ba.append(len);
    ba.append(UART_ADDR);
    ba.append(ADF4360_CTR);
    for(int i = 2; i != 0; i--)
    {
        ba.append(temp_1.cstd[i-1]);
    }
    temp_1.istd = 0;
    string = r_counter->text();
    temp_1.istd = string.toUInt(0);
    for(int i = 2; i != 0; i--)
    {
        ba.append(temp_1.cstd[i-1]);
    }
    temp_1.istd = power_level->currentIndex();
    ba.append(temp_1.cstd[0]);
    temp_1.istd = p_prescaler->currentIndex();
    ba.append(temp_1.cstd[0]);
    temp_1.istd = 0;
    string = a_counter->text();
    temp_1.istd = string.toUInt(0);
    ba.append(temp_1.cstd[0]);

    for(int i = 0; i < ba.size(); i++)
    {
        crc ^= ba.at(i);
    }
    ba.append(crc);
    qDebug() << ba;
    COM->write(ba);
    while(!COM->waitForBytesWritten(-1));           //Если слать в закрытый порт будет зависание
}

void MainWindow::setup_the_plot(void)
{
    //График температуры; настройка
    plot->setTitle("Data"); // заголовок
    plot->setCanvasBackground( Qt::white ); // цвет фона

    // Параметры осей координат
    plot->setAxisTitle(QwtPlot::yLeft, "ADC Values");
    plot->setAxisTitle(QwtPlot::xBottom, "Time");
    plot->insertLegend( new QwtLegend() );
    plot->setAxisScale(QwtPlot::yLeft, 300, 400);
    plot->setAxisScale(QwtPlot::xBottom, 0, 50000);

    // Включить сетку
    // #include <qwt_plot_grid.h>
    QwtPlotGrid *grid1 = new QwtPlotGrid();    //
    grid1->setMajorPen(QPen( Qt::gray, 1 )); // цвет линий и толщина
    grid1->attach( plot ); // добавить сетку к полю графика

    //curve_temp->setTitle( "Температура" );
    curve->setPen( Qt::blue, 2); // цвет и толщина кривой
    curve_DFT->setPen( Qt::darkGreen, 4, Qt::SolidLine); // цвет и толщина кривой
    curve->setRenderHint(QwtPlotItem::RenderAntialiased, true); // сглаживание
    curve_DFT->setRenderHint(QwtPlotItem::RenderAntialiased, true); // сглаживание
    // Маркеры кривой
    // #include <qwt_symbol.h>
    /*QwtSymbol *symbol1 = new QwtSymbol( QwtSymbol::Ellipse,
                      QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 3, 3 ) );
    curve_temp->setSymbol( symbol1 );*/
    curve->attach( plot ); // отобразить кривую на графике
    curve_DFT->attach( plot ); // отобразить кривую на графике

    /***************************************** СПЕКТР ********************************************/

    //График температуры; настройка
    spectre_graph->setTitle("Data"); // заголовок
    spectre_graph->setCanvasBackground( Qt::white ); // цвет фона

    // Параметры осей координат
    spectre_graph->setAxisTitle(QwtPlot::yLeft, "Level Values");
    spectre_graph->setAxisTitle(QwtPlot::xBottom, "Frequency");
    spectre_graph->insertLegend( new QwtLegend() );
    spectre_graph->setAxisScale(QwtPlot::yLeft, 300, 400);
    spectre_graph->setAxisScale(QwtPlot::xBottom, 0, 50000);

    // Включить сетку
    // #include <qwt_plot_grid.h>
    QwtPlotGrid *grid2 = new QwtPlotGrid();    //
    grid2->setMajorPen(QPen( Qt::gray, 1 )); // цвет линий и толщина
    grid2->attach( spectre_graph ); // добавить сетку к полю графика

    //curve_temp->setTitle( "Температура" );
    spectre_spurs->setPen( Qt::red, 2); // цвет и толщина кривой
    spectre_spurs->setStyle(QwtPlotCurve::Sticks);
    //spectre_spurs->setRenderHint(QwtPlotItem::RenderAntialiased, true); // сглаживание
    // Маркеры кривой
    // #include <qwt_symbol.h>
    /*QwtSymbol *symbol1 = new QwtSymbol( QwtSymbol::Ellipse,
                      QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 3, 3 ) );
    curve_temp->setSymbol( symbol1 );*/
    spectre_spurs->attach(spectre_graph); // отобразить кривую на графике

    /************************************************ График производных ************************************************************/

    //График; настройка
    derivative_plot->setTitle("Derivative"); // заголовок
    derivative_plot->setCanvasBackground(Qt::white); // цвет фона

    // Параметры осей координат
    derivative_plot->setAxisTitle(QwtPlot::yLeft, "Level Values");
    derivative_plot->setAxisTitle(QwtPlot::xBottom, "Frequency");
    derivative_plot->insertLegend( new QwtLegend() );
    derivative_plot->setAxisScale(QwtPlot::yLeft, -400, 400);
    derivative_plot->setAxisScale(QwtPlot::xBottom, 0, 10000);

    // Включить сетку
    QwtPlotGrid *derivative_plot_grid = new QwtPlotGrid();    //
    derivative_plot_grid->setMajorPen(QPen(Qt::darkGray, 1)); // цвет линий и толщина
    derivative_plot_grid->attach(derivative_plot); // добавить сетку к полю графика

    derivative_curve->setPen(Qt::darkCyan, 2); // цвет и толщина кривой
    derivative_curve->setStyle(QwtPlotCurve::Lines);
    //spectre_spurs->setRenderHint(QwtPlotItem::RenderAntialiased, true); // сглаживание
    // Маркеры кривой
    // #include <qwt_symbol.h>
    /*QwtSymbol *symbol1 = new QwtSymbol( QwtSymbol::Ellipse,
                      QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 3, 3 ) );
    curve_temp->setSymbol( symbol1 );*/
    derivative_curve->attach(derivative_plot); // отобразить кривую на графике

    /************************************************ График температуры ************************************************************/

    //График; настройка
    peak_plot->setTitle("Temperature"); // заголовок
    peak_plot->setCanvasBackground(Qt::white); // цвет фона

    // Параметры осей координат
    peak_plot->setAxisTitle(QwtPlot::yLeft, "Level Values");
    peak_plot->setAxisTitle(QwtPlot::xBottom, "Frequency");
    peak_plot->insertLegend( new QwtLegend() );
    peak_plot->setAxisScale(QwtPlot::yLeft, -400, 400);
    peak_plot->setAxisScale(QwtPlot::xBottom, 0, 10000);

    // Включить сетку
    QwtPlotGrid *peak_plot_grid = new QwtPlotGrid();    //
    peak_plot_grid->setMajorPen(QPen(Qt::darkGray, 1)); // цвет линий и толщина
    peak_plot_grid->attach(peak_plot); // добавить сетку к полю графика

    peak_curve->setPen(Qt::darkMagenta, 2); // цвет и толщина кривой
    peak_curve->setStyle(QwtPlotCurve::Lines);
    //spectre_spurs->setRenderHint(QwtPlotItem::RenderAntialiased, true); // сглаживание
    // Маркеры кривой
    // #include <qwt_symbol.h>
    /*QwtSymbol *symbol1 = new QwtSymbol( QwtSymbol::Ellipse,
                      QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 3, 3 ) );
    curve_temp->setSymbol( symbol1 );*/
    peak_curve->attach(peak_plot); // отобразить кривую на графике
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
  if (e->button() == Qt::LeftButton)    // Left button...
  {
      plot->setAxisAutoScale(QwtPlot::xBottom, 1);
      plot->setAxisAutoScale(QwtPlot::yLeft, 1);
      spectre_graph->setAxisAutoScale(QwtPlot::xBottom, 1);
      spectre_graph->setAxisAutoScale(QwtPlot::yLeft, 1);
      derivative_plot->setAxisAutoScale(QwtPlot::xBottom, 1);
      derivative_plot->setAxisAutoScale(QwtPlot::yLeft, 1);
      peak_plot->setAxisAutoScale(QwtPlot::xBottom, 1);
      peak_plot->setAxisAutoScale(QwtPlot::yLeft, 1);
  }
  else if (e->button() == Qt::MiddleButton)   // Right button...
  {
      // Включить возможность приближения/удаления графика
      QwtPlotMagnifier *magnifier1 = new QwtPlotMagnifier(plot->canvas());
      // клавиша, активирующая приближение/удаление
      magnifier1->setMouseButton(Qt::MidButton);
      // Включить возможность перемещения по графику
      QwtPlotPanner *panner1 = new QwtPlotPanner(plot->canvas());
      // клавиша, активирующая перемещение
      panner1->setMouseButton( Qt::RightButton );

      // Включить возможность приближения/удаления графика
      QwtPlotMagnifier *magnifier2 = new QwtPlotMagnifier(spectre_graph->canvas());
      // клавиша, активирующая приближение/удаление
      magnifier2->setMouseButton(Qt::MidButton);
      // Включить возможность перемещения по графику
      QwtPlotPanner *panner2 = new QwtPlotPanner(spectre_graph->canvas());
      // клавиша, активирующая перемещение
      panner2->setMouseButton( Qt::RightButton );

      // Включить возможность приближения/удаления графика
      QwtPlotMagnifier *deriv_magnifier = new QwtPlotMagnifier(derivative_plot->canvas());
      // клавиша, активирующая приближение/удаление
      deriv_magnifier->setMouseButton(Qt::MidButton);
      // Включить возможность перемещения по графику
      QwtPlotPanner *deriv_panner = new QwtPlotPanner(derivative_plot->canvas());
      // клавиша, активирующая перемещение
      deriv_panner->setMouseButton( Qt::RightButton );

      // Включить возможность приближения/удаления графика
      QwtPlotMagnifier *peak_magnifier = new QwtPlotMagnifier(peak_plot->canvas());
      // клавиша, активирующая приближение/удаление
      peak_magnifier->setMouseButton(Qt::MidButton);
      // Включить возможность перемещения по графику
      QwtPlotPanner *peak_panner = new QwtPlotPanner(peak_plot->canvas());
      // клавиша, активирующая перемещение
      peak_panner->setMouseButton( Qt::RightButton );
  }
}

void MainWindow::clear_graph(void)
{
    //points.clear();
    points_DFT.clear();
    //curve->setSamples(points);
    curve_DFT->setSamples(points_DFT);
    plot->replot();

    spectre_points.clear();
    spectre_spurs->setSamples(spectre_points);
    spectre_graph->replot();
}

void MainWindow::paint_curve(uint16_t counter)
{
    for (uint16_t i = 0; i < counter; i++)
    {
        spectre_points << QPointF(i, Fourier.module[i]);
    }

    for (uint16_t i = 0; i < counter; i++)
    {
        //points << QPointF(i, ADC_DATA_BUFFER[i]); // координаты x, y
        points_DFT << QPointF(i, Fourier_1.module[i]);
    }

    //curve->setSamples(points);
    curve_DFT->setSamples(points_DFT);
    plot->replot();

    spectre_spurs->setSamples(spectre_points);
    spectre_graph->replot();
}

uint16_t MainWindow::median_filter(uint16_t datum)
{
 struct pair
 {
   struct pair   *point;                              /* Pointers forming list linked in sorted order */
   uint16_t  value;                                   /* Values to sort */
 };
 static struct pair buffer[MEDIAN_FILTER_SIZE] = {}; //{0} ;/* Buffer of nwidth pairs */
 static struct pair *datpoint = buffer;               /* Pointer into circular buffer of data */
 static struct pair small = {NULL, STOPPER};          /* Chain stopper */
 static struct pair big = {&small, 0};                /* Pointer to head (largest) of linked list.*/

 struct pair *successor;                              /* Pointer to successor of replaced data item */
 struct pair *scan;                                   /* Pointer used to scan down the sorted list */
 struct pair *scanold;                                /* Previous value of scan */
 struct pair *median;                                 /* Pointer to median */
 uint16_t i;

 if (datum == STOPPER)
 {
   datum = STOPPER + 1;                             /* No stoppers allowed. */
 }

 if ( (++datpoint - buffer) >= MEDIAN_FILTER_SIZE)
 {
   datpoint = buffer;                               /* Increment and wrap data in pointer.*/
 }

 datpoint->value = datum;                           /* Copy in new datum */
 successor = datpoint->point;                       /* Save pointer to old value's successor */
 median = &big;                                     /* Median initially to first in chain */
 scanold = NULL;                                    /* Scanold initially null. */
 scan = &big;                                       /* Points to pointer to first (largest) datum in chain */

 /* Handle chain-out of first item in chain as special case */
 if (scan->point == datpoint)
 {
   scan->point = successor;
 }
 scanold = scan;                                     /* Save this pointer and   */
 scan = scan->point ;                                /* step down chain */

 /* Loop through the chain, normal loop exit via break. */
 for (i = 0 ; i < MEDIAN_FILTER_SIZE; ++i)
 {
   /* Handle odd-numbered item in chain  */
   if (scan->point == datpoint)
   {
     scan->point = successor;                      /* Chain out the old datum.*/
   }

   if (scan->value < datum)                        /* If datum is larger than scanned value,*/
   {
     datpoint->point = scanold->point;             /* Chain it in here.  */
     scanold->point = datpoint;                    /* Mark it chained in. */
     datum = STOPPER;
   };

   /* Step median pointer down chain after doing odd-numbered element */
   median = median->point;                       /* Step median pointer.  */
   if (scan == &small)
   {
     break;                                      /* Break at end of chain  */
   }
   scanold = scan;                               /* Save this pointer and   */
   scan = scan->point;                           /* step down chain */

   /* Handle even-numbered item in chain.  */
   if (scan->point == datpoint)
   {
     scan->point = successor;
   }

   if (scan->value < datum)
   {
     datpoint->point = scanold->point;
     scanold->point = datpoint;
     datum = STOPPER;
   }

   if (scan == &small)
   {
     break;
   }

   scanold = scan;
   scan = scan->point;
 }
 return median->value;
}

uint16_t MainWindow::lowpass_filter(uint16_t datum)
{
    float ALPHA = 0.4;//0.2512;
    float BETA = (1 - ALPHA);

    static uint8_t low_pass_trigger = 0;
    static uint16_t in_values[LOW_PASS_FILTER_SIZE];
    static uint16_t out_values[LOW_PASS_FILTER_SIZE];
    static uint16_t lp_counter = 0;
    uint16_t local_counter = lp_counter;
    uint16_t value = 0;

    if(lp_counter == LOW_PASS_FILTER_SIZE)
    {
        lp_counter = 0;
        local_counter = (LOW_PASS_FILTER_SIZE-1);
    }

    in_values[lp_counter] = datum;
    if(low_pass_trigger != 0)
    {
        out_values[lp_counter] = ALPHA*out_values[local_counter-1] + BETA*in_values[lp_counter];
    }
    else
    {
        out_values[lp_counter] = datum;
        low_pass_trigger = 1;
    }
    value = out_values[lp_counter];
    lp_counter++;
    return value;
}

double MainWindow::lowpass_filter_double_1(double datum)
{
    float ALPHA = 0.7;//0.2512;
    float BETA = (1 - ALPHA);

    static uint8_t low_pass_trigger = 0;
    static double in_values[LOW_PASS_FILTER_SIZE];
    static double out_values[LOW_PASS_FILTER_SIZE];
    static uint16_t lp_counter = 0;
    uint16_t local_counter = lp_counter;
    double value = 0;

    if(lp_counter == LOW_PASS_FILTER_SIZE)
    {
        lp_counter = 0;
        local_counter = (LOW_PASS_FILTER_SIZE-1);
    }

    in_values[lp_counter] = datum;
    if(low_pass_trigger != 0)
    {
        out_values[lp_counter] = ALPHA*out_values[local_counter-1] + BETA*in_values[lp_counter];
    }
    else
    {
        out_values[lp_counter] = datum;
        low_pass_trigger = 1;
    }
    value = out_values[lp_counter];
    lp_counter++;
    return value;
}

double MainWindow::lowpass_filter_double_2(double datum)
{
    float ALPHA = 0.7;//0.2512;
    float BETA = (1 - ALPHA);

    static uint8_t low_pass_trigger = 0;
    static double in_values[LOW_PASS_FILTER_SIZE];
    static double out_values[LOW_PASS_FILTER_SIZE];
    static uint16_t lp_counter = 0;
    uint16_t local_counter = lp_counter;
    double value = 0;

    if(lp_counter == LOW_PASS_FILTER_SIZE)
    {
        lp_counter = 0;
        local_counter = (LOW_PASS_FILTER_SIZE-1);
    }

    in_values[lp_counter] = datum;
    if(low_pass_trigger != 0)
    {
        out_values[lp_counter] = ALPHA*out_values[local_counter-1] + BETA*in_values[lp_counter];
    }
    else
    {
        out_values[lp_counter] = datum;
        low_pass_trigger = 1;
    }
    value = out_values[lp_counter];
    lp_counter++;
    return value;
}

uint16_t MainWindow::average_filter(uint16_t datum)
{
    static uint16_t data_massive[AVERAGE_FILTER_SIZE];
    static uint16_t av_counter = 0;
    static uint8_t average_trigger = 0;
    uint32_t temp = 0;
    uint16_t value = 0;

    data_massive[av_counter] = datum;
    av_counter++;
    if(av_counter == AVERAGE_FILTER_SIZE)
    {
        av_counter = 0;
    }

    if(average_trigger != 0)
    {
        for(int i = 0; i < AVERAGE_FILTER_SIZE; i++)
        {
            temp += data_massive[i];
        }
        value = temp/AVERAGE_FILTER_SIZE;
    }
    else if(av_counter == (AVERAGE_FILTER_SIZE-1))
    {
        average_trigger = 1;
    }
    return value;

}

void MainWindow::through_filters_test(void)
{
    uint16_t acc_number = in_message->text().toUInt();
    //out_message->setText(QString::number(acc_number));

    out_message->setText(QString::number(lowpass_filter(acc_number)));
}

void MainWindow::not_received(void)
{

}

void MainWindow::sigma_filter(void)
{

}

MainWindow::DFT_result MainWindow::discrete_FourierTransform(double *massive_re, double *massive_im, char dir, uint16_t N)
{
    DFT_result out;
    uint16_t M = N;
    out.module = new double[M];
    out.real = new double[M];
    out.image = new double[M];

    //qDebug() << N;

    if(dir == 1)
    {
        for (uint16_t k = 0; k < M; k++)
        {
            out.real[k] = 0;
            out.image[k] = 0;
            for(uint16_t i = 0; i < N; i++)
            {
                out.real[k] = out.real[k] + (massive_re[i]*cos((2*M_PI/N)*i*k) + massive_im[i]*sin((2*M_PI/N)*i*k));
                //qDebug() << massive_im[i];
                //qDebug() << massive_re[i]*cos((2*M_PI/N)*i*k);
                //qDebug() << (massive_re[i]*cos((2*M_PI/N)*i*k) + massive_im[i]*sin((2*M_PI/N)*i*k));
                out.image[k] = out.image[k] + (-massive_re[i]*sin((2*M_PI/N)*i*k) + massive_im[i]*cos((2*M_PI/N)*i*k));
            }
            out.module[k] = sqrt(pow(out.real[k], 2) + pow(out.image[k], 2));

        }
    }
    else if(dir == -1)
    {
        for (uint16_t k = 0; k < N; k++)
        {
            out.real[k] = 0;
            out.image[k] = 0;
            for(uint16_t i = 0; i < M; i++)
            {
                out.real[k] = out.real[k] + (massive_re[i]*cos((2*M_PI/N)*i*k) - massive_im[i]*sin((2*M_PI/N)*i*k));
                out.image[k] = out.image[k] + (massive_re[i]*sin((2*M_PI/N)*i*k) + massive_im[i]*cos((2*M_PI/N)*i*k));
            }
            out.real[k] /= M;
            out.image[k] /= M;
            out.module[k] = sqrt(pow(out.real[k], 2) + pow(out.image[k], 2));
        }
    }

    return out;
}

void MainWindow::FFT(short int dir,long m,double *x,double *y)
{
    long n,i,i1,j,k,i2,l,l1,l2;
    double c1,c2,tx,ty,t1,t2,u1,u2,z;

    /* Calculate the number of points */
    n = 1;
    for (i=0;i<m;i++)
        n *= 2;

    /* Do the bit reversal */
    i2 = n >> 1;
    j = 0;
    for (i=0;i<n-1;i++) {
        if (i < j) {
            tx = x[i];
            ty = y[i];
            x[i] = x[j];
            y[i] = y[j];
            x[j] = tx;
            y[j] = ty;
        }
        k = i2;
        while (k <= j) {
            j -= k;
            k >>= 1;
        }
        j += k;
    }

    /* Compute the FFT */
    c1 = -1.0;
    c2 = 0.0;
    l2 = 1;
    for (l=0;l<m;l++) {
        l1 = l2;
        l2 <<= 1;
        u1 = 1.0;
        u2 = 0.0;
        for (j=0;j<l1;j++) {
            for (i=j;i<n;i+=l2) {
                i1 = i + l1;
                t1 = u1 * x[i1] - u2 * y[i1];
                t2 = u1 * y[i1] + u2 * x[i1];
                x[i1] = x[i] - t1;
                y[i1] = y[i] - t2;
                x[i] += t1;
                y[i] += t2;
            }
            z =  u1 * c1 - u2 * c2;
            u2 = u1 * c2 + u2 * c1;
            u1 = z;
        }
        c2 = sqrt((1.0 - c1) / 2.0);
        if (dir == 1)
            c2 = -c2;
        c1 = sqrt((1.0 + c1) / 2.0);
    }

    /* Scaling for forward transform */
    if (dir == 1) {
        for (i=0;i<n;i++) {
            x[i] /= n;
            y[i] /= n;
        }
    }
}

MainWindow::~MainWindow()
{
    File->close();
    delete ui;
}
