from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QSplitter,  QAction, QFormLayout,  QInputDialog, QScrollArea,  QMessageBox, QPushButton,  QGroupBox,  QCheckBox,  QLineEdit,  QFrame,  QDial)
from PyQt5.QtGui import QIcon, QColor,  QPalette,  QImage,  QPixmap, QPainter, QPolygonF,  QBrush
import os
from PyQt5.QtCore import Qt,  QRect,  pyqtSignal,  QSignalMapper, QSize, QPointF,  QBasicTimer
from widgets import Widgets
from joystick import Joy
class Camera(Widgets):
    maxRange = { 'x': [-90, 90], 'y': [-90, 90] }
    def __init__(self,  pasp):
        super().__init__(pasp)
        self.createControl()
    def createControl(self):
    
        self.joyLayout = QHBoxLayout()
        self.joystick = Joy(self.maxRange)
        self.joystick.setMinimumSize(200, 200)
        self.joyLayout.addWidget(self.joystick)
        self.mainWidgetLayout.addLayout(self.joyLayout) 
