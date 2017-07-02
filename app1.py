from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QSplitter,  QAction, QFormLayout,  QInputDialog, QMessageBox, QPushButton,  QGroupBox,  QCheckBox,  QLineEdit,  QFrame,  QDial)
from PyQt5.QtGui import QIcon, QColor,  QPalette,  QImage,  QPixmap
import os
from PyQt5.QtCore import Qt,  QRect,  pyqtSignal,  QSignalMapper, QSize
import sys
import time
from joystick import Joy
portList=['COM'+str(i) for i in range(1, 4+1)]
serialSpeedCases=['9600', '14400', '38400', '57600', '115200']
class Window (QMainWindow):
    def __init__(self):
        super().__init__()
        self.statusbar =  self.statusBar()
        self.cont =  Content(self, QDesktopWidget().screenGeometry())
        self.cont.res[int, int].connect(self.resiz)
        #self.statusBar().showMessage("qqqqqqqqqqq")
        self.setCentralWidget(self.cont)
        self.setBackground()
        self.center()
        
        self.setWindowTitle('Navigare')
        self.setWindowIcon(QIcon('icon.jpg'))
        
        self.show()
    def resiz(self, a, b):
        #self.resize(a, b)
        self.setMaximumWidth(a)
        self.statusBar().showMessage(str((a, b, self.geometry().width())))
        self.update()
    def setBackground(self):
        pal =  QPalette()
        pal.setColor(QPalette.Background,  Qt.white)
        self.setAutoFillBackground(True)
        self.setPalette(pal)        
    def center(self):
        
        screen =  QDesktopWidget().screenGeometry()
        print(screen)
        self.resize(screen.width()/ 2,  screen.height() / 2)
        size =  self.geometry()
        #x =  (screen.width() - size.width()) / 2
        #y = (screen.height() - size.height()) / 2
        x = 10
        y = 10
        self.move(x,  y)        
class Content(QWidget):
    numberOfWidgets = 6
    res =  pyqtSignal(int, int)
    windows =  [True] * numberOfWidgets
    windows[0]=True
    def __init__(self,  parent, screen):
        super().__init__(parent)
        self.screen = screen
        self.create()
    def create(self):
        self.mainBox =  QVBoxLayout(self)
        
        self.hor1Box =  QHBoxLayout()
        self.widgets = [0]*5
        self.controlSplitter1 =  QSplitter(Qt.Horizontal)
        #self.controlSplitter1 = QHBoxLayout()
        self.controlSplitter2 = QSplitter(Qt.Horizontal)
        
        self.widgets[0] =  Control()
        self.widgets[0].changeWindSignal[int, int].connect(self.changeWindows)
        
        self.widgets[1] =  Camera() 
        
        self.widgets[2] = Map()
        
        self.widgets[3] = Locator()
        
        for i in range(3):
            self.controlSplitter1.addWidget(self.widgets[i])
            if self.windows[i] == True:            
                self.widgets[i].show()
            else:
                self.widgets[i].hide()
        for i in range(3, 4):
            self.controlSplitter2.addWidget(self.widgets[i])
            if self.windows[i] == True:            
                self.widgets[i].show()
            else:
                self.widgets[i].hide()        
        
        #self.hor1Box.addWidget(self.controlSplitter)
        print(self.windows)
        
        self.mainBox.addWidget(self.controlSplitter1)
        self.mainBox.addWidget(self.controlSplitter2)
        #self.mainBox.addStretch(1)
        self.setLayout(self.mainBox)        
    def sendMessage(self,  m):
        self.msg.emit('Hi')
    def changeWindows(self,  i, state):
        print(i, state)
        self.windows[i+1] =   bool(state)
        if self.windows[i+1] == False:
            self.widgets[i+1].hide()
            self.res.emit(400,  400)
            self.setMaximumWidth(400)
        elif self.windows[i+1] == True:      
            self.widgets[i+1].show()
            self.res.emit(890, 400)
            self.setMaximumWidth(890)
        self.update()
class Widgets(QFrame):
    def __init__(self):
        super().__init__()
        self.setFrameShape(QFrame.StyledPanel)
        self.mainLayout =  QVBoxLayout(self)
        self.setMaximumWidth(400)
        self.setMaximumHeight(400)        
        self.create()  
    def create(self):
        self.mainWidgetLayout =  QVBoxLayout()
        self.mainLayout.addLayout(self.mainWidgetLayout)    
class Control(Widgets):
    changeWindSignal =  pyqtSignal(int, int)
    global portList
    global serialSpeedCases
    def __init__(self):
        super().__init__()
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
        self.mainWidgetLayout.addLayout(self.gbLayout)
        self.setMaximumWidth(400)
        self.setMaximumHeight(400)
        
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
        state = self.menu[i].checkState()
        self.changeWindSignal.emit(i, state)
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
        
        self.joystick =  Joy()
        self.joystick.setMinimumSize(300, 200)
        #self.joystick.setMinimumWidth(200)
        self.joystick.sender[int, int].connect(self.do)
        
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
        
        self.mainWidgetLayout.addLayout(self.rotSliderLayout)
        self.mainWidgetLayout.addLayout(self.controlLayout)
        self.mainWidgetLayout.addLayout(self.bottomLayout)
    def do(self, a, b):
        print(a, b)
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
        self.mainWidgetLayout.addWidget(self.connectGB)
        
        self.pConnect =  QPushButton('Disconnected')
        self.pSending =  QPixmap('pause.png')
        self.lSending =  QLabel()
        self.lSending.setPixmap(self.pSending)
        self.pCheck =  QPushButton('Check')
        self.connectGBLayout.addWidget(self.pConnect)
        self.connectGBLayout.addWidget(self.lSending)
        self.connectGBLayout.addWidget(self.pCheck)





class Camera(Widgets):
    def __init__(self):
        super().__init__()
        self.createControl()
    def createControl(self):
    
        self.cameraHBox = QHBoxLayout()
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
    
        self.cameraHBox.addLayout(self.joy1Layout)
        self.cameraHBox.addLayout(self.joy2Layout)
        self.mainWidgetLayout.addLayout(self.cameraHBox)  
class Map(Widgets):
    def __init__(self):
        super().__init__()   

class Locator(Widgets):
    def __init__(self):
        super().__init__()



if __name__ == "__main__":
    app = QApplication([])
    window = Window()
    sys.exit(app.exec_())