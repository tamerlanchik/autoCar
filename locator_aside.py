from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QSplitter,  QAction, QFormLayout,  QInputDialog, QScrollArea,  QMessageBox, QPushButton,  QGroupBox,  QCheckBox,  QLineEdit,  QFrame,  QDial)
from PyQt5.QtGui import QIcon, QColor,  QPalette,  QImage,  QPixmap, QPainter, QPolygonF,  QBrush
import os
from PyQt5.QtCore import Qt,  QRect,  pyqtSignal,  QSignalMapper, QSize, QPointF,  QBasicTimer
from widgets import Widgets

class Locator_aside(Widgets):  
    points = ( (-100, -100), (-180, -80), (-120, -70), (-220, -60) )
    def __init__(self,  pasp):
        super().__init__(pasp)
        self.style = open('locator.css', 'r')
        self.styleSheet = self.style.read()
        self.style.close()
        self.setStyleSheet(self.styleSheet)
        
        self.setMinimumWidth(400)
        self.setMinimumHeight(400)
        self.iconLocator = QPixmap('locator-aside.png')
        
        self.contr = QHBoxLayout()
        self.f = QLabel()
        self.mainWidgetLayout.addStretch(2)
        self.mainWidgetLayout.addLayout(self.contr)
        self.rescanBut = QPushButton('Rescan')
        self.rescanBut.setMinimumSize(60, 20)
        self.rescanBut.toggled.connect(self.rescan)
        self.scanSlider = QSlider(Qt.Horizontal)
        self.contr.addWidget(self.rescanBut)
        self.contr.addWidget(self.scanSlider)
    def rescan(self): 
        print('sss')
    def paintEvent(self, event):
        geom  = self.geometry()
        self.zero = (geom.width()-10, int(geom.height()*0.9))
        p = QPainter(self)
        p.setRenderHint(QPainter.Antialiasing)   #smoothing for lines
        p.setRenderHint(QPainter.SmoothPixmapTransform)  #smoothing for Pixmap
        p.setPen(Qt.blue)        
        
        #drawing grid & scale numbers
        p.translate(*self.zero)
        step = 20
        p.setOpacity(0.2)
        for i in range(-self.zero[0]//step, 2):
            p.drawLine(i*step, 0, i*step, -geom.height())
        for i in range(-self.zero[1]//step, 0):
            p.drawLine(0, i*step,  -geom.width(), i*step)
            
        p.setOpacity(0.7)
        
        
        for i in range(-self.zero[0]//(step), 2, 2):
            p.drawText(i*step-10, 10, str(i*step))
            
        for i in range(0, -self.zero[1]//step, -2):
            p.drawText(-self.zero[0]+10, i*step+5, str(i*step))
        #-----------------------------------------------------------
        
        #drawing locator
        p.setOpacity(1)
        p.drawLine(-self.zero[0], 0, 0, 0)   #hor Line
        
        p.translate(0, -30)
        p.rotate(50)
        p.drawLine(0, 0, -geom.width()*2, 0) #rotatable line
        p.drawPixmap(-30, -10, self.iconLocator) #locator icon
        #-----------------------------------------------------------
        
        #drawing barrier map
        p.rotate(-50)
        p.translate(0, 30)
        p.setBrush(Qt.blue)
        p.setOpacity(0.2)
        
        
        self.polygon = QPolygonF()
        self.polygon.append(QPointF(self.points[0][1], 0))
        self.polygon.append(QPointF(-self.zero[0], 0))
        self.polygon.append(QPointF(-self.zero[0], -geom.height()*0.9))
        self.polygon.append(QPointF(self.points[-1][1], -self.zero[1]))
        
        for u in self.points:
            p.drawEllipse(u[0]-1, u[1]-1, 2, 2)
            self.polygon.append(QPointF(*u))
            
        p.drawPolygon(self.polygon)        
