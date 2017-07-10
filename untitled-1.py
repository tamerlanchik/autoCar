from PyQt5.QtCore import Qt, QPoint
from PyQt5.QtWidgets import QWidget, QVBoxLayout, QPushButton, QGroupBox, QCheckBox, QApplication
from PyQt5.QtGui import QPainter, QBrush, QPen, QPalette
import sys
#from dictionary import T
class DisplayImg(QWidget):
    
    def __init__(self, size = 300, numb = 2):
        super().__init__()
        self.setFixedHeight(size+1)
        self.setFixedWidth(size+1)
        Pal=QPalette()
        Pal.setColor(QPalette.Background, Qt.white)
        self.setAutoFillBackground(True)
        self.setPalette(Pal)
        self.numb=numb
        self.doesShowWayFlag=False
        self.doesShowCirclesFlag=False
        self.doesShowLegsFlag=False
        

    
    def createControls(self):
        self.mainBox=QVBoxLayout(self)
        self.mainGroupBox=QGroupBox(self)
        
        self.doesShowWayCheck=QCheckBox('d', self)
        self.doesShowWayCheck.stateChanged[int].connect(self.doesDrawWays)
        
        self.isShowCircles=QCheckBox('s', self)
        self.isShowCircles.stateChanged[int].connect(self.doesDrawCircles)
        
        self.isShowLegs=QCheckBox('d', self)
        self.isShowLegs.stateChanged[int].connect(self.doesDrawLegs)
        
        self.clearButton=QPushButton('f', self)
        self.clearButton.clicked.connect(self.clearDisplay)
        
        self.mainBox.addWidget(self.doesShowWayCheck)
        self.mainBox.addWidget(self.isShowCircles)
        self.mainBox.addWidget(self.isShowLegs)
        self.mainBox.addWidget(self.clearButton)
        self.mainBox.addStretch(1)
        
        self.mainGroupBox.setLayout(self.mainBox)
        return self.mainGroupBox
        
    def paintEvent(self, e):
        painter=QPainter(self)
        painter.begin(self)
        self.drawGrid(painter)
        #self.showCircles()
        painter.end()
        
    def drawGrid(self, painter):
        painter.setPen(Qt.gray)
        for i in range(0, self.width()+2, 10):
            painter.drawLine(i, 0, i, self.height())
        for i in range(0, self.height()+2, 10):
            painter.drawLine(0, i, self.width(), i)
            
        painter.setPen(Qt.black)
        if self.numb==0:
            painter.drawLine(self.width()//2, 0, self.width()//2, self.height())
            
            painter.drawLine(0, self.height()-20, self.width(), self.height()-20)
        elif self.numb==1:
            painter.drawLine(self.width()-21, 0, self.width()-21, self.height())
            painter.drawLine(0, self.height()//2, self.width(), self.height()//2)
            
        if self.doesShowCirclesFlag==True:
            self.showCircles(painter)
            
    def showCircles(self, painter):
        painter.setPen(Qt.red)
        painter.setBrush(Qt.red)
        painter.drawEllipse(QPoint(self.width()-21, self.height()//2), 2, 2) 
        painter.setBrush(Qt.NoBrush)
        painter.drawEllipse(QPoint(self.width()-21, self.height()//2), 100, 100)
        
    #----SLOTS----------------------
    def doesDrawCircles(self, flag):
        self.doesShowCirclesFlag=bool(flag)
        self.update()
    def doesDrawWays(self, flag):
        self.doesShowWayFlag=bool(flag)
        self.update()
    def doesDrawLegs(self, flag):
        self.doesShowLegsFlag=bool(flag)
        self.update()
    def clearDisplay(self):
        self.doesShowWayFlag=False
        self.update()
        
if __name__ == "__main__":
    app = QApplication([])
    wind = DisplayImg()
    wind.setGeometry(100, 100, 300, 300)
    wind.show()
    sys.exit(app.exec_())