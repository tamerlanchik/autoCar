from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QSplitter,  QAction, QFormLayout,  QInputDialog, QMessageBox, QPushButton,  QGroupBox,  QCheckBox,  QLineEdit,  QFrame,  QDial)
from PyQt5.QtGui import QIcon, QColor,  QPalette,  QImage,  QPixmap
import os
from PyQt5.QtCore import Qt,  QRect,  pyqtSignal,  QSignalMapper, QSize
import sys
import time
from joystick import Joy
#from communicator import Communicator

from multiprocessing import Process
portList=['COM'+str(i) for i in range(1, 4+1)]
serialSpeedCases=['9600', '14400', '38400', '57600', '115200']
rotate = 0
gaz = 0
class Window (QMainWindow):
    
    def __init__(self):
        for i in range(100):
            print('Working class A, i=%s' % i)
            sleep(0.5)