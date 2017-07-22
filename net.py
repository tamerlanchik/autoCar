from PyQt5.QtWidgets import QWidget
from PyQt5.QtCore import pyqtSignal
from serial import Serial
from data import Data
d = Data()
class Net(QWidget):
    isConnectedFlag = False
    send =  pyqtSignal(str)
    serial =  Serial()
    def __init__(self):
        super().__init__()
    def sendData(self,  data):
        print(data)
        if 'connect' in data:
            port,  speed =  data.replace('connect',  '').split('/')
            if port ==  d.portList[0]:
                try:
                    self.serial.close()
                    self.isConnectedFlag =  False
                    return 'Disconnected'
                except:
                    return 'Cannot disconnect'                
            for i in range(3):
                try:
                    self.serial = Serial(port,  speed,  dsrdtr = 0, timeout = 10)
                    #self.serial.open()
                    if self.serial.isOpen() ==  True:
                        self.isConnectedFlag =  True
                        #self.serial.open()
                    return 'Connected'
                except:
                    pass
            else: return 'Cannot connect'
        elif 'move' in data:
            rot, gaz =  data.replace('move',  '').split('/')
            message =  bytes( (rot +  '/' + gaz + '$').encode('utf-8'))
            try:
                self.serial.write(message)
                return '<font color ="green">Data sent</font'
            except:
                return '<font color = "red">Cannot send</font>'
        elif "rescan" in data:
            try:
                self.serial.write(bytes('@'.encode('utf-8')))
                return "Starting rescan"
            except:
                return "Cannot rescan"
    def receiveData(self):
        try:
            if self.isConnectedFlag ==  True:
                ans =  ''
                if self.serial.inWaiting() > 0:
                    print("Adding data" + str(self.serial.inWaiting()))
                    ans += str(self.serial.readline())
                if ans !=  '':
                    if '%' in ans:
                        return "Stop"
                    else:
                        print("Sending data")
                        return ans[2:]
            else:
                return "error"
        except:
            print("Error in receiveData (Net)")
            
        
                
