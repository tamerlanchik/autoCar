from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QSplitter,  QAction, QFormLayout,  QInputDialog, QScrollArea,  QMessageBox, QPushButton,  QGroupBox,  QCheckBox,  QLineEdit,  QFrame,  QDial)
from PyQt5.QtGui import QIcon, QColor,  QPalette,  QImage,  QPixmap, QPainter, QPolygonF,  QBrush
import os
from PyQt5.QtCore import Qt,  QRect,  pyqtSignal,  QSignalMapper, QSize, QPointF,  QBasicTimer
from control import Control
from camera import Camera
from map import Map
from locator_aside import Locator_aside
from locator_atop import Locator_atop
from collisions import Collisions
class Content(QWidget):
    numberOfWidgets = 6
    receive =  pyqtSignal(int)
    res =  pyqtSignal(int, int)
    send =  pyqtSignal(str,  int)
    showMessage =  pyqtSignal(str)
    windows =  [1, 0, 0, 0, 0, 0]
    #windows[0]=True
    def __init__(self,  parent, screen):
        super().__init__(parent)
        self.screen = screen
        self.create()
    def create(self):
        self.mainBox =  QVBoxLayout(self)
        
        self.widgets = [0]*self.numberOfWidgets
        
        self.controlSplitter = [0]*2
        for i in range(2):
            self.controlSplitter[i] =  QSplitter(Qt.Horizontal)
            self.mainBox.addWidget(self.controlSplitter[i])
        
        #creating widgets
        self.widgets = [Control(pasp =  0), Locator_atop(pasp =  4), Camera(pasp =  1),  Map(pasp =  2),  Locator_aside(pasp =  3), Collisions(pasp =  5) ]
        
        #self.widgets[0].send[int].connect(self.sendData)
        
        #adding widgets to the layout
        for i in range(self.numberOfWidgets):
            self.widgets[i].send[str,  int].connect(self.sendData)
            self.widgets[i].receive[int].connect(self.receiveData)
            self.widgets[i].showMessage[str].connect(self.sendMessage)
            self.controlSplitter[i//3].addWidget(self.widgets[i])
            if self.windows[i] == True:            
                self.widgets[i].show()
                self.widgets[i].isActive =  True
            else:
                self.widgets[i].hide()   
        
        self.setLayout(self.mainBox)
    def sendData(self,  data,  numb):
        self.send.emit(data,  numb)
    def receiveData(self,  numb):
        self.receive.emit(numb)
    def sendMessage(self,  m):
        self.showMessage.emit(m)
    
