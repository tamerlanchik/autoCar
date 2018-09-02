from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QSplitter,  QAction, QFormLayout,  QInputDialog, QScrollArea,  QMessageBox, QPushButton,  QGroupBox,  QCheckBox,  QLineEdit,  QFrame,  QDial)
from PyQt5.QtGui import QIcon, QColor,  QPalette,  QImage,  QPixmap, QPainter, QPolygonF,  QBrush
import os
from PyQt5.QtCore import Qt,  QRect,  pyqtSignal,  QSignalMapper, QSize, QPointF,  QBasicTimer
from widgets import Widgets
from joystick import Joy
from data import Data
d = Data()
class Control(Widgets):
    maxRange = {'x':(-90, 90), 'y': (-30, 30) }
    isConnected =  False
    def __init__(self,  pasp):
        super().__init__(pasp)
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
        #self.changeWindSignal.emit(i, state)
    def createControl(self):
        #self.msg.emit("Hello")
        self.rotSliderLayout =  QHBoxLayout()
        
        self.rotSlider =  QSlider(Qt.Horizontal)
        self.rotSlider.setRange(*self.maxRange['x'])
        self.rotSlider.setMinimumWidth(300)
        self.rotSlider.setTickInterval(5)
        self.rotSlider.setTickPosition(QSlider().TicksBothSides)
        self.rotSlider.valueChanged[int].connect(self.rotSliderChanged)
        self.rotLabel =  QLabel('Rotate')
        self.rotLine =  QLineEdit('0')
        self.rotLine.setMaximumWidth(30)
        
        self.rotSliderLayout.addWidget(self.rotSlider)
        self.rotSliderLayout.addStretch(1)
        self.rotSliderLayout.addWidget(self.rotLabel)
        self.rotSliderLayout.addWidget(self.rotLine)

        self.controlLayout =  QHBoxLayout()
        
        self.joystick =  Joy(self.maxRange)
        self.joystick.setFocusPolicy(Qt.StrongFocus)
        self.joystick.setMinimumSize(300, 200)
        self.joystick.sender[int, int].connect(self.joystickMoved)
        
        
        self.gazSlider =  QSlider(Qt.Vertical)
        self.gazSlider.setRange(*self.maxRange['y'])
        self.gazSlider.setMinimumWidth(80)
        self.gazSlider.setTickInterval(2)
        self.gazSlider.setTickPosition(QSlider().TicksBothSides)
        self.gazSlider.valueChanged[int].connect(self.gazSliderChanged)
        self.controlLayout.addStretch(1)
        self.controlLayout.addWidget(self.joystick)
        self.controlLayout.addStretch(1)
        self.controlLayout.addWidget(self.gazSlider)
        self.controlLayout.addStretch(1)
        
        self.bottomLayout =  QHBoxLayout()
        self.bKey =  QPushButton('key')
        self.bFix =  QPushButton('Fix')
        self.bLog =  QPushButton('Log')
        self.bLog.clicked.connect(self.p)
        self.bSettings =  QPushButton('set')
        self.bKey.setMaximumWidth(40)
        self.bFix.setMaximumWidth(40)
        self.bLog.setMaximumWidth(40)
        self.bSettings.setMaximumWidth(40)
        
        self.labelSpeed =  QLabel('Speed')
        self.lineSpeed =  QLineEdit('0')
        self.gazLabel =  QLabel('Gas')
        self.gazLine =  QLineEdit('0')        
        self.lineSpeed.setMaximumWidth(50)
        self.bottomLayout.addWidget(self.bKey)
        self.bottomLayout.addWidget(self.bFix)
        self.bottomLayout.addWidget(self.bLog)
        self.bottomLayout.addWidget(self.bSettings)
        
        self.bottomLayout.addStretch(1)
        self.bottomLayout.addWidget(self.labelSpeed)
        self.bottomLayout.addWidget(self.lineSpeed)
        self.bottomLayout.addWidget(self.gazLabel)
        self.bottomLayout.addWidget(self.gazLine)
        self.bottomLayout.addStretch(1)
        
        self.mainWidgetLayout.addLayout(self.rotSliderLayout)
        self.mainWidgetLayout.addLayout(self.controlLayout)
        self.mainWidgetLayout.addLayout(self.bottomLayout)
    def p(self):
        print('Ffffffff')
    def createConnecter(self):
        self.connectGB =  QGroupBox(self)
        
        self.connectGBLayout =  QHBoxLayout()
        
        self.choosePortBox=QFormLayout()
        self.cbPort =  QComboBox()
        self.cbPort.setMaximumWidth(80)
        self.cbPort.addItems(d.portList)
        self.cbPort.activated[int].connect(self.connect)
        self.cbPort.setCurrentIndex(15)
        self.cbLabel =  QLabel('<font color = "red">Disconnected</font>')
        
        self.choosePortBox.addRow("Port",  self.cbPort)
        self.choosePortBox.addRow("State",  self.cbLabel)
        
        self.connectGBLayout.addLayout(self.choosePortBox)
        
        self.chooseSpeedBox=QFormLayout()
        self.cbSpeed =  QComboBox()
        self.cbSpeed.setMaximumWidth(80)
        self.cbSpeed.addItems(d.serialSpeedCases)
        self.cbSpeed.setCurrentIndex(0)
    
        self.chooseSpeedBox.addRow("Speed",  self.cbSpeed)
    
        self.connectGBLayout.addLayout(self.chooseSpeedBox)
        
        self.connectGB.setLayout(self.connectGBLayout)
        self.mainWidgetLayout.addWidget(self.connectGB)
        
        self.pSending =  QPixmap('pause.png')
        self.lSending =  QLabel()
        self.lSending.setPixmap(self.pSending)
        self.pCheck =  QPushButton('Check')
        self.connectGBLayout.addWidget(self.lSending)
        self.connectGBLayout.addWidget(self.pCheck)

    def rotSliderChanged(self, rot):
        global rotate
        rotate = rot
        self.updateControls()
    def gazSliderChanged(self, gaze):
        global gaz
        gaz = gaze
        self.updateControls()
    def updateControls(self):
        self.rotLine.setText(str(rotate))
        self.gazLine.setText(str(gaz))
        self.joystick.setPosition(rotate, gaz)
        self.rotSlider.setValue(rotate)
        self.gazSlider.setValue(gaz)
        self.send.emit('move' + str(rotate) + '/' + str(gaz),  self.pasp)
    def joystickMoved(self, x, y):
        global gaz
        global rotate
        gaz = y
        rotate = x
        self.updateControls()
    def connect(self,  port):
        global portList
        speed =  self.cbSpeed.currentText()
        self.sendData('connect' + d.portList[port] + '/' + speed)
    def connectStateChanged(self, data):
        if data ==  True:
            self.cbLabel.setText('font color = "green">Connected</font>')
        else:
            self.cbLabel.setText('<font color = "red">Disconnected</font>')
            

        
