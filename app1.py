from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QSplitter,  QAction, QFormLayout,  QInputDialog, QMessageBox, QPushButton,  QGroupBox,  QCheckBox,  QLineEdit,  QFrame,  QDial)
from PyQt5.QtGui import QIcon, QColor,  QPalette,  QImage,  QPixmap
import os
import serial
from PyQt5.QtCore import Qt,  QRect,  pyqtSignal,  QSignalMapper
import sys
import time
portList=['COM'+str(i) for i in range(1, 4+1)]
serialSpeedCases=['9600', '14400', '38400', '57600', '115200']
class Window (QMainWindow):
    def __init__(self):
        super().__init__()
        self.statusbar =  self.statusBar()
        self.cont =  Content(self)
        #self.cont.ms[str].connect(self.statusBar().showMessage)
        #self.statusBar().showMessage("qqqqqqqqqqq")
        self.setCentralWidget(self.cont)
        self.setBackground()
        self.center()
        
        self.setWindowTitle('Navigare')
        self.setWindowIcon(QIcon('icon.jpg'))
        
        self.show()
    def setBackground(self):
        pal =  QPalette()
        pal.setColor(QPalette.Background,  Qt.white)
        self.setAutoFillBackground(True)
        self.setPalette(pal)        
    def center(self):
        screen =  QDesktopWidget().screenGeometry()
        self.resize(screen.width()/ 4,  screen.height() / 4)
        size =  self.geometry()
        x =  (screen.width() - size.width()) / 2
        y = (screen.height() - size.height()) / 2
        self.move(x,  y)        
class Content(QWidget):
    #ms =  pyqtSignal(str)
    windows =  [False] * 5
    #windows[0] = True
    def __init__(self,  parent):
        super().__init__(parent)
        self.create()
    def create(self):
        self.mainBox =  QVBoxLayout(self)
        
        self.hor1Box =  QHBoxLayout()
        
        self.controlSplitter =  QSplitter(Qt.Horizontal)
        self.control =  Control()
        self.controlSplitter.addWidget(self.control)
        self.control.changeWindSignal[int].connect(self.changeWindows)
        
        if self.windows[0] ==  True:
            self.camera =  Camera()
            print("eef")
            self.controlSplitter.addWidget(self.camera)
            
        
        self.hor1Box.addWidget(self.controlSplitter)
        print(self.windows)
        
        self.mainBox.addWidget(self.controlSplitter)
        self.mainBox.addStretch(1)
        self.setLayout(self.mainBox)        
    def sendMessage(self,  m):
        self.msg.emit('Hi')
    def changeWindows(self,  i):
        print(i)
        self.windows[i] =   not self.windows[i]
        self.create()
        self.update()
