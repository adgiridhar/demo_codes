package cansat_2015;
import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.text.SimpleDateFormat;
import java.sql.Timestamp;
import java.util.*;
import java.io.*;
//------------------------------------------------------
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Toolkit;
import java.util.Random;
import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;
import static java.lang.Math.pow;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.ThermometerPlot;
import org.jfree.chart.plot.dial.*;
//import org.jfree.experimental.chart.plot.dial.DialPointer;
import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.DefaultCategoryDataset;
import org.jfree.data.general.DefaultValueDataset;
import org.jfree.ui.ApplicationFrame;
import org.jfree.ui.RefineryUtilities;
import java.util.Date;
import java.text.*;
/**
 *
 * @author GIRIDHAR A D
 */
public class CANSAT_2015 extends javax.swing.JFrame implements SerialPortEventListener
{
    //--------Serial Vars-------------------------//
    static CommPortIdentifier portId;
    static Enumeration portList;
    static BufferedReader input;
    static OutputStream output;
    SerialPort serialPort;
    Thread readThread;
    String ComPort = "";
    private static final int BAUD_RATE = 9600;
    private static final int TIME_OUT = 2000;
    static SimpleDateFormat sdfTime = new SimpleDateFormat("HH:mm:ss");
    Calendar now = Calendar.getInstance();
    static int S_hour, S_minute, S_seconds, S_millis, E_hour, E_minute, E_seconds, E_millis;
    //--------------GUI Special Vals-------------------//
    static Dimension screenDimension = Toolkit.getDefaultToolkit().getScreenSize();
    static double screenWidth = screenDimension.getWidth();
    static double screenHeight = screenDimension.getHeight();
    //----------Graph Vars----------------------------------------------//
    static int data, flag=0;
    static double chart_data=0;
    static int clear_count=0;
    static ChartPanel AltitudechartPanel,TemperaturechartPanel,inThermometerPanel,outThermometerPanel,rollpitchchartPanel;
    static DefaultCategoryDataset Altitudedataset = new DefaultCategoryDataset();
    static DefaultCategoryDataset Temperaturedataset = new DefaultCategoryDataset();
    public static DefaultValueDataset dataset_inT = new DefaultValueDataset();
    public static DefaultValueDataset dataset_outT = new DefaultValueDataset();
    static DefaultCategoryDataset rollpitchdataset = new DefaultCategoryDataset();
    static JFreeChart AltitudelineChart;
    static JFreeChart TemperaturelineChart;
    static JFreeChart rollpitchlineChart;
    static int startTime=(int) System.currentTimeMillis();
    static double [] inTempMat={27.05,27.10,27.10,27.10,27.10,27.10,27.10,26.40,26.40,26.40,26.30,27.10,27.00,27.00,27.00};
    static double [] outTempMat={25.63,25.60,25.60,25.60,25.60,25.55,25.55,25.70,25.70,25.49,25.49,25.49,25.65,25.65,25.65};
    //------------------IMAGES---------------------------//
    static String comm_dir = "C:\\Users\\GIRIDHAR A D\\Documents\\NetBeansProjects\\GUI_dependencies\\";
    static Image rollImg=Toolkit.getDefaultToolkit().getImage(comm_dir+"Resources\\Indicator_Background - Roll.jpg");
    static Image rollImg_=Toolkit.getDefaultToolkit().getImage(comm_dir+"roll_point.JPG");
    static Image pitchImg=Toolkit.getDefaultToolkit().getImage(comm_dir+"Resources\\Indicator_Background - Pitch.jpg");
    static Image pitchImg_=Toolkit.getDefaultToolkit().getImage(comm_dir+"Resources\\LongNeedleAltimeter.jpg");
    static Image yawImg=Toolkit.getDefaultToolkit().getImage(comm_dir+"Resources\\Indicator_Background - Yaw.jpg");
    static Image yawImg_=Toolkit.getDefaultToolkit().getImage(comm_dir+"roll_point.JPG");
    static Image logoImg=Toolkit.getDefaultToolkit().getImage(comm_dir+"Logo.JPG");
    static Image srmlogoImg=Toolkit.getDefaultToolkit().getImage(comm_dir+"SRM-University-logo.JPG");
    static Graphics2D g2d;
    
    //-------------------VALUES/UPDATION---------------//
    static double altitudeVal=0,descentRate=0,Roll=0,Pitch=0,Yaw=0,Acc_X=0, Acc_Y=0,Acc_Z=0;
    static double IN_temp=0,OUT_temp=0;
    static int delayTime = 30;//in millis
    //------------------FileOperations-----------------//
    static FileInputStream f_in = null;
    static FileOutputStream f_out = null;
    public static String file_dir = "C:\\Users\\GIRIDHAR A D\\Documents\\NetBeansProjects\\GUI_dependencies\\CSV Files\\";
    public static String file_name = "";
    static FileInputStream add_f_in = null;
    static FileOutputStream add_f_out = null;
    public static String add_file_dir = "C:\\Users\\GIRIDHAR A D\\Documents\\NetBeansProjects\\GUI_dependencies\\CSV Files\\";
    public static String add_file_name = "additional.csv";
    
    public CANSAT_2015() throws IOException 
    {
        initComponents();
        create_AltitudeChart();
        create_TemperatureChart();
        create_rollpitchChart();
        try{
    add_f_out = new FileOutputStream(add_file_dir+add_file_name);
}
    catch(Exception e)
    {
        System.out.println(e);
    }
    }
    
