from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QSplitter,  QAction, QFormLayout,  QInputDialog, QScrollArea,  QMessageBox, QPushButton,  QGroupBox,  QCheckBox,  QLineEdit,  QFrame,  QDial)
from PyQt5.QtGui import QIcon, QColor,  QPalette,  QImage,  QPixmap, QPainter, QPolygonF,  QBrush
import os
from PyQt5.QtCore import Qt,  QRect,  pyqtSignal,  QSignalMapper, QSize, QPointF,  QBasicTimer
from PyQt5.QtMultimedia import QSound
from widgets import Widgets

class Collisions(Widgets):
    coll = [False, False, False, False]
    def __init__(self, pasp):
        super().__init__(pasp)
        self.setMinimumWidth(300)
        self.setMinimumHeight(200)
        self.img = QPixmap('car.png')
        self.img = self.img.scaled(200, 94)
        self.imgSize = (200, 94)
        self.bordImg = QPixmap('border.png')
        self.bordImg = self.bordImg.scaled(120, 50)
        self.bordSize = (120, 50)
        self.bordPos = ( (-self.bordSize[0]//2, -self.imgSize[1]//2-55),
                         (-self.bordSize[0]//2, -self.imgSize[1]//2+100),
                         (-self.bordSize[0]//2, -self.imgSize[1]//2-100),
                         (-self.bordSize[0]//2, self.imgSize[1]//2+50) )
        self.coll = [True]*4
        self.alarm = QSound('frog.wav')
        self.contr = QHBoxLayout()
        self.f = QLabel()
        self.mainWidgetLayout.addStretch(2)
        self.mainWidgetLayout.addLayout(self.contr)
        self.rescanBut = QPushButton('Rescan')
        self.scanSlider = QSlider(Qt.Horizontal)
        self.contr.addWidget(self.rescanBut)
        self.contr.addWidget(self.scanSlider)        
    def paintEvent(self, event):
        geom = self.geometry()
        p = QPainter(self)
        p.setRenderHint(QPainter.Antialiasing)   #smoothing for lines
        p.setRenderHint(QPainter.SmoothPixmapTransform)  #smoothing for Pixmap        
        p.setPen(Qt.blue)
        p.setBrush(Qt.blue)
        p.translate(geom.width()//2, geom.height()//2)
        
        p.drawPixmap(-self.imgSize[0]//2, -self.imgSize[1]//2, self.img)
        p.setOpacity(0.7)
        
        for i in range(4):
            if i == 2: p.rotate(90)
            if self.coll[i]==True:
                p.drawPixmap(*self.bordPos[i], self.bordImg)
    def collisionFound(self, data):
        for i in range(4):
            if data[i] == True and self.coll[i]==False:
                self.alarm = QSound('frog.wav')
            self.coll[i] = data[i]
        self.update()
