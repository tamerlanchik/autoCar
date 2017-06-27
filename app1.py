from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QAction, QInputDialog, QMessageBox, QPushButton)
from PyQt5.QtGui import QIcon, QColor
import os
import serial
from PyQt5.QtCore import Qt
import sys
import time

class Window (QMainWindow):
    def __init__(self):
        super().__init__()
        screen =  QDesktopWidget().screenGeometry()
        print(screen,  screen.width(),  screen.height())
        self.resize(screen.width() - 10,  screen.height() - 30)
        size =  self.geometry()
        print(size)
        x =  (screen.width() - size.width()) / 2
        y = (screen.height() - size.height()) / 2
        print(x,  y)
        self.move(x,  y)
        self.show()
if __name__ == "__main__":
    app = QApplication([])
    window = Window()
    sys.exit(app.exec_())