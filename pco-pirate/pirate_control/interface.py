
import os
import os.path
from pyBusPirateLite.SPI import *

class BusPirateInterface:
    def __init__(self, port, baud):
        self.port = port
        self.baud = baud
        self.impl = None
        self.ready = False
        
        if os.path.exists(self.port):
            try:
                self.open(self.port)
            except:
                print "Could not open port."

    def open(self, port):
        if not os.path.exists(self.port):
            return False
    
        self.port = port
        impl = SPI(self.port, self.baud)
        
        if not impl.BBmode():
            print "Failed to enter binary mode."
            return False
        if not impl.enter_SPI():
            print "Failed to enter SPI mode."
            return False
        if not impl.cfg_pins(PinCfg.POWER | PinCfg.CS | PinCfg.AUX):
            print "Failed to set SPI peripherals."
            return False
        if not impl.set_speed(SPISpeed._1MHZ):
            print "Failed to set SPI Speed."
            return False
        if not impl.cfg_spi(SPICfg.OUT_TYPE):
            print "Failed to set SPI configuration."
            return False
        impl.timeout(0.2)
        self.impl = impl
        return True      

    def close(self):
        if not self.impl:
            return None
        self.impl.reset()

    def send(self, data):
        if not self.impl:
            return None
            
        try:
            self.impl.bulk_trans(len(data), data)
            #for i in range(len(data)):
            #    print "Sending 0x%02X" % data[i]
        except serial.serialutil.SerialException:
            self.open(self.port)
        
