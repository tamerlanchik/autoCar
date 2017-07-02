from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QSplitter,  QAction, QFormLayout,  QInputDialog, QMessageBox, QPushButton,  QGroupBox,  QCheckBox,  QLineEdit,  QFrame,  QDial)
from PyQt5.QtGui import QPolygon, QPainter, QIcon, QColor,  QPalette,  QImage,  QPixmap
import os
from PyQt5.QtCore import  QPointF, Qt,  QRect,  pyqtSignal,  QSignalMapper, QPoint, QSize
import sys
import time

class Joy(QFrame):
    sender = pyqtSignal(int, int)
    pos0 = pos =[0, 0]
    shiftPos = [0, 0]
    R = 60
    size = (200, 200)
    
    def __init__(self, maxRange):
        super().__init__()
        self.setFrameShape(QFrame.StyledPanel)
        self.maxRange = maxRange
        if __name__ == "__main__":
            self.setGeometry(300, 300, *self.size)
            self.show()
            
    def setMinimumSize(self, x, y):
        self.size = [x, y]
        super().setMinimumSize(x, y)
        
    def send(self, pos):
        self.sender.emit(pos[0], -pos[1])
        
    def mouseMoveEvent(self, event):
        x = event.pos().x()-self.size[0]//2  #getting mouse coorditates in the translated coordintion system
        y = event.pos().y()-self.size[1]//2 
        
        x -= self.shiftPos[0] # getting coordinates of the joystick centre
        y -= self.shiftPos[1]
        
        
        if self.maxRange['x'][0]<= x <= self.maxRange['x'][1]:
            self.pos[0] = x
        else:
            if abs(self.maxRange['x'][0] - x) < abs(self.maxRange['x'][1] - x):
                self.pos[0] = self.maxRange['x'][0]
            else:
                self.pos[0] = self.maxRange['x'][1]
        
        if self.maxRange['y'][0]<=y <= self.maxRange['y'][1]:
            self.pos[1] = y
        else:
            if abs(self.maxRange['y'][0] - y) < abs(self.maxRange['y'][1] - y):
                self.pos[1] = self.maxRange['y'][0]
            else:
                self.pos[1] = self.maxRange['y'][1]      
        self.send(self.pos)
        self.update()
        
    def mousePressEvent(self, event):
        x, y = event.pos().x()-self.size[0]//2, event.pos().y()-self.size[1]//2
        self.shiftPos = [x, y]
        
    def mouseReleaseEvent(self, event):
        self.pos = [0, 0]
        self.update()
        
    def paintEvent(self, event):
        p = QPainter(self)
        p.setRenderHint(QPainter.Antialiasing)
        p.translate(self.size[0]//2, self.size[1]//2)
        
        p.setPen(Qt.gray)
        p.drawLine(-self.size[0]//2, 0, self.size[0]//2, 0)
        p.drawLine(0, -self.size[1]//2, 0, self.size[1]//2)
        
        p.setBrush(Qt.black)
        p.setPen(Qt.black)
        p.setOpacity(0.6)
        p.drawEllipse(self.pos[0]-self.R+3, self.pos[1]-self.R+8, self.R*2, self.R*2)
        
        p.setOpacity(1)
        p.setBrush(Qt.darkBlue)
        p.setPen(Qt.blue)
        p.drawEllipse(self.pos[0]-self.R, self.pos[1]-self.R, self.R*2, self.R*2)
        
        
        p.setPen(Qt.black)
        p.setOpacity(0.5)
        p.drawText(self.size[0]//2-50, self.size[1]//2-20, str(self.pos))
        
    def keyPressEvent(self, event):
        key = event.key()
        if   key == Qt.Key_Left:  self.pos[0] -= 1
        elif key == Qt.Key_Right: self.pos[0] += 1
        elif key == Qt.Key_Up:    self.pos[1] -= 1
        elif key == Qt.Key_Down:  self.pos[1] += 1
        elif key == Qt.Key_Space: self.pos = [0, 0]
        self.sender.emit(self.pos[0], -self.pos[1])
        self.update()
    
    def setPosition(self, x, y):
        self.pos = [x, -y]
        self.update()
if __name__ == "__main__":
    app = QApplication([])
    joy = Joy({'rotate':(-50, 50), 'gaz':(-30, 30)})
    sys.exit(app.exec_())