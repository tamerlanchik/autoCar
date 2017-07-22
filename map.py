from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QSplitter,  QAction, QFormLayout,  QInputDialog, QScrollArea,  QMessageBox, QPushButton,  QGroupBox,  QCheckBox,  QLineEdit,  QFrame,  QDial)
from PyQt5.QtGui import QIcon, QColor,  QPalette,  QImage,  QPixmap, QPainter, QPolygonF,  QBrush
import os
from PyQt5.QtCore import Qt,  QRect,  pyqtSignal,  QSignalMapper, QSize, QPointF,  QBasicTimer
from widgets import Widgets

class Map(Widgets):
    def __init__(self,  pasp):
        super().__init__(pasp) 
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

