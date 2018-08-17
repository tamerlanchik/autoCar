from PyQt5.QtWidgets import (QMainWindow, QDesktopWidget,  QWidget, QLCDNumber, QSlider,
    QVBoxLayout, QApplication, QLabel, QHBoxLayout, QComboBox, QSplitter,  QAction, QFormLayout,  QInputDialog, QMessageBox, QPushButton,  QGroupBox,  QCheckBox,  QLineEdit,  QFrame,  QDial)
from PyQt5.QtGui import QIcon, QColor,  QPalette,  QImage,  QPixmap
import os
from PyQt5.QtCore import Qt,  QRect,  pyqtSignal,  QSignalMapper, QSize
import sys
import time
from multiprocessing import Process
import os
import subprocess
import sys
from app1 import Window
#from communicator import Communicator

class Main(QMainWindow):
    def __init__(self):
        super().__init__()
        print('s')
        #self.statusBar().showMessage('Hello')
        self.setGeometry(100,  100,  200,  200)
        #self.show()
        self.initApp()
    def initApp(self):
        pipes =  []
        self.wind =  os.path.join(os.path.dirname(__file__), "./app1.py")
        self.comm =  os.path.join(os.path.dirname(__file__), "./communicator.py")
        #self.window =  Window()
        #self.comm =  Communicator()
        #print(self.window.sendo[int,  int].connect(self.s))
        '''p2 =  Process (target =  comm)
        p2.start()'''
        command1 =  [sys.executable,  self.wind]
        pipe1 =  subprocess.Popen(command1,  stdin =  subprocess.PIPE)
        
        #pipe1.wait()
        
        command2 =  [sys.executable,  self.comm]
        pipe2 =  subprocess.Popen(command2,  stdin =  subprocess.PIPE)
    
        #pipe2.wait()        
    def s(self,  a):
        print(a)
        #self.statusBar().showMessage(str(a))

if __name__ == "__main__":
    app = QApplication([])
    main = Main()
    sys.exit(app.exec_())