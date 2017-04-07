import PySide
from PySide.QtCore  import *
from PySide.QtGui   import *

# ------------------------------------------------------------------------------

class ContinuousControlView(QWidget):
    def __init__(self, parent = None):
        QWidget.__init__(self, parent)
        self.slider = QSlider(Qt.Horizontal, self)
        self.slider.show()
        self.slider.setFixedWidth(150)
        self.spinBox = QSpinBox(self)
        self.spinBox.setFixedWidth(70)
        self.spinBox.show()
        self.layout = QHBoxLayout()
        self.layout.addWidget(self.slider)
        self.layout.addWidget(self.spinBox)
        self.setLayout(self.layout)
        self.slider.valueChanged.connect(self.spinBox.setValue)
        self.spinBox.valueChanged.connect(self.slider.setValue)
        
    def sizeHint(self):
        return QSize(225, 30)
            
    def contentMargins(self):
        return QMargins(0, 0, 0, 0)            
            
    def setRange(self, min, max, increment):
        self.slider.setRange(min, max)
        self.slider.setTickInterval(increment)
        self.slider.setSingleStep(increment)
        self.spinBox.setRange(min, max)
        self.spinBox.setSingleStep(increment)

# ------------------------------------------------------------------------------

class NoteControlView(ContinuousControlView):
    def __init__(self, parent = None):
        ContinuousControlView.__init__(self, parent)
        self.slider.setFixedWidth(500)
        checkbox = QCheckBox(self)
        checkbox.toggled.connect(self.checkBoxToggled)
        self.layout.addWidget(checkbox)
        self.setRange(0, 12800, 1)


    def checkBoxToggled(self, state):
        if state:
            print "Coarse mode"
            self.setRange(0, 12800, 100)
        else:
            print "Fine mode"
            self.setRange(0, 12800, 1)
