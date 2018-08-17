from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QSplitter,  QAction, QFormLayout,  QInputDialog, QScrollArea,  QMessageBox, QPushButton,  QGroupBox,  QCheckBox,  QLineEdit,  QFrame,  QDial)
from PyQt5.QtGui import QIcon, QColor,  QPalette,  QImage,  QPixmap, QPainter, QPolygonF,  QBrush
import os
from PyQt5.QtCore import Qt,  QRect,  pyqtSignal,  QSignalMapper, QSize, QPointF,  QBasicTimer
from widgets import Widgets

class Locator_atop(Widgets):
    points = ( (-100, -100), (-80, -180), (-70, -120), (-60, -220) )
    mouse = [0, 0]
    center = [0, 0]
    def __init__(self,  pasp):
        super().__init__(pasp)
        self.style = open('locator.css', 'r')
        self.styleSheet = self.style.read()
        self.style.close()
        self.setStyleSheet(self.styleSheet)        
        self.setMinimumWidth(500)
        self.setMinimumHeight(500)
        self.iconLocator = QPixmap('locator-atop.png')
        self.points = self.points[::-1]
        self.contr = QHBoxLayout()
        self.f = QLabel()
        self.mainWidgetLayout.addStretch(2)
        self.mainWidgetLayout.addLayout(self.contr)
        self.rescanBut = QPushButton('Rescan')
        self.rescanBut.setMinimumSize(60, 20)
        self.rescanBut.clicked.connect(self.rescan)
        self.scanSlider = QSlider(Qt.Horizontal)
        self.contr.addWidget(self.rescanBut)
        self.contr.addWidget(self.scanSlider)
        self.timer =  QBasicTimer()
        self.polygon =  QPolygonF()
        self.angle =  90
    def start(self):
        #self.timer.start(100,  self)
        #self.sendData("connect19/9600")
        print("Started")
        print()
    def timerEvent(self,  event):
        if self.isConnectedFlag ==  True:
            self.receiveData()
            self.showMessage.emit(self.data)
            if self.data !=  None:
                if self.data ==  "Stop":
                    print("Stop")
                    self.timer.stop()
                else:
                    self.data =  self.data[:-5]
                    print(self.data)
                    i,  l =  map(int, self.data.replace('\n',  '').split('/'))
                    self.angle =  90 - i
                    x =  l *  math.cos(math.radians(i))
                    y =  l *  math.sin(math.radians(-i))
                    #self.polygon.append(QPointF(x,  y))
                    self.points.append((int(x * 8),  int(y * 8)))
                    print(self.points[-1])
        self.update()
    def rescan(self):
        geom =  self.geometry()
        print(geom)
        self.polygon = QPolygonF()
        self.polygon.append(QPointF(-geom.width()//2, -geom.height() // 2))
        self.polygon.append(QPointF(-geom.width()//2, -geom.height()*0.9))
        self.polygon.append(QPointF(geom.width()//2, -geom.height()*0.9))
        self.polygon.append(QPointF(geom.width()//2, -geom.height() // 2))
        
        self.points =  []
        self.sendData("rescan")
        self.update()
        self.timer.start(10,  self)
    def paintEvent(self, event):
        try:
            geom  = self.geometry()
            p = QPainter(self)
            p.setRenderHint(QPainter.Antialiasing)   #smoothing for lines
            p.setRenderHint(QPainter.SmoothPixmapTransform)  #smoothing for Pixmap
            p.setPen(Qt.blue)     
            
            #drawing grid & scale numbers
            p.translate(*self.center)
            step = 20
            p.setOpacity(0.2)
            
            for i in range(geom.width()//step):
                p.drawLine(i*step, 0, i*step, geom.height()*0.9)
            for i in range(geom.height()//step):
                p.drawLine(0, i*step,  geom.width(), i*step) 
                
            p.setOpacity(0.7)
            p.translate(geom.width()//2, geom.height()*0.9)
            p.drawLine(0, 0, 200, 200)
            for i in range(-geom.width()//(step*2), geom.width()//(step*2), 2):
                p.drawText(i*step-10, 10, str(i*step))
            for i in range(0, -geom.height()//step, -2):
                p.drawText(-geom.width()//2, i*step+5, str(i*step))    
            #-----------------------------------------------------------
            
            #drawing locator
            p.setOpacity(1)
            p.drawLine(-geom.width()//2, 0, geom.width(), 0)   #hor Line
            
            p.rotate(self.angle)
            p.drawLine(0, 0, 0, -geom.height()) #rotatable line
            p.drawPixmap(-20, -27, self.iconLocator) #locator icon
            #-----------------------------------------------------------
            
            #drawing barrier map
            p.rotate(-self.angle)
            p.setBrush(Qt.blue)
            p.setOpacity(0.2)
            
            
            for u in self.points:
                p.setOpacity(1)
                p.setBrush(QBrush(Qt.red,  Qt.SolidPattern))
                p.drawEllipse(u[0]-2, u[1]-2, 5, 5)
                p.setOpacity(0.2)
                p.setBrush(Qt.blue)
                self.polygon.append(QPointF(*u))
                
            p.drawPolygon(self.polygon)
        except:
            print("Error")

    def mousePressEvent(self, event):
        self.mouse = [event.pos().x(), event.pos().y()]
    def mouseMoveEvent(self, event):
        self.center = [event.pos().x() - self.mouse[0], event.pos().y() - self.mouse[1]]
        self.update()