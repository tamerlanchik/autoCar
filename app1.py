from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QSplitter,  QAction, QFormLayout,  QInputDialog, QScrollArea,  QMessageBox, QPushButton,  QGroupBox,  QCheckBox,  QLineEdit,  QFrame,  QDial)
from PyQt5.QtGui import QIcon, QColor,  QPalette,  QImage,  QPixmap, QPainter, QPolygonF,  QBrush
import os
from PyQt5.QtCore import Qt,  QRect,  pyqtSignal,  QSignalMapper, QSize, QPointF,  QBasicTimer
from PyQt5.QtMultimedia import QSound
import sys
import time
import random
from net import Net
from content import Content
from data import Data
import math
class Window (QMainWindow):
    send =  pyqtSignal(int,  int)
    def __init__(self):
        print('window')
        super().__init__()
        self.statusbar =  self.statusBar()
        self.scrollArea =  QScrollArea()
        self.cont =  Content(self, QDesktopWidget().screenGeometry())
        self.scrollArea.setWidget(self.cont)
        self.cont.send[str,  int].connect(self.sendData)
        self.cont.receive[int].connect(self.receiveData)
        self.cont.showMessage[str].connect(self.showMessage)
        self.setCentralWidget(self.cont)
        self.setBackground()
        self.center()
        
        self.setWindowTitle('Navigare')
        self.setWindowIcon(QIcon('icon.jpg'))
        
        self.net =  Net()
        self.net.send[str].connect(self.sendData)
        self.show()
    def closeEvent(self,  event):
        self.net.sendData("connect/0")
    def sendData(self,  data,  numb):
        self.statusBar().showMessage(str(data))
        ans =  self.net.sendData(data)
        self.statusbar.showMessage(ans)
        if 'connect' in data:
            if ans == 'Connected':
                for i in range(self.cont.numberOfWidgets):
                    self.cont.widgets[i].isConnectedFlag = True
                    #self.cont.widget[numb].connectStateChanged(True)
            elif ans == 'Disconnected':
                for i in range(self.cont.numberOfWidgets):
                    self.cont.widgets[i].isConnectedFlag = False
                    #self.cont.widget[numb].connectStateChanged(False)
    def receiveData(self,  numb):
        ans =  self.net.receiveData()
        self.cont.widgets[numb].data =  ans
    def showMessage(self,  message):
        self.statusbar.showMessage(message)
    def setBackground(self):
        pal =  QPalette()
        pal.setColor(QPalette.Background,  Qt.white)
        self.setAutoFillBackground(True)
        self.setPalette(pal)        
    def center(self):
        
        screen =  QDesktopWidget().screenGeometry()
        self.resize(screen.width()/ 2,  screen.height() / 2)
        size =  self.geometry()
        #x =  (screen.width() - size.width()) / 2
        #y = (screen.height() - size.height()) / 2
        x = 10
        y = 10
        self.move(x,  y)        
if __name__ == "__main__":
    app = QApplication([])
    data = Data()
    window = Window()
    sys.exit(app.exec_())