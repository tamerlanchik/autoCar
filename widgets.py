from PyQt5.QtWidgets import (QVBoxLayout, QHBoxLayout, QComboBox, QSplitter, QFormLayout, QScrollArea,  QMessageBox, QGroupBox,  QFrame)
from PyQt5.QtCore import pyqtSignal

class Widgets(QFrame):
    send =  pyqtSignal(str,  int)
    receive =  pyqtSignal(int)
    showMessage =  pyqtSignal(str)
    isActive = False
    pasp =  -1
    data =  0
    isConnectedFlag =  False
    def __init__(self,  pasp):
        super().__init__()
        self.pasp =  pasp
        self.setFrameShape(QFrame.StyledPanel)     
        self.create()  
        self.setMinimumHeight(400)
        self.setMinimumWidth(400)
        
    def create(self):
        self.mainWidgetLayout =  QVBoxLayout(self)
        self.setLayout(self.mainWidgetLayout)
    def sendData(self,  data):
        self.send.emit(data,  self.pasp)
    def receiveData(self):
        self.receive.emit(self.pasp)
        