    public void paintComponent(Graphics g){
         g2d=(Graphics2D)g; // Create a Java2D version of g.
         //g2d.translate(150, 50); // Translate the center of our coordinates.
         g2d.rotate(randInt()/(180/3.141),150,100);///(180/3.141));  // Rotate the image by 1 radian.
         g2d.drawImage(rollImg, 0, 0, 300, 200, this);
    }
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">                          
    private void initComponents() {

        connectionPanel = new javax.swing.JPanel();
        serialCommLabel = new javax.swing.JLabel();
        connectButton = new javax.swing.JButton();
        jComboBox1 = new javax.swing.JComboBox();
        disconnectButton = new javax.swing.JButton();
        resetButton = new javax.swing.JButton();
        statusLabel = new javax.swing.JLabel();
        jLabel17 = new javax.swing.JLabel();
        launchtimeLabel = new javax.swing.JLabel();
        jLabel19 = new javax.swing.JLabel();
        elapsedtimeLabel = new javax.swing.JLabel();
        jPanel2 = new javax.swing.JPanel();
        jLabel18 = new javax.swing.JLabel();
        FSWLabel = new javax.swing.JLabel();
        dataPanel = new javax.swing.JPanel();
        realtimedata = new javax.swing.JLabel();
        comportLabel = new javax.swing.JLabel();
        jLabel8 = new javax.swing.JLabel();
        jLabel9 = new javax.swing.JLabel();
        jLabel10 = new javax.swing.JLabel();
        jLabel11 = new javax.swing.JLabel();
        jLabel12 = new javax.swing.JLabel();
        jLabel13 = new javax.swing.JLabel();
        jLabel14 = new javax.swing.JLabel();
        jLabel15 = new javax.swing.JLabel();
        jLabel16 = new javax.swing.JLabel();
        descentrateLabel1 = new javax.swing.JLabel();
        inTempLabel1 = new javax.swing.JLabel();
        altitudeLabel2 = new javax.swing.JLabel();
        outTempLabel1 = new javax.swing.JLabel();
        rollLabel1 = new javax.swing.JLabel();
        pitchLabel1 = new javax.swing.JLabel();
        accxLabel = new javax.swing.JLabel();
        accyLabel = new javax.swing.JLabel();
        acczLabel = new javax.swing.JLabel();
        realtimedataTextField = new javax.swing.JTextField();
        jScrollPane1 = new javax.swing.JScrollPane();
        realtimedataTextArea = new javax.swing.JTextArea();
        SaveCSV = new javax.swing.JButton();
        CreateCSV = new javax.swing.JButton();
        jLabel7 = new javax.swing.JLabel();
        BatteryLabel = new javax.swing.JLabel();
        jLabel23 = new javax.swing.JLabel();
        PressureLabel = new javax.swing.JLabel();
        altitudePanel = new javax.swing.JPanel();
        altitudeGraph = new javax.swing.JPanel();
        Altitude = new javax.swing.JLabel();
        altitudeLabel = new javax.swing.JLabel();
        mLabel = new javax.swing.JLabel();
        Altitude1 = new javax.swing.JLabel();
        descentrateLabel = new javax.swing.JLabel();
        mLabel1 = new javax.swing.JLabel();
        temperaturePanel = new javax.swing.JPanel();
        temperatureGraph = new javax.swing.JPanel();
        inThermometer = new javax.swing.JPanel();
        outThermometer = new javax.swing.JPanel();
        TemperatureLabel = new javax.swing.JLabel();
        INLabel = new javax.swing.JLabel();
        outTempLabel = new javax.swing.JLabel();
        OUTLabel = new javax.swing.JLabel();
        degC = new javax.swing.JLabel();
        degC1 = new javax.swing.JLabel();
        inTempLabel = new javax.swing.JLabel();
        imuPanel = new javax.swing.JPanel();
        roll = new javax.swing.JPanel(){
            @Override
            protected void paintComponent(Graphics g){
                super.paintComponent(g);
                g2d=(Graphics2D)g; // Create a Java2D version of g.
                //g2d.translate(150, 50); // Translate the center of our coordinates.
                g.drawImage(rollImg, 0, 0, roll.getHeight(), roll.getWidth(), this);

                g2d.rotate(Roll/(180/3.141),roll.getHeight()/2,roll.getWidth()/2);///(180/3.141));  // Rotate the image by 1 radian.
            g2d.drawImage(rollImg_, roll.getHeight()/2-(150/2),roll.getWidth()/2, 150,20, this);
        }
    };
    pitch = new javax.swing.JPanel(){
        @Override
        protected void paintComponent(Graphics g){
            super.paintComponent(g);
            g2d=(Graphics2D)g; // Create a Java2D version of g.
            //g2d.translate(150, 50); // Translate the center of our coordinates.
            g.drawImage(pitchImg, 0, 0, pitch.getHeight(), pitch.getWidth(), this);

            g2d.rotate(Pitch/(180/3.141),pitch.getHeight()/2,pitch.getWidth()/2);///(180/3.141));  // Rotate the image by 1 radian.
        g2d.drawImage(pitchImg_, pitch.getHeight()/2-10,pitch.getWidth()/2-10, 70, 20, this);
    }
    };
    yaw = new javax.swing.JPanel(){
        @Override
        protected void paintComponent(Graphics g){
            super.paintComponent(g);
            g2d=(Graphics2D)g; // Create a Java2D version of g.
            //g2d.translate(150, 50); // Translate the center of our coordinates.
            g.drawImage(yawImg, 0, 0, yaw.getHeight(), yaw.getWidth(), this);

            g2d.rotate(Yaw/(180/3.141),yaw.getHeight()/2,yaw.getWidth()/2);///(180/3.141));  // Rotate the image by 1 radian.
        g2d.drawImage(yawImg_, yaw.getHeight()/2-(100/2),yaw.getWidth()/2, 100, 10, this);
    }
    };
    rollpitchGraph = new javax.swing.JPanel();
    IMUDataLabel = new javax.swing.JLabel();
    jLabel1 = new javax.swing.JLabel();
    jLabel2 = new javax.swing.JLabel();
    jLabel3 = new javax.swing.JLabel();
    rollLabel = new javax.swing.JLabel();
    pitchLabel = new javax.swing.JLabel();
    yawLabel = new javax.swing.JLabel();
    gpsPanel = new javax.swing.JPanel();
    GPSDataLabel = new javax.swing.JLabel();
    jLabel4 = new javax.swing.JLabel();
    jLabel6 = new javax.swing.JLabel();
    latitudeLabel = new javax.swing.JLabel();
    altitudeLabel1 = new javax.swing.JLabel();
    jPanel1 = new javax.swing.JPanel();
    jLabel20 = new javax.swing.JLabel();
    jLabel21 = new javax.swing.JLabel();
    jLabel22 = new javax.swing.JLabel();
    acczLabel1 = new javax.swing.JLabel();
    accyLabel1 = new javax.swing.JLabel();
    accxLabel1 = new javax.swing.JLabel();
    jLabel24 = new javax.swing.JLabel();

    setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
    setBounds(new java.awt.Rectangle(0, 0, 0, 0));
    setMinimumSize(screenDimension);
    getContentPane().setLayout(new org.netbeans.lib.awtextra.AbsoluteLayout());

    connectionPanel.setBackground(new java.awt.Color(102, 102, 102));
    connectionPanel.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));

    serialCommLabel.setFont(new java.awt.Font("Tahoma", 1, 32)); // NOI18N
    serialCommLabel.setForeground(new java.awt.Color(255, 255, 255));
    serialCommLabel.setText("Serial Communication Status:");

    connectButton.setFont(new java.awt.Font("Tahoma", 1, 36)); // NOI18N
    connectButton.setForeground(new java.awt.Color(0, 153, 0));
    connectButton.setText("Connect");
    connectButton.addActionListener(new java.awt.event.ActionListener() {
        public void actionPerformed(java.awt.event.ActionEvent evt) {
            connectButtonActionPerformed(evt);
        }
    });

    jComboBox1.setFont(new java.awt.Font("Tahoma", 0, 32)); // NOI18N
    jComboBox1.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "Choose Item.." }));
    jComboBox1.addActionListener(new java.awt.event.ActionListener() {
        public void actionPerformed(java.awt.event.ActionEvent evt) {
            jComboBox1ActionPerformed(evt);
        }
    });

    disconnectButton.setFont(new java.awt.Font("Tahoma", 1, 36)); // NOI18N
    disconnectButton.setForeground(new java.awt.Color(255, 0, 0));
    disconnectButton.setText("Disconnect");
    disconnectButton.addActionListener(new java.awt.event.ActionListener() {
        public void actionPerformed(java.awt.event.ActionEvent evt) {
            disconnectButtonActionPerformed(evt);
        }
    });

    resetButton.setFont(new java.awt.Font("Tahoma", 1, 36)); // NOI18N
    resetButton.setForeground(new java.awt.Color(0, 0, 153));
    resetButton.setText("Reset");
    resetButton.addActionListener(new java.awt.event.ActionListener() {
        public void actionPerformed(java.awt.event.ActionEvent evt) {
            resetButtonActionPerformed(evt);
        }
    });

    statusLabel.setFont(new java.awt.Font("Tahoma", 1, 32)); // NOI18N
    statusLabel.setForeground(new java.awt.Color(255, 255, 255));
    statusLabel.setText("Not Connected");

    jLabel17.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    jLabel17.setForeground(new java.awt.Color(255, 255, 255));
    jLabel17.setText("Lauch Time");

    launchtimeLabel.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    launchtimeLabel.setForeground(new java.awt.Color(255, 255, 255));
    launchtimeLabel.setText("HH:MM:SS");

    jLabel19.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    jLabel19.setForeground(new java.awt.Color(255, 255, 255));
    jLabel19.setText("Elapsed Time");

    elapsedtimeLabel.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    elapsedtimeLabel.setForeground(new java.awt.Color(255, 255, 255));
    elapsedtimeLabel.setText("HH:MM:SS");

    jPanel2 = new javax.swing.JPanel(){
        @Override
        protected void paintComponent(Graphics g){
            super.paintComponent(g);
            g2d=(Graphics2D)g; // Create a Java2D version of g.
            //g2d.translate(150, 50); // Translate the center of our coordinates.
            g.drawImage(logoImg, 0, 0, jPanel2.getHeight(), jPanel2.getWidth(), this);

        }
    };

    javax.swing.GroupLayout jPanel2Layout = new javax.swing.GroupLayout(jPanel2);
    jPanel2.setLayout(jPanel2Layout);
    jPanel2Layout.setHorizontalGroup(
        jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGap(0, 151, Short.MAX_VALUE)
    );
    jPanel2Layout.setVerticalGroup(
        jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGap(0, 150, Short.MAX_VALUE)
    );

    jLabel18.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    jLabel18.setForeground(new java.awt.Color(255, 255, 255));
    jLabel18.setText("FSW State");

    FSWLabel.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    FSWLabel.setForeground(new java.awt.Color(255, 255, 255));
    FSWLabel.setText("Value");

    javax.swing.GroupLayout connectionPanelLayout = new javax.swing.GroupLayout(connectionPanel);
    connectionPanel.setLayout(connectionPanelLayout);
    connectionPanelLayout.setHorizontalGroup(
        connectionPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(connectionPanelLayout.createSequentialGroup()
            .addGroup(connectionPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(connectionPanelLayout.createSequentialGroup()
                    .addContainerGap()
                    .addComponent(serialCommLabel)
                    .addGap(0, 0, Short.MAX_VALUE))
                .addGroup(connectionPanelLayout.createSequentialGroup()
                    .addGap(24, 24, 24)
                    .addGroup(connectionPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(connectionPanelLayout.createSequentialGroup()
                            .addGroup(connectionPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                .addGroup(connectionPanelLayout.createSequentialGroup()
                                    .addComponent(jLabel18, javax.swing.GroupLayout.PREFERRED_SIZE, 115, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addGap(72, 72, 72)
                                    .addComponent(FSWLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 115, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGroup(connectionPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                                    .addGroup(connectionPanelLayout.createSequentialGroup()
                                        .addComponent(jLabel19, javax.swing.GroupLayout.PREFERRED_SIZE, 150, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                        .addComponent(elapsedtimeLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 115, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addGroup(connectionPanelLayout.createSequentialGroup()
                                        .addComponent(jLabel17, javax.swing.GroupLayout.PREFERRED_SIZE, 131, javax.swing.GroupLayout.PREFERRED_SIZE)
                                        .addGap(56, 56, 56)
                                        .addComponent(launchtimeLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 115, javax.swing.GroupLayout.PREFERRED_SIZE))))
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(jPanel2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                        .addGroup(connectionPanelLayout.createSequentialGroup()
                            .addGroup(connectionPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                                .addComponent(connectButton, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(disconnectButton, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 39, Short.MAX_VALUE)
                            .addGroup(connectionPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                .addComponent(resetButton, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                .addComponent(jComboBox1, 0, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))))
            .addContainerGap())
        .addGroup(connectionPanelLayout.createSequentialGroup()
            .addContainerGap()
            .addComponent(statusLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 475, javax.swing.GroupLayout.PREFERRED_SIZE)
            .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
    );
    connectionPanelLayout.setVerticalGroup(
        connectionPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(connectionPanelLayout.createSequentialGroup()
            .addContainerGap()
            .addComponent(serialCommLabel)
            .addGap(18, 18, 18)
            .addComponent(statusLabel)
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 17, Short.MAX_VALUE)
            .addGroup(connectionPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addComponent(jComboBox1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGroup(connectionPanelLayout.createSequentialGroup()
                    .addGap(4, 4, 4)
                    .addComponent(connectButton, javax.swing.GroupLayout.PREFERRED_SIZE, 50, javax.swing.GroupLayout.PREFERRED_SIZE)))
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(connectionPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                .addGroup(connectionPanelLayout.createSequentialGroup()
                    .addComponent(jPanel2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addContainerGap())
                .addGroup(connectionPanelLayout.createSequentialGroup()
                    .addGroup(connectionPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                        .addComponent(disconnectButton, javax.swing.GroupLayout.PREFERRED_SIZE, 48, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(resetButton, javax.swing.GroupLayout.PREFERRED_SIZE, 0, Short.MAX_VALUE))
                    .addGap(18, 18, 18)
                    .addGroup(connectionPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(jLabel17)
                        .addComponent(launchtimeLabel))
                    .addGap(18, 18, 18)
                    .addGroup(connectionPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(elapsedtimeLabel)
                        .addComponent(jLabel19))
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                    .addGroup(connectionPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(jLabel18)
                        .addComponent(FSWLabel))
                    .addGap(29, 29, 29))))
    );

    getContentPane().add(connectionPanel, new org.netbeans.lib.awtextra.AbsoluteConstraints(1, 0, 560, 410));

    dataPanel.setBackground(new java.awt.Color(102, 102, 102));
    dataPanel.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));

    realtimedata.setFont(new java.awt.Font("Tahoma", 1, 36)); // NOI18N
    realtimedata.setForeground(new java.awt.Color(255, 255, 255));
    realtimedata.setText("Real Time Data from Port:");

    comportLabel.setFont(new java.awt.Font("Tahoma", 1, 36)); // NOI18N
    comportLabel.setForeground(new java.awt.Color(255, 255, 255));
    comportLabel.setText("COM");

    jLabel8.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    jLabel8.setForeground(new java.awt.Color(255, 255, 255));
    jLabel8.setText("Altitude (m)");

    jLabel9.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    jLabel9.setForeground(new java.awt.Color(255, 255, 255));
    jLabel9.setText("Descent Rate (m/s)");

    jLabel10.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    jLabel10.setForeground(new java.awt.Color(255, 255, 255));
    jLabel10.setText("IN Temp 'C");

    jLabel11.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    jLabel11.setForeground(new java.awt.Color(255, 255, 255));
    jLabel11.setText("Pitch");

    jLabel12.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    jLabel12.setForeground(new java.awt.Color(255, 255, 255));
    jLabel12.setText("Roll");

    jLabel13.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    jLabel13.setForeground(new java.awt.Color(255, 255, 255));
    jLabel13.setText("OUT Temp 'C");

    jLabel14.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    jLabel14.setForeground(new java.awt.Color(255, 255, 255));
    jLabel14.setText("Acc Z");

    jLabel15.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    jLabel15.setForeground(new java.awt.Color(255, 255, 255));
    jLabel15.setText("Acc X");

    jLabel16.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    jLabel16.setForeground(new java.awt.Color(255, 255, 255));
    jLabel16.setText("Acc Y");

    descentrateLabel1.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    descentrateLabel1.setForeground(new java.awt.Color(255, 255, 255));
    descentrateLabel1.setText("Value");

    inTempLabel1.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    inTempLabel1.setForeground(new java.awt.Color(255, 255, 255));
    inTempLabel1.setText("Value");

    altitudeLabel2.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    altitudeLabel2.setForeground(new java.awt.Color(255, 255, 255));
    altitudeLabel2.setText("Value");

    outTempLabel1.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    outTempLabel1.setForeground(new java.awt.Color(255, 255, 255));
    outTempLabel1.setText("Value");

    rollLabel1.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    rollLabel1.setForeground(new java.awt.Color(255, 255, 255));
    rollLabel1.setText("Value");

    pitchLabel1.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    pitchLabel1.setForeground(new java.awt.Color(255, 255, 255));
    pitchLabel1.setText("Value");

    accxLabel.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    accxLabel.setForeground(new java.awt.Color(255, 255, 255));
    accxLabel.setText("Value");

    accyLabel.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    accyLabel.setForeground(new java.awt.Color(255, 255, 255));
    accyLabel.setText("Value");

    acczLabel.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    acczLabel.setForeground(new java.awt.Color(255, 255, 255));
    acczLabel.setText("Value");

    realtimedataTextField.setFont(new java.awt.Font("Tahoma", 1, 18)); // NOI18N
    realtimedataTextField.setText("realtimedata");

    realtimedataTextArea.setColumns(20);
    realtimedataTextArea.setRows(5);
    jScrollPane1.setViewportView(realtimedataTextArea);

    SaveCSV.setText("Save CSV");
    SaveCSV.addActionListener(new java.awt.event.ActionListener() {
        public void actionPerformed(java.awt.event.ActionEvent evt) {
            SaveCSVActionPerformed(evt);
        }
    });

    CreateCSV.setText("Create CSV");
    CreateCSV.addActionListener(new java.awt.event.ActionListener() {
        public void actionPerformed(java.awt.event.ActionEvent evt) {
            CreateCSVActionPerformed(evt);
        }
    });

    jLabel7.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    jLabel7.setForeground(new java.awt.Color(255, 255, 255));
    jLabel7.setText("Battery");

    BatteryLabel.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    BatteryLabel.setForeground(new java.awt.Color(255, 255, 255));
    BatteryLabel.setText("Value");

    jLabel23.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    jLabel23.setForeground(new java.awt.Color(255, 255, 255));
    jLabel23.setText("Pressure");

    PressureLabel.setFont(new java.awt.Font("Tahoma", 0, 24)); // NOI18N
    PressureLabel.setForeground(new java.awt.Color(255, 255, 255));
    PressureLabel.setText("Value");

    javax.swing.GroupLayout dataPanelLayout = new javax.swing.GroupLayout(dataPanel);
    dataPanel.setLayout(dataPanelLayout);
    dataPanelLayout.setHorizontalGroup(
        dataPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(dataPanelLayout.createSequentialGroup()
            .addGap(10, 10, 10)
            .addComponent(realtimedata)
            .addContainerGap(74, Short.MAX_VALUE))
        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, dataPanelLayout.createSequentialGroup()
            .addContainerGap()
            .addGroup(dataPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addComponent(realtimedataTextField)
                .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, dataPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(SaveCSV, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(CreateCSV, javax.swing.GroupLayout.PREFERRED_SIZE, 101, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addComponent(jScrollPane1, javax.swing.GroupLayout.Alignment.TRAILING)
                .addGroup(dataPanelLayout.createSequentialGroup()
                    .addGap(55, 55, 55)
                    .addGroup(dataPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(dataPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(jLabel10)
                            .addComponent(jLabel9)
                            .addComponent(jLabel11)
                            .addComponent(jLabel12)
                            .addComponent(jLabel13)
                            .addComponent(jLabel14)
                            .addComponent(jLabel15)
                            .addComponent(jLabel16)
                            .addComponent(jLabel7))
                        .addComponent(jLabel8, javax.swing.GroupLayout.Alignment.TRAILING)
                        .addComponent(jLabel23, javax.swing.GroupLayout.Alignment.TRAILING))
                    .addGap(26, 26, 26)
                    .addGroup(dataPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addComponent(altitudeLabel2)
                        .addComponent(PressureLabel)
                        .addComponent(descentrateLabel1)
                        .addComponent(inTempLabel1)
                        .addComponent(outTempLabel1)
                        .addComponent(rollLabel1)
                        .addComponent(pitchLabel1)
                        .addComponent(accxLabel)
                        .addComponent(accyLabel)
                        .addComponent(acczLabel)
                        .addComponent(BatteryLabel))
                    .addGap(0, 0, Short.MAX_VALUE)))
            .addContainerGap())
        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, dataPanelLayout.createSequentialGroup()
            .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(comportLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 137, javax.swing.GroupLayout.PREFERRED_SIZE)
            .addGap(31, 31, 31))
    );
    dataPanelLayout.setVerticalGroup(
        dataPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(dataPanelLayout.createSequentialGroup()
            .addContainerGap()
            .addComponent(realtimedata)
            .addGroup(dataPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(dataPanelLayout.createSequentialGroup()
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                    .addComponent(comportLabel)
                    .addGap(342, 342, 342)
                    .addComponent(CreateCSV)
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(SaveCSV))
                .addGroup(dataPanelLayout.createSequentialGroup()
                    .addGap(86, 86, 86)
                    .addGroup(dataPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(jLabel8)
                        .addComponent(altitudeLabel2))
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                    .addGroup(dataPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(PressureLabel)
                        .addComponent(jLabel23))
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                    .addGroup(dataPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(jLabel9)
                        .addComponent(descentrateLabel1))
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                    .addGroup(dataPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(jLabel10)
                        .addComponent(inTempLabel1))
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                    .addGroup(dataPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(dataPanelLayout.createSequentialGroup()
                            .addComponent(jLabel13)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(jLabel12)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(jLabel11)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(jLabel15)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(jLabel16)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(jLabel14)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addGroup(dataPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                                .addComponent(jLabel7)
                                .addComponent(BatteryLabel)))
                        .addGroup(dataPanelLayout.createSequentialGroup()
                            .addComponent(outTempLabel1)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(rollLabel1)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(pitchLabel1)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(accxLabel)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(accyLabel)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(acczLabel)))))
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(realtimedataTextField, javax.swing.GroupLayout.PREFERRED_SIZE, 47, javax.swing.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 374, javax.swing.GroupLayout.PREFERRED_SIZE)
            .addContainerGap(24, Short.MAX_VALUE))
    );

    getContentPane().add(dataPanel, new org.netbeans.lib.awtextra.AbsoluteConstraints(0, 420, 560, 1020));

    altitudePanel.setBackground(new java.awt.Color(102, 102, 102));
    altitudePanel.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));

    Altitude.setFont(new java.awt.Font("Tahoma", 1, 36)); // NOI18N
    Altitude.setForeground(new java.awt.Color(255, 255, 255));
    Altitude.setText("Altitude");

    altitudeLabel.setFont(new java.awt.Font("Tahoma", 1, 36)); // NOI18N
    altitudeLabel.setForeground(new java.awt.Color(255, 255, 255));
    altitudeLabel.setText("Val");

    mLabel.setFont(new java.awt.Font("Tahoma", 1, 36)); // NOI18N
    mLabel.setForeground(new java.awt.Color(255, 255, 255));
    mLabel.setText("m");

    Altitude1.setFont(new java.awt.Font("Tahoma", 1, 36)); // NOI18N
    Altitude1.setForeground(new java.awt.Color(255, 255, 255));
    Altitude1.setText("Descent Rate");

    descentrateLabel.setFont(new java.awt.Font("Tahoma", 1, 36)); // NOI18N
    descentrateLabel.setForeground(new java.awt.Color(255, 255, 255));
    descentrateLabel.setText("Val");

    mLabel1.setFont(new java.awt.Font("Tahoma", 1, 36)); // NOI18N
    mLabel1.setForeground(new java.awt.Color(255, 255, 255));
    mLabel1.setText("m/s");

    javax.swing.GroupLayout altitudePanelLayout = new javax.swing.GroupLayout(altitudePanel);
    altitudePanel.setLayout(altitudePanelLayout);
    altitudePanelLayout.setHorizontalGroup(
        altitudePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(altitudePanelLayout.createSequentialGroup()
            .addContainerGap()
            .addGroup(altitudePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addComponent(altitudeGraph, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addGroup(altitudePanelLayout.createSequentialGroup()
                    .addGroup(altitudePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addComponent(Altitude1)
                        .addComponent(Altitude))
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                    .addGroup(altitudePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                        .addComponent(descentrateLabel, javax.swing.GroupLayout.DEFAULT_SIZE, 147, Short.MAX_VALUE)
                        .addComponent(altitudeLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                    .addGap(34, 34, 34)
                    .addGroup(altitudePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addComponent(mLabel)
                        .addComponent(mLabel1))
                    .addGap(0, 264, Short.MAX_VALUE)))
            .addContainerGap())
    );
    altitudePanelLayout.setVerticalGroup(
        altitudePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, altitudePanelLayout.createSequentialGroup()
            .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addGroup(altitudePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                .addComponent(Altitude, javax.swing.GroupLayout.PREFERRED_SIZE, 34, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addComponent(altitudeLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 34, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addComponent(mLabel))
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
            .addGroup(altitudePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                .addComponent(Altitude1, javax.swing.GroupLayout.PREFERRED_SIZE, 34, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addComponent(descentrateLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 34, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addComponent(mLabel1))
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(altitudeGraph, javax.swing.GroupLayout.PREFERRED_SIZE, 476, javax.swing.GroupLayout.PREFERRED_SIZE)
            .addContainerGap())
    );

    getContentPane().add(altitudePanel, new org.netbeans.lib.awtextra.AbsoluteConstraints(570, 100, 800, 610));

    temperaturePanel.setBackground(new java.awt.Color(102, 102, 102));
    temperaturePanel.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));

    TemperatureLabel.setFont(new java.awt.Font("Tahoma", 1, 36)); // NOI18N
    TemperatureLabel.setForeground(new java.awt.Color(255, 255, 255));
    TemperatureLabel.setText("Temperature");

    INLabel.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    INLabel.setForeground(new java.awt.Color(255, 255, 255));
    INLabel.setText("IN");

    outTempLabel.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    outTempLabel.setForeground(new java.awt.Color(255, 255, 255));
    outTempLabel.setText("Val");

    OUTLabel.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    OUTLabel.setForeground(new java.awt.Color(255, 255, 255));
    OUTLabel.setText("OUT");

    degC.setFont(new java.awt.Font("Tahoma", 1, 18)); // NOI18N
    degC.setForeground(new java.awt.Color(255, 255, 255));
    degC.setText("*C");

    degC1.setFont(new java.awt.Font("Tahoma", 1, 18)); // NOI18N
    degC1.setForeground(new java.awt.Color(255, 255, 255));
    degC1.setText("*C");

    inTempLabel.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    inTempLabel.setForeground(new java.awt.Color(255, 255, 255));
    inTempLabel.setText("Val");

    javax.swing.GroupLayout temperaturePanelLayout = new javax.swing.GroupLayout(temperaturePanel);
    temperaturePanel.setLayout(temperaturePanelLayout);
    temperaturePanelLayout.setHorizontalGroup(
        temperaturePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
        .addGroup(javax.swing.GroupLayout.Alignment.LEADING, temperaturePanelLayout.createSequentialGroup()
            .addComponent(TemperatureLabel)
            .addGap(0, 0, Short.MAX_VALUE))
        .addGroup(temperaturePanelLayout.createSequentialGroup()
            .addContainerGap()
            .addGroup(temperaturePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                .addComponent(temperatureGraph, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addGroup(javax.swing.GroupLayout.Alignment.LEADING, temperaturePanelLayout.createSequentialGroup()
                    .addComponent(INLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 39, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(38, 38, 38)
                    .addComponent(inTempLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 84, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(degC, javax.swing.GroupLayout.PREFERRED_SIZE, 31, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(186, 186, 186)
                    .addComponent(OUTLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 64, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(36, 36, 36)
                    .addComponent(outTempLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 72, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(35, 35, 35)
                    .addComponent(degC1, javax.swing.GroupLayout.PREFERRED_SIZE, 36, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addGap(0, 138, Short.MAX_VALUE))
                .addGroup(temperaturePanelLayout.createSequentialGroup()
                    .addComponent(inThermometer, javax.swing.GroupLayout.PREFERRED_SIZE, 378, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(outThermometer, javax.swing.GroupLayout.PREFERRED_SIZE, 352, javax.swing.GroupLayout.PREFERRED_SIZE)))
            .addContainerGap())
    );
    temperaturePanelLayout.setVerticalGroup(
        temperaturePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, temperaturePanelLayout.createSequentialGroup()
            .addGroup(temperaturePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                .addGroup(temperaturePanelLayout.createSequentialGroup()
                    .addGap(0, 0, Short.MAX_VALUE)
                    .addComponent(outThermometer, javax.swing.GroupLayout.PREFERRED_SIZE, 327, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGroup(temperaturePanelLayout.createSequentialGroup()
                    .addComponent(TemperatureLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 32, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(temperatureGraph, javax.swing.GroupLayout.PREFERRED_SIZE, 260, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                    .addGroup(temperaturePanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(INLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                        .addComponent(inTempLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 29, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(degC, javax.swing.GroupLayout.PREFERRED_SIZE, 29, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(OUTLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 29, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(outTempLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 32, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addComponent(degC1, javax.swing.GroupLayout.PREFERRED_SIZE, 34, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                    .addComponent(inThermometer, javax.swing.GroupLayout.PREFERRED_SIZE, 327, javax.swing.GroupLayout.PREFERRED_SIZE)))
            .addGap(44, 44, 44))
    );

    getContentPane().add(temperaturePanel, new org.netbeans.lib.awtextra.AbsoluteConstraints(570, 720, 800, 710));

    imuPanel.setBackground(new java.awt.Color(102, 102, 102));
    imuPanel.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));

    roll.setBackground(new java.awt.Color(102, 102, 102));

    javax.swing.GroupLayout rollLayout = new javax.swing.GroupLayout(roll);
    roll.setLayout(rollLayout);
    rollLayout.setHorizontalGroup(
        rollLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGap(0, 302, Short.MAX_VALUE)
    );
    rollLayout.setVerticalGroup(
        rollLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGap(0, 308, Short.MAX_VALUE)
    );

    pitch.setBackground(new java.awt.Color(102, 102, 102));

    javax.swing.GroupLayout pitchLayout = new javax.swing.GroupLayout(pitch);
    pitch.setLayout(pitchLayout);
    pitchLayout.setHorizontalGroup(
        pitchLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGap(0, 0, Short.MAX_VALUE)
    );
    pitchLayout.setVerticalGroup(
        pitchLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGap(0, 257, Short.MAX_VALUE)
    );

    yaw.setBackground(new java.awt.Color(102, 102, 102));

    javax.swing.GroupLayout yawLayout = new javax.swing.GroupLayout(yaw);
    yaw.setLayout(yawLayout);
    yawLayout.setHorizontalGroup(
        yawLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGap(0, 189, Short.MAX_VALUE)
    );
    yawLayout.setVerticalGroup(
        yawLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGap(0, 182, Short.MAX_VALUE)
    );

    IMUDataLabel.setFont(new java.awt.Font("Tahoma", 1, 36)); // NOI18N
    IMUDataLabel.setForeground(new java.awt.Color(255, 255, 255));
    IMUDataLabel.setText("IMU Data");

    jLabel1.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    jLabel1.setForeground(new java.awt.Color(255, 255, 255));
    jLabel1.setText("Roll");

    jLabel2.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    jLabel2.setForeground(new java.awt.Color(255, 255, 255));
    jLabel2.setText("Pitch");

    jLabel3.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    jLabel3.setForeground(new java.awt.Color(255, 255, 255));
    jLabel3.setText("Yaw");

    rollLabel.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    rollLabel.setForeground(new java.awt.Color(255, 255, 255));
    rollLabel.setText("Value");

    pitchLabel.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    pitchLabel.setForeground(new java.awt.Color(255, 255, 255));
    pitchLabel.setText("Value");

    yawLabel.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    yawLabel.setForeground(new java.awt.Color(255, 255, 255));
    yawLabel.setText("Value");

    javax.swing.GroupLayout imuPanelLayout = new javax.swing.GroupLayout(imuPanel);
    imuPanel.setLayout(imuPanelLayout);
    imuPanelLayout.setHorizontalGroup(
        imuPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(imuPanelLayout.createSequentialGroup()
            .addGroup(imuPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addComponent(IMUDataLabel)
                .addGroup(imuPanelLayout.createSequentialGroup()
                    .addContainerGap()
                    .addGroup(imuPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addComponent(jLabel1)
                        .addComponent(jLabel2)
                        .addComponent(jLabel3))
                    .addGap(25, 25, 25)
                    .addGroup(imuPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addComponent(yawLabel)
                        .addComponent(pitchLabel)
                        .addComponent(rollLabel))))
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 8, Short.MAX_VALUE)
            .addComponent(rollpitchGraph, javax.swing.GroupLayout.PREFERRED_SIZE, 582, javax.swing.GroupLayout.PREFERRED_SIZE)
            .addContainerGap())
        .addGroup(imuPanelLayout.createSequentialGroup()
            .addGap(2, 2, 2)
            .addComponent(roll, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(pitch, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addGap(18, 18, 18)
            .addComponent(yaw, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
    );
    imuPanelLayout.setVerticalGroup(
        imuPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(imuPanelLayout.createSequentialGroup()
            .addGroup(imuPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(imuPanelLayout.createSequentialGroup()
                    .addComponent(rollpitchGraph, javax.swing.GroupLayout.PREFERRED_SIZE, 495, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addGroup(imuPanelLayout.createSequentialGroup()
                    .addComponent(IMUDataLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 31, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addGroup(imuPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(rollLabel)
                        .addComponent(jLabel1))
                    .addGap(62, 62, 62)
                    .addGroup(imuPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(pitchLabel)
                        .addComponent(jLabel2))
                    .addGap(72, 72, 72)
                    .addGroup(imuPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(jLabel3)
                        .addComponent(yawLabel))
                    .addGap(194, 194, 194)))
            .addGroup(imuPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addComponent(roll, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addComponent(pitch, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addComponent(yaw, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
    );

    getContentPane().add(imuPanel, new org.netbeans.lib.awtextra.AbsoluteConstraints(1380, 0, 780, 810));

    gpsPanel.setBackground(new java.awt.Color(102, 102, 102));
    gpsPanel.setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));

    GPSDataLabel.setFont(new java.awt.Font("Tahoma", 1, 36)); // NOI18N
    GPSDataLabel.setForeground(new java.awt.Color(255, 255, 255));
    GPSDataLabel.setText("Accelerometer Data");

    jLabel4.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    jLabel4.setForeground(new java.awt.Color(255, 255, 255));
    jLabel4.setText("Angle of Descent");

    jLabel6.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    jLabel6.setForeground(new java.awt.Color(255, 255, 255));
    jLabel6.setText("Distance from Start");

    latitudeLabel.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    latitudeLabel.setForeground(new java.awt.Color(255, 255, 255));
    latitudeLabel.setText("Value");

    altitudeLabel1.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    altitudeLabel1.setForeground(new java.awt.Color(255, 255, 255));
    altitudeLabel1.setText("Value");

    jPanel1 = new javax.swing.JPanel(){
        @Override
        protected void paintComponent(Graphics g){
            super.paintComponent(g);
            g2d=(Graphics2D)g; // Create a Java2D version of g.
            //g2d.translate(150, 50); // Translate the center of our coordinates.
            g.drawImage(srmlogoImg, 0, 0, jPanel1.getHeight(), jPanel1.getWidth(), this);

        }
    };

    javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
    jPanel1.setLayout(jPanel1Layout);
    jPanel1Layout.setHorizontalGroup(
        jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGap(0, 414, Short.MAX_VALUE)
    );
    jPanel1Layout.setVerticalGroup(
        jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGap(0, 413, Short.MAX_VALUE)
    );

    jLabel20.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    jLabel20.setForeground(new java.awt.Color(255, 255, 255));
    jLabel20.setText("Acc X");

    jLabel21.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    jLabel21.setForeground(new java.awt.Color(255, 255, 255));
    jLabel21.setText("Acc Y");

    jLabel22.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    jLabel22.setForeground(new java.awt.Color(255, 255, 255));
    jLabel22.setText("Acc Z");

    acczLabel1.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    acczLabel1.setForeground(new java.awt.Color(255, 255, 255));
    acczLabel1.setText("Value");

    accyLabel1.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    accyLabel1.setForeground(new java.awt.Color(255, 255, 255));
    accyLabel1.setText("Value");

    accxLabel1.setFont(new java.awt.Font("Tahoma", 1, 24)); // NOI18N
    accxLabel1.setForeground(new java.awt.Color(255, 255, 255));
    accxLabel1.setText("Value");

    javax.swing.GroupLayout gpsPanelLayout = new javax.swing.GroupLayout(gpsPanel);
    gpsPanel.setLayout(gpsPanelLayout);
    gpsPanelLayout.setHorizontalGroup(
        gpsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(gpsPanelLayout.createSequentialGroup()
            .addContainerGap()
            .addGroup(gpsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(gpsPanelLayout.createSequentialGroup()
                    .addComponent(GPSDataLabel)
                    .addGap(0, 0, Short.MAX_VALUE))
                .addGroup(gpsPanelLayout.createSequentialGroup()
                    .addGap(2, 2, 2)
                    .addGroup(gpsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(gpsPanelLayout.createSequentialGroup()
                            .addComponent(jLabel6)
                            .addGap(18, 18, 18)
                            .addComponent(altitudeLabel1))
                        .addGroup(gpsPanelLayout.createSequentialGroup()
                            .addComponent(jLabel4)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 64, Short.MAX_VALUE)
                            .addComponent(latitudeLabel)
                            .addGap(1, 1, 1))
                        .addGroup(gpsPanelLayout.createSequentialGroup()
                            .addGroup(gpsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                .addComponent(jLabel22)
                                .addComponent(jLabel20)
                                .addComponent(jLabel21))
                            .addGap(26, 26, 26)
                            .addGroup(gpsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                .addComponent(accxLabel1)
                                .addComponent(acczLabel1)
                                .addComponent(accyLabel1))
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 160, javax.swing.GroupLayout.PREFERRED_SIZE)))
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                    .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)))
            .addContainerGap())
    );
    gpsPanelLayout.setVerticalGroup(
        gpsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
        .addGroup(gpsPanelLayout.createSequentialGroup()
            .addContainerGap()
            .addComponent(GPSDataLabel, javax.swing.GroupLayout.PREFERRED_SIZE, 43, javax.swing.GroupLayout.PREFERRED_SIZE)
            .addGroup(gpsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                .addGroup(gpsPanelLayout.createSequentialGroup()
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 140, Short.MAX_VALUE)
                    .addComponent(jPanel1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addContainerGap())
                .addGroup(gpsPanelLayout.createSequentialGroup()
                    .addGap(26, 26, 26)
                    .addGroup(gpsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                        .addComponent(jLabel6)
                        .addComponent(altitudeLabel1))
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                    .addGroup(gpsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addGroup(gpsPanelLayout.createSequentialGroup()
                            .addComponent(accxLabel1)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(accyLabel1)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(acczLabel1))
                        .addGroup(gpsPanelLayout.createSequentialGroup()
                            .addComponent(jLabel20)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(jLabel21)
                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                            .addComponent(jLabel22)))
                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                    .addGroup(gpsPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                        .addComponent(latitudeLabel)
                        .addComponent(jLabel4))
                    .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))
    );

    getContentPane().add(gpsPanel, new org.netbeans.lib.awtextra.AbsoluteConstraints(1380, 810, 780, 630));

    jLabel24.setFont(new java.awt.Font("Tahoma", 0, 36)); // NOI18N
    jLabel24.setText("TEAM ID 2531 - WELKINSAT - Ground Station");
    getContentPane().add(jLabel24, new org.netbeans.lib.awtextra.AbsoluteConstraints(600, 10, 740, 80));

    pack();
    }// </editor-fold>                        

    private void connectButtonActionPerformed(java.awt.event.ActionEvent evt) {                                              
        portList = CommPortIdentifier.getPortIdentifiers();

        while (portList.hasMoreElements()) {
            portId = (CommPortIdentifier) portList.nextElement();
            if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
                jComboBox1.addItem(portId.getName());
            }
        }
        statusLabel.setText("Waiting for port..");
    }                                             

    private void disconnectButtonActionPerformed(java.awt.event.ActionEvent evt) {                                                 
        if (serialPort != null) {
            serialPort.removeEventListener();
            serialPort.close();
            flag=0;
            statusLabel.setText("Not Connected");
        }
        try
        {
        f_out.close();
        }
        catch(Exception e)
        {
            System.out.println(e);
        }
        
    }                                                

    private void resetButtonActionPerformed(java.awt.event.ActionEvent evt) {                                            
       S_hour = Calendar.getInstance().get(Calendar.HOUR);
            S_minute = Calendar.getInstance().get(Calendar.MINUTE);
            S_seconds = Calendar.getInstance().get(Calendar.SECOND);
            S_millis = Calendar.getInstance().get(Calendar.MILLISECOND);
            launchtimeLabel.setText(S_hour+":"+S_minute+":"+S_seconds+"."+S_millis);
            flag=1;
       launchtimeLabel.setText(S_hour+":"+S_minute+":"+S_seconds+"."+S_millis);
       //elapsedtimeLabel.setText("HH:MM:SS");
       altitudeLabel.setText("Value");
       altitudeLabel1.setText("Value");
       altitudeLabel2.setText("Value");
       inTempLabel.setText("Val");
       inTempLabel1.setText("Value");
       outTempLabel.setText("Val");
       outTempLabel1.setText("Value");
       rollLabel.setText("Value");
       pitchLabel.setText("Value");
       yawLabel.setText("Value");
       rollLabel1.setText("Value");
       pitchLabel1.setText("Value");
       
       Altitudedataset.clear();
       Temperaturedataset.clear();
       rollpitchdataset.clear();
       Roll=0;
       Pitch=0;
       Yaw=0;
       roll.repaint();
       pitch.repaint();
       yaw.repaint();

       dataset_inT.setValue(0);
       dataset_outT.setValue(0);
       
       Date date = new Date();
        SimpleDateFormat ft = new SimpleDateFormat ("dd_MM_yyyy_hh_mm_ss");
        file_name = ft.format(date)+".csv";
        try
        {
        f_out.close();
        f_out = new FileOutputStream(file_dir+file_name);
        
        }
        catch(Exception e)
        {
            System.out.println(e);
        }
    }                                           

    private void jComboBox1ActionPerformed(java.awt.event.ActionEvent evt) {                                           
        ComPort = jComboBox1.getSelectedItem().toString();
        comportLabel.setText(ComPort);
        portList = CommPortIdentifier.getPortIdentifiers();
        while (portList.hasMoreElements()) {
            portId = (CommPortIdentifier) portList.nextElement();
            if (portId.getPortType() == CommPortIdentifier.PORT_SERIAL) {
                if (portId.getName().equals(ComPort)) {
                    break;
                }
            }
        }
        //System.out.println(portId.getName() + "");
        try {
            // open serial port, and use class name for the appName.
            serialPort = (SerialPort) portId.open(this.getClass().getName(),
                    TIME_OUT);

            // set port parameters
            serialPort.setSerialPortParams(BAUD_RATE, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);

            // open the streams
            input = new BufferedReader(new InputStreamReader(serialPort.getInputStream()));
            output = serialPort.getOutputStream();

            // add event listeners
            serialPort.addEventListener(this);
            serialPort.notifyOnDataAvailable(true);

            
            S_hour = Calendar.getInstance().get(Calendar.HOUR);
            S_minute = Calendar.getInstance().get(Calendar.MINUTE);
            S_seconds = Calendar.getInstance().get(Calendar.SECOND);
            S_millis = Calendar.getInstance().get(Calendar.MILLISECOND);
            launchtimeLabel.setText(S_hour+":"+S_minute+":"+S_seconds+"."+S_millis);
            flag=1;
            statusLabel.setText("Connected..");
        } catch (Exception e) {
            System.err.println(e.toString());
        }
        //portId = (CommPortIdentifier) ComPort;
        Date date = new Date();
        SimpleDateFormat ft = new SimpleDateFormat ("dd_MM_yyyy_hh_mm_ss");
        file_name = ft.format(date)+".csv";
        try
        {
        f_out = new FileOutputStream(file_dir+file_name);
        }
        catch(Exception e)
        {
            System.out.println(e);
        }
    }                                          

    private void SaveCSVActionPerformed(java.awt.event.ActionEvent evt) {                                        
    try{
        f_out.close();
    }
    catch(Exception e)
    {
        System.out.println(e);
    }
               // TODO add your handling code here:
    }                                       

    private void CreateCSVActionPerformed(java.awt.event.ActionEvent evt) {                                          
        Date date = new Date();
        SimpleDateFormat ft = new SimpleDateFormat ("dd_MM_yyyy_hh_mm_ss");
        file_name = ft.format(date)+".csv";
        try
        {
        f_out = new FileOutputStream(file_dir+file_name);
        }
        catch(Exception e)
        {
            System.out.println(e);
        }
    }                                         

    public static void main(String args[]) 
    {
        //-----------------------------------
        System.out.println(screenWidth+" "+screenHeight);
        //-----------------------------------
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    new CANSAT_2015().setVisible(true);
                    
                } catch (IOException ex) {
                    Logger.getLogger(CANSAT_2015.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        });
        LineChart_AWT chart = new LineChart_AWT("","");
        //System.out.println(imuPanel.getBounds());
        new update_GUI();
    }

    // Variables declaration - do not modify                     
    private static javax.swing.JLabel Altitude;
    private static javax.swing.JLabel Altitude1;
    public static javax.swing.JLabel BatteryLabel;
    public javax.swing.JButton CreateCSV;
    public static javax.swing.JLabel FSWLabel;
    private javax.swing.JLabel GPSDataLabel;
    private javax.swing.JLabel IMUDataLabel;
    private javax.swing.JLabel INLabel;
    private javax.swing.JLabel OUTLabel;
    public static javax.swing.JLabel PressureLabel;
    public javax.swing.JButton SaveCSV;
    private javax.swing.JLabel TemperatureLabel;
    private static javax.swing.JLabel accxLabel;
    private static javax.swing.JLabel accxLabel1;
    private static javax.swing.JLabel accyLabel;
    private static javax.swing.JLabel accyLabel1;
    private static javax.swing.JLabel acczLabel;
    private static javax.swing.JLabel acczLabel1;
    private static javax.swing.JPanel altitudeGraph;
    private static javax.swing.JLabel altitudeLabel;
    private static javax.swing.JLabel altitudeLabel1;
    private static javax.swing.JLabel altitudeLabel2;
    private javax.swing.JPanel altitudePanel;
    private static javax.swing.JLabel comportLabel;
    private javax.swing.JButton connectButton;
    private javax.swing.JPanel connectionPanel;
    private javax.swing.JPanel dataPanel;
    private javax.swing.JLabel degC;
    private javax.swing.JLabel degC1;
    private static javax.swing.JLabel descentrateLabel;
    private static javax.swing.JLabel descentrateLabel1;
    private javax.swing.JButton disconnectButton;
    private static javax.swing.JLabel elapsedtimeLabel;
    private javax.swing.JPanel gpsPanel;
    private static javax.swing.JPanel imuPanel;
    private static javax.swing.JLabel inTempLabel;
    private static javax.swing.JLabel inTempLabel1;
    private static javax.swing.JPanel inThermometer;
    private javax.swing.JComboBox jComboBox1;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel10;
    private javax.swing.JLabel jLabel11;
    private javax.swing.JLabel jLabel12;
    private javax.swing.JLabel jLabel13;
    private javax.swing.JLabel jLabel14;
    private javax.swing.JLabel jLabel15;
    private javax.swing.JLabel jLabel16;
    private javax.swing.JLabel jLabel17;
    private javax.swing.JLabel jLabel18;
    private javax.swing.JLabel jLabel19;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel20;
    private javax.swing.JLabel jLabel21;
    private javax.swing.JLabel jLabel22;
    private javax.swing.JLabel jLabel23;
    private javax.swing.JLabel jLabel24;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel6;
    private javax.swing.JLabel jLabel7;
    private javax.swing.JLabel jLabel8;
    private javax.swing.JLabel jLabel9;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JLabel latitudeLabel;
    private static javax.swing.JLabel launchtimeLabel;
    private javax.swing.JLabel mLabel;
    private javax.swing.JLabel mLabel1;
    private static javax.swing.JLabel outTempLabel;
    private static javax.swing.JLabel outTempLabel1;
    private static javax.swing.JPanel outThermometer;
    private static javax.swing.JPanel pitch;
    private static javax.swing.JLabel pitchLabel;
    private static javax.swing.JLabel pitchLabel1;
    private javax.swing.JLabel realtimedata;
    private static javax.swing.JTextArea realtimedataTextArea;
    private static javax.swing.JTextField realtimedataTextField;
    private javax.swing.JButton resetButton;
    private static javax.swing.JPanel roll;
    private static javax.swing.JLabel rollLabel;
    private static javax.swing.JLabel rollLabel1;
    private static javax.swing.JPanel rollpitchGraph;
    private javax.swing.JLabel serialCommLabel;
    private static javax.swing.JLabel statusLabel;
    private static javax.swing.JPanel temperatureGraph;
    private javax.swing.JPanel temperaturePanel;
    private static javax.swing.JPanel yaw;
    private static javax.swing.JLabel yawLabel;
    // End of variables declaration                   
public  void create_AltitudeChart()
{
    
   AltitudelineChart = ChartFactory.createLineChart( "",
         "","",
         createAltitudeDataset(),
         PlotOrientation.VERTICAL,
         true,true,false);
         
      AltitudechartPanel = new ChartPanel(AltitudelineChart); 
      AltitudechartPanel.setPreferredSize(altitudeGraph.getSize());
      altitudeGraph.add(AltitudechartPanel); 
        altitudeGraph.setVisible(true);
}
public  void create_TemperatureChart()
{
   TemperaturelineChart = ChartFactory.createLineChart( "",
         "","",
         createTemperatureDataset(),
         PlotOrientation.VERTICAL,
         true,true,false);
         
      TemperaturechartPanel = new ChartPanel(TemperaturelineChart); 
      TemperaturechartPanel.setPreferredSize(temperatureGraph.getSize());
      temperatureGraph.add(TemperaturechartPanel); 
        temperatureGraph.setVisible(true);
}
public  void create_rollpitchChart()
{
   rollpitchlineChart = ChartFactory.createLineChart( "",
         "","",
         createrollpitchDataset(),
         PlotOrientation.VERTICAL,
         true,true,false);
         
      rollpitchchartPanel = new ChartPanel(rollpitchlineChart); 
      rollpitchchartPanel.setPreferredSize(rollpitchGraph.getSize());
      rollpitchGraph.add(rollpitchchartPanel); 
        rollpitchGraph.setVisible(true);
}
   static CategoryDataset createAltitudeDataset( )
   {
    
      //dataset.addValue( (Number)chart_data , "Rand" , val++);
      Altitudedataset.addValue( (Number)altitudeVal , "Altitude" , (int) System.currentTimeMillis() - startTime );
      //Altitudedataset.removeColumn();
      return Altitudedataset; 
   }
   static CategoryDataset createTemperatureDataset( )
   {
       int a=10;
      //dataset.addValue( (Number)chart_data , "Rand" , val++);
       int time = (int)System.currentTimeMillis() - startTime;
      Temperaturedataset.addValue( (Number)IN_temp, "IN_Temperature" , time);
      Temperaturedataset.addValue( (Number)OUT_temp, "OUT_Temperature" , time);
      return Temperaturedataset; 
   }
   static CategoryDataset createrollpitchDataset( )
   {
       int a=10;
      //dataset.addValue( (Number)chart_data , "Rand" , val++);
      int time = (int)System.currentTimeMillis() - startTime;
      rollpitchdataset.addValue( (Number)Roll, "Roll" , time);
      rollpitchdataset.addValue( (Number)Pitch, "Pitch" , time);
      return rollpitchdataset; 
   }
   public static int randInt() {
       int max=100, min=0;
    Random rand = new Random();
    int randomNum = rand.nextInt((max - min) + 1) + min;
    return randomNum;
    }
   public static void create_inThermometer()
{
    
    //-----------IN-TEMPERATURE---------
     dataset_inT.setValue(IN_temp);
ThermometerPlot plot = new ThermometerPlot(dataset_inT);
JFreeChart chart = new JFreeChart("IN Temperature",  // chart title
                                        JFreeChart.DEFAULT_TITLE_FONT,
                                        plot,                  // plot
                                        false);                // include legend

chart.setBackgroundPaint(new Color(241,250,224));
inThermometerPanel= new ChartPanel(chart);
//plot.setMercuryPaint();
//final NumberAxis rangeAxis = (NumberAxis) plot.getRangeAxis();
//rangeAxis.setUpperBound(50);
inThermometerPanel.setPreferredSize(inThermometer.getSize());
inThermometer.add(inThermometerPanel); 
inThermometer.setVisible(true);
}
   public static void create_outThermometer(){
//--------OUT-TEMPERATURE---------
dataset_outT.setValue(OUT_temp);
ThermometerPlot plot1 = new ThermometerPlot(dataset_outT);
JFreeChart chart1 = new JFreeChart("OUT Temperature",  // chart title
                                        JFreeChart.DEFAULT_TITLE_FONT,
                                        plot1,                  // plot
                                        false);                // include legend

chart1.setBackgroundPaint(new Color(241,250,224));
outThermometerPanel= new ChartPanel(chart1);
//plot.setMercuryPaint();
//final NumberAxis rangeAxis = (NumberAxis) plot.getRangeAxis();
//rangeAxis.setUpperBound(50);
outThermometerPanel.setPreferredSize(outThermometer.getSize());
outThermometer.add(outThermometerPanel); 
outThermometer.setVisible(true);

}
   public static void update_Values()
   {
       
       //altitudeVal=randInt();
       descentRate=randInt();
       {
           int count=0;
       //IN_temp=inTempMat[count];
       //OUT_temp=outTempMat[count++];
       count++;
       //IN_temp=randInt();
       //OUT_temp=randInt();
       if(count==15) count=0;
       }
       //Roll=randInt();
       //Pitch=randInt();
       //Yaw=randInt();
       //Acc_X=randInt();
       //Acc_Y=randInt();
       //Acc_Z=randInt();
       System.out.println("Updating values");
       altitudeLabel.setText(Double.toString(altitudeVal));
       altitudeLabel1.setText(Double.toString(altitudeVal));
       altitudeLabel2.setText(Double.toString(altitudeVal));
       inTempLabel.setText(Double.toString(IN_temp));
       inTempLabel1.setText(Double.toString(IN_temp));
       outTempLabel.setText(Double.toString(OUT_temp));
       outTempLabel1.setText(Double.toString(OUT_temp));
       rollLabel.setText(Double.toString(Roll));
       pitchLabel.setText(Double.toString(Pitch));
       yawLabel.setText(Double.toString(Yaw));
       rollLabel1.setText(Double.toString(Roll));
       pitchLabel1.setText(Double.toString(Pitch));
       //realtimedataTextField.setText(Integer.toString(altitudeVal)+","+Integer.toString(IN_temp)+","+Integer.toString(Roll)+","+Integer.toString(Pitch)+","+Integer.toString(Yaw));
       //realtimedataTextArea.append(Integer.toString(altitudeVal)+","+Integer.toString(IN_temp)+","+Integer.toString(Roll)+","+Integer.toString(Pitch)+","+Integer.toString(Yaw)+"\n");
   }
static int serial_flag=0;
    @Override
    public void serialEvent(SerialPortEvent Event) {
        try {
            if (Event.getEventType() == SerialPortEvent.DATA_AVAILABLE) {
                try {
                    int[] comma = new int[20];
                    String[] data = new String[20];
                    String inputLine = input.readLine();
                    //chart_data = Double.parseDouble(inputLine);
                    realtimedataTextField.setText(inputLine);
                    realtimedataTextArea.append(inputLine+"\n");
                    
                    try{
                        int count_file = inputLine.length();
                        int j=0;
                        for(int i=0; i<count_file; i++)
                        {
                        j=inputLine.charAt(i);
                        f_out.write(j);
                        }
                        f_out.write('\n');
                        //System.out.println("File Write Successful");
                    }
                    catch(Exception e)
                    {
                        //System.out.println("file error");
                        System.out.println(e);
                    }
                    serial_flag=1;
                    //System.out.println(inputLine);
                    //0-Team Id
                    //1-Pack Count
                    //2-Mission Time
                    //3-Alt
                    //4-Temp
                    //5-Roll
                    //6-Pitch
                    //7-Yaw
                    //8-Press
                    //9-Climb
                    //inputLine+='x';
                    System.out.println(inputLine);
                    int count = inputLine.length();
                    //System.out.println(count);
                    System.out.println(count);
                    for(int i=0,j=0; i<count-1; i++)
                    {
                        if(inputLine.charAt(i)==',')
                        {comma[j++]=i;
                        System.out.println(i);
                        }
                    }
                    //System.out.println("data sep succ");
                    int packets=15;//number of packets.. not the index number
                    data[0]=inputLine.substring(0,comma[0]);
                    //System.out.println(data[0]);
                    for(int i=1;i<(packets-1);i++)
                    {
                    data[i]=inputLine.substring(comma[i-1]+1,comma[i]);
                    //System.out.println(data[i]);
                    }
                    data[packets-1]=inputLine.substring(comma[packets-2]+1);
                    //System.out.println(data[14]);
                    //System.out.println("data impll succ");
                    for(int i=0; i<9; i++)
                    {
                        //System.out.println("Data"+i+data[i]);
                    }
                    //Team Id 1
                    altitudeVal=Double.valueOf(data[2])/100;
                    double demo = pow((1-(Double.valueOf(data[2])/(double)4433000)),(double)5.255)*(double)101325;
                    PressureLabel.setText(String.valueOf(demo));
                    IN_temp=Double.valueOf(data[3])/100;
                    OUT_temp=Double.valueOf(data[4])/100;//-373;
                    BatteryLabel.setText("8.8");//Double.valueOf(data[5]).toString());
                    FSWLabel.setText(Double.valueOf(data[6]).toString());
                    double demo_val = Double.valueOf(data[7])/100;
                    accxLabel.setText(String.valueOf(demo_val));
                    accxLabel1.setText(String.valueOf(demo_val));
                    demo_val = Double.valueOf(data[8])/100;
                    accyLabel.setText(String.valueOf(demo_val));
                    accyLabel1.setText(String.valueOf(demo_val));
                    demo_val = Double.valueOf(data[9])/100;
                    acczLabel.setText(String.valueOf(demo_val));
                    acczLabel1.setText(String.valueOf(demo_val));
                    //accxLabel1.setText(Double.valueOf(data[7]).toString());
                    //accyLabel1.setText(Double.valueOf(data[8]).toString());
                    //acczLabel1.setText(Double.valueOf(data[9]).toString());
                    //packet count 10
                    Roll=Double.valueOf(data[11]);
                    Pitch=Double.valueOf(data[12]);
                    Yaw=Double.valueOf(data[13]);
                    descentrateLabel.setText(Double.valueOf(data[14]).toString());
                    descentrateLabel1.setText(Double.valueOf(data[14]).toString());
                    //jPanel7.setSize(20, height);
                    /*
                    String add_line = "";
                    add_line = "2531"+data[1].toString()+","+Double.toString(Double.valueOf(data[2])/100)+","+Double.toString(Double.valueOf(data[3])/100)+","+Double.toString(Double.valueOf(data[4])/100)+",8.8,"+Double.valueOf(data[6]).toString()+","+Double.valueOf(data[7]).toString()+","+Double.valueOf(data[8]).toString()+","+Double.valueOf(data[9]).toString()+","+data[10].toString()+","+data[11]+","+data[12]+","+data[13]+","+data[14];
                    try{
                        int count_file = add_line.length();
                        int j=0;
                        for(int i=0; i<count_file; i++)
                        {
                        j=inputLine.charAt(i);
                        add_f_out.write(j);
                        }
                        add_f_out.write('\n');
                        //System.out.println("File Write Successful");
                    }
                    catch(Exception e)
                    {
                        //System.out.println("file error");
                        System.out.println(e);
                    }
                    */
                } catch (Exception e) {
                    System.out.println("data error");
                    System.err.println(e.toString());
                }
                finally
                {
                    
                }
            }
            else    serial_flag=0;
        } catch (Exception e) {

        }
        finally
                {
                    E_hour = Calendar.getInstance().get(Calendar.HOUR);
                    E_minute = Calendar.getInstance().get(Calendar.MINUTE);
                    E_seconds = Calendar.getInstance().get(Calendar.SECOND);
                    //E_millis = Calendar.getInstance().get(Calendar.MILLISECOND);
                    elapsedtimeLabel.setText((E_hour-S_hour)+":"+(E_minute-S_minute)+":"+(E_seconds-S_seconds));
                }
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    
    }
   static class update_GUI implements Runnable{
        update_GUI()
        {
            Thread t = new Thread(this);
            t.start();
        }
        @Override
        public void run() 
        {
            while(true)
            {
                System.out.println();
                
                if(flag==1)
                {
                try{                 
            Thread.sleep(delayTime);
             }
             catch(Exception e)
             {
                 System.out.println(e);
             }
                
                
                clear_count++;
                update_Values();
                /*
                if(clear_count>100)
                {
                    Altitudedataset.clear();
                    //Altitudedataset.removeRow(clear_count-100);
                    Temperaturedataset.clear();
                    //Temperaturedataset.removeRow(clear_count-100);
                    rollpitchdataset.clear();
                    //Temperaturedataset.removeRow(clear_count-100);
                    clear_count=0;
                }
                */
                clear_count=0;
                if(serial_flag==1)
                {
                    System.out.println("Repainting");
             createAltitudeDataset();
             createTemperatureDataset();
             create_inThermometer();
             create_outThermometer();
             createrollpitchDataset();
             roll.repaint();
             pitch.repaint();
             yaw.repaint();
                }
                }
             
             
            
            }            
        }
   }
//-----------------UNWANTED BITCH!! DUNNO Y!!!--------------------------------------


static class LineChart_AWT extends ApplicationFrame
{
    static int data;
    static DefaultCategoryDataset dataset;
    
   public LineChart_AWT( String applicationTitle , String chartTitle )
   {
       
      super(applicationTitle);
      JFreeChart lineChart = ChartFactory.createLineChart( chartTitle,
         "Years","Number of Schools",
         createDataset(),
         PlotOrientation.VERTICAL,
         true,true,false);
         
      ChartPanel chartPanel = new ChartPanel( lineChart );
      chartPanel.setPreferredSize( new java.awt.Dimension( 100 , 100 ) );
      setContentPane( chartPanel );
   }

   private static CategoryDataset createDataset( )
   {
      dataset = new DefaultCategoryDataset();
      dataset.addValue( 15 , "schools" , "1970" );
      dataset.addValue( 30 , "schools" , "1980" );
      dataset.addValue( 60 , "schools" ,  "1990" );
      dataset.addValue( 120 , "schools" , "2000" );
      dataset.addValue( 240 , "schools" , "2010" );
      dataset.addValue( 300 , "schools" , "2014" );
      return dataset;
   }
   
   static class data implements Runnable
   {
        data()
        {
            Thread t = new Thread();
            t.start();
        }
        @Override
        public void run() 
        {
            
            while(true)
            {
             try{
                 
          
            Thread.sleep(500);
             }
             catch(Exception e)
             {
                 System.out.println(e);
             }
            }            
        }
       
   }
   public static int randInt(int min, int max) {
    Random rand = new Random();
    int randomNum = rand.nextInt((max - min) + 1) + min;
    return randomNum;
    }
}
}
