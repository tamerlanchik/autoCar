from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QAction, QInputDialog, QMessageBox, QPushButton)
from PyQt5.QtGui import QIcon, QColor,  QPalette
import os
import serial
from PyQt5.QtCore import Qt
import sys
import time

class Window (QMainWindow):
    def __init__(self):
        super().__init__()
        
        self.setBackground()
        self.center()
        
        self.statusBar =  self.statusBar()
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
        self.resize(screen.width() - 20,  screen.height() - 40)
        size =  self.geometry()
        x =  (screen.width() - size.width()) / 2
        y = (screen.height() - size.height()) / 2
        self.move(x,  y)        
if __name__ == "__main__":
    app = QApplication([])
    window = Window()
    sys.exit(app.exec_())