class Control(QFrame):
    changeWindSignal =  pyqtSignal(int)
    global portList
    global serialSpeedCases
    def __init__(self):
        super().__init__()
        self.setFrameShape(QFrame.StyledPanel)
        #self.msg.emit('fefdsf')
        self.mainLayout =  QVBoxLayout(self)
        self.createMenu()
        self.createControl()
        self.createConnecter()
    def createMenu(self):
        self.gb =  QGroupBox()
        self.gbLayout =  QHBoxLayout()
        self.gbLayout.addWidget(self.gb)
        self.gb.setTitle('Windows')
        self.menuLayout =  QHBoxLayout()
        self.gb.setLayout(self.menuLayout)
        self.mainLayout.addLayout(self.gbLayout)
        
        self.lis =  ('Camera',  'Map',  'Locator (atop)',  'locator (side)',  'Collisions')
        self.menu =  [0] * 5
        self.menuBoxMapper =  QSignalMapper(self)
        for i in range(5):
            self.menu[i] =  QCheckBox(self.lis[i])
            self.menuBoxMapper.setMapping(self.menu[i],  i)
            self.menu[i].stateChanged[int].connect(self.menuBoxMapper.map)
            self.menuLayout.addWidget(self.menu[i])
        
        self.menuBoxMapper.mapped[int].connect(self.changeWindows)
        self.bLog =  QPushButton('Log')
        self.bSettings =  QPushButton('set')
    def changeWindows(self,  i):
        self.changeWindSignal.emit(i)
    def createControl(self):
        #self.msg.emit("Hello")
        self.rotSliderLayout =  QHBoxLayout()
        
        self.rotSlider =  QSlider(Qt.Horizontal)
        self.rotSlider.setMinimumWidth(300)
        self.rotSlider.setTickInterval(2)
        self.rotSlider.setTickPosition(QSlider().TicksBothSides)        
        self.rotLabel =  QLabel('Rotate')
        self.rotLine =  QLineEdit('0')
        self.rotLine.setMaximumWidth(30)
        
        self.rotSliderLayout.addWidget(self.rotSlider)
        self.rotSliderLayout.addStretch(1)
        self.rotSliderLayout.addWidget(self.rotLabel)
        self.rotSliderLayout.addWidget(self.rotLine)

        self.controlLayout =  QHBoxLayout()
        
        self.joystick =  QDial()
        self.joystick.setMinimumHeight(200)
        self.joystick.setMinimumWidth(200)
        
        self.gaz =  QSlider(Qt.Vertical)
        self.gaz.setMinimumWidth(80)
        self.gaz.setTickInterval(5)
        self.gaz.setTickPosition(QSlider().TicksBothSides)
        self.controlLayout.addStretch(1)
        self.controlLayout.addWidget(self.joystick)
        self.controlLayout.addStretch(1)
        self.controlLayout.addWidget(self.gaz)
        self.controlLayout.addStretch(1)
        
        self.bottomLayout =  QHBoxLayout()
        self.bKey =  QPushButton('key')
        self.bFix =  QPushButton('Fix')
        self.bLog =  QPushButton('Log')
        self.bSettings =  QPushButton('set')
        self.bKey.setMaximumWidth(40)
        self.bFix.setMaximumWidth(40)
        self.bLog.setMaximumWidth(40)
        self.bSettings.setMaximumWidth(40)
        
        self.labelSpeed =  QLabel('Speed')
        self.lineSpeed =  QLineEdit('0')
        self.lineSpeed.setMaximumWidth(50)
        self.bottomLayout.addWidget(self.bKey)
        self.bottomLayout.addWidget(self.bFix)
        self.bottomLayout.addWidget(self.bLog)
        self.bottomLayout.addWidget(self.bSettings)
        
        self.bottomLayout.addStretch(1)
        self.bottomLayout.addWidget(self.labelSpeed)
        self.bottomLayout.addWidget(self.lineSpeed)
        self.bottomLayout.addStretch(1)
        
        self.mainLayout.addLayout(self.rotSliderLayout)
        self.mainLayout.addLayout(self.controlLayout)
        self.mainLayout.addLayout(self.bottomLayout)
        
    def createConnecter(self):
        self.connectGB =  QGroupBox(self)
        
        self.connectGBLayout =  QHBoxLayout()
        
        self.choosePortBox=QFormLayout()
        self.cbPort =  QComboBox()
        self.cbPort.setMaximumWidth(80)
        self.cbPort.addItem("Not state")
        self.cbPort.addItems(portList)
        
        self.choosePortBox.addRow("Port",  self.cbPort)
        
        self.connectGBLayout.addLayout(self.choosePortBox)
        
        self.chooseSpeedBox=QFormLayout()
        self.cbSpeed =  QComboBox()
        self.cbSpeed.setMaximumWidth(80)
        self.cbSpeed.addItems(serialSpeedCases)
    
        self.chooseSpeedBox.addRow("Speed",  self.cbSpeed)
    
        self.connectGBLayout.addLayout(self.chooseSpeedBox)
        
        self.connectGB.setLayout(self.connectGBLayout)
        self.mainLayout.addWidget(self.connectGB)
        
        self.pConnect =  QPushButton('Disconnected')
        self.pSending =  QPixmap('pause.png')
        self.lSending =  QLabel()
        self.lSending.setPixmap(self.pSending)
        self.pCheck =  QPushButton('Check')
        self.connectGBLayout.addWidget(self.pConnect)
        self.connectGBLayout.addWidget(self.lSending)
        self.connectGBLayout.addWidget(self.pCheck)





class Camera(QFrame):
    def __init__(self):
        super().__init__()
        self.setFrameShape(QFrame.StyledPanel)
        self.mainLayout =  QVBoxLayout(self)
        self.createControl()
    def createControl(self):
        self.controlLayout =  QHBoxLayout()
        
        self.joy1Layout =  QVBoxLayout()
        self.joy1Label =  QFormLayout()
        self.joy1Line =  QLineEdit('0')
        self.joy1Line.setMaximumWidth(50)
        self.joy1Label.addRow("Horizontal angle",  self.joy1Line)
        self.joystick1 =  QDial()
        self.joystick1.setMinimumHeight(200)
        self.joystick1.setMinimumWidth(200)
        self.joy1Layout.addStretch(1)
        self.joy1Layout.addLayout(self.joy1Label)
        self.joy1Layout.addWidget(self.joystick1)
        self.joy1Layout.addStretch(1)
    
        self.joy2Layout =  QVBoxLayout()
        self.joy2Label =  QFormLayout()
        self.joy2Line =  QLineEdit('0')
        self.joy2Line.setMaximumWidth(50)
        self.joy2Label.addRow("Vertical angle",  self.joy2Line)
        self.joystick2 =  QDial()
        self.joystick2.setMinimumHeight(200)
        self.joystick2.setMinimumWidth(200)
        self.joy2Layout.addStretch(1)
        self.joy2Layout.addLayout(self.joy2Label)
        self.joy2Layout.addWidget(self.joystick2)
        self.joy2Layout.addStretch(1)
        
        self.controlLayout.addLayout(self.joy1Layout)
        self.controlLayout.addLayout(self.joy2Layout)
        
        self.mainLayout.addLayout(self.controlLayout)
if __name__ == "__main__":
    app = QApplication([])
    window = Window()
    sys.exit(app.exec_())