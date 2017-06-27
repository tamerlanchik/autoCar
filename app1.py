from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QAction, QInputDialog, QMessageBox, QPushButton,  QGroupBox,  QCheckBox,  QLineEdit,  QFrame,  QDial)
from PyQt5.QtGui import QIcon, QColor,  QPalette
import os
import serial
from PyQt5.QtCore import Qt,  QRect,  pyqtSignal
import sys
import time

class Window (QMainWindow):
    def __init__(self):
        super().__init__()
        self.statusbar =  self.statusBar()
        self.cont =  Content(self)
        self.cont.ms[str].connect(self.statusBar().showMessage)
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
        self.resize(screen.width()/ 3,  screen.height() / 3)
        size =  self.geometry()
        x =  (screen.width() - size.width()) / 2
        y = (screen.height() - size.height()) / 2
        self.move(x,  y)        
class Content(QWidget):
    ms =  pyqtSignal(str)
    windows =  [False] * 5
    def __init__(self,  parent):
        super().__init__(parent)
        self.mainBox =  QVBoxLayout(self)
        self.control =  Control()
        
        self.mainBox.addWidget(self.control)
        self.mainBox.addStretch(1)
        self.setLayout(self.mainBox)
    def sendMessage(self,  m):
        self.msg.emit('Hi')
class Control(QWidget):
    #msg =  pyqtSignal(str)
    def __init__(self):
        super().__init__()
        #self.msg.emit('fefdsf')
        self.mainLayout =  QVBoxLayout(self)
        self.createMenu()
        self.createControl()
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
        for i in range(5):
            self.menu[i] =  QCheckBox(self.lis[i])
            self.menuLayout.addWidget(self.menu[i])
        self.bLog =  QPushButton('Log')
        self.bSettings =  QPushButton('set')
        self.menuLayout.addWidget(self.bLog)
        self.menuLayout.addWidget(self.bSettings)
    def createControl(self):
        #self.msg.emit("Hello")
        self.rotSliderLayout =  QHBoxLayout()
        
        self.rotSlider =  QSlider(Qt.Horizontal)
        self.rotSlider.setMinimumWidth(450)
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
        self.labelSpeed =  QLabel('Speed')
        self.lineSpeed =  QLineEdit('0')
        self.lineSpeed.setMaximumWidth(50)
        self.bottomLayout.addWidget(self.bKey)
        self.bottomLayout.addWidget(self.bFix)
        self.bottomLayout.addStretch(1)
        self.bottomLayout.addWidget(self.labelSpeed)
        self.bottomLayout.addWidget(self.lineSpeed)
        self.bottomLayout.addStretch(1)
        
        self.mainLayout.addLayout(self.rotSliderLayout)
        self.mainLayout.addLayout(self.controlLayout)
        self.mainLayout.addLayout(self.bottomLayout)



if __name__ == "__main__":
    app = QApplication([])
    window = Window()
    sys.exit(app.exec_())