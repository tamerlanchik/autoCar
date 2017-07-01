from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QSplitter,  QAction, QFormLayout,  QInputDialog, QMessageBox, QPushButton,  QGroupBox,  QCheckBox,  QLineEdit,  QFrame,  QDial)
from PyQt5.QtGui import QPainter, QIcon, QColor,  QPalette,  QImage,  QPixmap
import os
from PyQt5.QtCore import Qt,  QRect,  pyqtSignal,  QSignalMapper, QPoint, QSize
import sys
import time

class Joy(QFrame):
    sender = pyqtSignal(int, int)
    pos = [0, 0]
    shiftPos = [0, 0]
    R = 30
    size = (200, 200)
    def __init__(self):
        super().__init__()
        if __name__ == "__main__":
            self.setGeometry(300, 300, *self.size)
            self.show()
    def setMinimumSize(self, x, y):
        self.size = [x, y]
        super().setMinimumSize(x, y)
    def send(self, pos):
        self.sender.emit(pos[0], pos[1])
    def mouseMoveEvent(self, event):
        x = event.pos().x()-self.size[0]//2
        y = event.pos().y()-self.size[1]//2
        self.pos = [x-self.shiftPos[0], y-self.shiftPos[1]]
        self.send(self.pos)
        self.update()
    def mousePressEvent(self, event):
        x, y = event.pos().x()-self.size[0]//2, event.pos().y()-self.size[1]//2
        self.shiftPos = [x, y]
        print(self.shiftPos)
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
        p.setOpacity(0.8)
        p.drawEllipse(self.pos[0]-self.R+2, self.pos[1]-self.R+2, self.R*2, self.R*2)
        
        p.setOpacity(1)
        p.setBrush(Qt.red)
        p.setPen(Qt.red)
        p.drawEllipse(self.pos[0]-self.R, self.pos[1]-self.R, self.R*2, self.R*2)
        
        p.setPen(Qt.black)
        p.setOpacity(0.5)
        p.drawText(self.size[0]//2-50, self.size[1]//2-20, str(self.pos))
if __name__ == "__main__":
    app = QApplication([])
    joy = Joy()
    sys.exit(app.exec_())