
import sys
import os
import os.path
import PySide
from PySide.QtCore  import *
from PySide.QtGui   import *

import pirate_control
from pirate_control.views       import *
from pirate_control.interface   import *
from pirate_control.controller  import *

windowWidth     = 800
windowHeight    = 600

# ------------------------------------------------------------------------------

class PcoControlSection(QWidget):
    def __init__(self, controller, parent = None):
        QWidget.__init__(self, parent)
        self.setFixedSize(windowWidth, windowHeight)

        noteGroup = QGroupBox("Note", self)
        noteGroup.setContentsMargins(0, 10, 0, 0)
        noteLayout = QFormLayout()
        noteGroup.setLayout(noteLayout)

        noteControl = NoteControlView(self)
        noteControl.slider.valueChanged.connect(controller.sendFineNote)
        noteLayout.addRow("Note", noteControl)

        # ----------------------------------------------------------------------
        # Misc

        miscGroup = QGroupBox("Misc settings", self)
        miscGroup.setContentsMargins(0, 10, 0, 0)
        miscLayout = QFormLayout()
        miscGroup.setLayout(miscLayout)

        globalDetune = ContinuousControlView(miscGroup)
        globalDetune.setRange(-500, 500, 1)
        globalDetune.slider.valueChanged.connect(controller.sendGlobalDetune)
        miscLayout.addRow("Tuning", globalDetune)

        sync = QCheckBox(miscGroup)
        sync.toggled.connect(controller.sendEnableSync)
        miscLayout.addRow("Sync", sync)

        # ----------------------------------------------------------------------
        # External modulation

        modGroup = QGroupBox("External modulation", self)
        modGroup.setContentsMargins(0, 20, 0, 0)
        modLayout = QFormLayout()
        modGroup.setLayout(modLayout)

        modOnOff = QCheckBox(modGroup)
        modOnOff.setCheckState(Qt.Checked)
        modOnOff.toggled.connect(controller.sendEnableModulation)
        modLayout.addRow("On/Off", modOnOff)

        modRange = ContinuousControlView(modGroup)
        modRange.setRange(0, 48, 1)
        modRange.slider.setValue(12)
        modRange.slider.valueChanged.connect(controller.sendModulationRangeSemi)
        modLayout.addRow("Range", modRange)

        # ----------------------------------------------------------------------
        # Portamento

        portGroup = QGroupBox("Portamento", self)
        portGroup.setContentsMargins(0, 20, 0, 0)
        portLayout = QFormLayout()
        portGroup.setLayout(portLayout)

        portOnOff = QCheckBox(portGroup)
        portOnOff.toggled.connect(controller.sendEnablePortamento)
        portLayout.addRow("On/Off", portOnOff)

        portTrigger = QPushButton("", portGroup)
        portTrigger.pressed.connect(controller.triggerPortamento)
        portLayout.addRow("Trigger", portTrigger)

        portMode = QComboBox(portGroup)
        portMode.addItem("Linear",      0)
        portMode.addItem("Exponential", 1)
        portMode.addItem("Logarithmic", 2)
        portMode.currentIndexChanged.connect(controller.sendPortamentoMode)
        portLayout.addRow("Mode", portMode)

        portAmount = ContinuousControlView(portGroup)
        portAmount.setRange(0, 0x3fff, 1)
        portAmount.slider.valueChanged.connect(controller.sendPortamentoAmount)
        portLayout.addRow("Amount", portAmount)

        # ----------------------------------------------------------------------
        # Vibrato

        vibratoGroup = QGroupBox("Vibrato", self)
        vibratoGroup.setContentsMargins(0, 20, 0, 0)
        vibratoLayout = QFormLayout()
        vibratoGroup.setLayout(vibratoLayout)

        # vibratoOnOff = QCheckBox(vibratoGroup)
        # vibratoOnOff.toggled.connect(controller.sendEnableVibrato)
        # vibratoLayout.addRow("On/Off", vibratoOnOff)

        vibratoSpeed = ContinuousControlView(vibratoGroup)
        vibratoSpeed.setRange(0, 0x3fff, 1)
        vibratoSpeed.slider.valueChanged.connect(controller.sendVibratoSpeed)
        vibratoLayout.addRow("Speed", vibratoSpeed)

        vibratoAmount = ContinuousControlView(vibratoGroup)
        vibratoAmount.setRange(0, 0x3fff, 10)
        vibratoAmount.slider.valueChanged.connect(controller.sendVibratoAmount)
        vibratoLayout.addRow("Amount", vibratoAmount)

        vibratoWave = QComboBox(vibratoGroup)
        vibratoWave.addItem("Sine",     0)
        vibratoWave.addItem("Square",   1)
        vibratoWave.addItem("Saw",      2)
        vibratoWave.addItem("Ramp",     3)
        vibratoWave.addItem("Triange",  4)
        vibratoWave.currentIndexChanged.connect(controller.sendVibratoWaveform)
        vibratoLayout.addRow("Waveform", vibratoWave)

        # ----------------------------------------------------------------------
        # PWM

        pwmGroup = QGroupBox("PWM", self)
        pwmGroup.setContentsMargins(0, 20, 0, 0)
        pwmLayout = QFormLayout()
        pwmGroup.setLayout(pwmLayout)

        # pwmOnOff = QCheckBox(pwmGroup)
        # pwmOnOff.toggled.connect(controller.sendEnablePwm)
        # pwmLayout.addRow("On/Off", pwmOnOff)

        pwmBaseLevel = ContinuousControlView(pwmGroup)
        pwmBaseLevel.setRange(-32767, 32767, 1)
        pwmBaseLevel.slider.setValue(0x1fff);
        pwmBaseLevel.slider.valueChanged.connect(controller.sendPwmBaseLevel)
        pwmLayout.addRow("Base level", pwmBaseLevel)

        pwmSpeed = ContinuousControlView(pwmGroup)
        pwmSpeed.setRange(0, 0x3fff, 1)
        pwmSpeed.slider.valueChanged.connect(controller.sendPwmSpeed)
        pwmLayout.addRow("Speed", pwmSpeed)

        pwmAmount = ContinuousControlView(pwmGroup)
        pwmAmount.setRange(0, 0x3fff, 10)
        pwmAmount.slider.valueChanged.connect(controller.sendPwmAmount)
        pwmLayout.addRow("Amount", pwmAmount)

        pwmWave = QComboBox(pwmGroup)
        pwmWave.addItem("Sine",     0)
        pwmWave.addItem("Square",   1)
        pwmWave.addItem("Saw",      2)
        pwmWave.addItem("Ramp",     3)
        pwmWave.addItem("Triange",  4)
        pwmWave.currentIndexChanged.connect(controller.sendPwmWaveform)
        pwmLayout.addRow("Waveform", pwmWave)


        # ----------------------------------------------------------------------
        # Master layout

        masterLayout = QVBoxLayout()
        masterLayout.addWidget(noteGroup)

        doublePanelLayout = QHBoxLayout()
        doublePanelContainer = QWidget(self)
        doublePanelContainer.setLayout(doublePanelLayout)
        masterLayout.addWidget(doublePanelContainer)

        leftLayout      = QVBoxLayout()
        rightLayout     = QVBoxLayout()
        leftContainer   = QWidget(self)
        rightContainer  = QWidget(self)
        leftContainer.setLayout(leftLayout)
        rightContainer.setLayout(rightLayout)
        doublePanelLayout.addWidget(leftContainer)
        doublePanelLayout.addWidget(rightContainer)

        leftLayout.addWidget(miscGroup)
        leftLayout.addWidget(modGroup)
        leftLayout.addWidget(portGroup)
        rightLayout.addWidget(vibratoGroup)
        rightLayout.addWidget(pwmGroup)

        self.setLayout(masterLayout)

# ------------------------------------------------------------------------------

class SettingsWindow(QMainWindow):
    def __init__(self, pirateInterface, parent = None):
        QMainWindow.__init__(self, parent)
        self.setWindowTitle("Settings")
        self.setFixedSize(300, 30)
        self.pirateInterface = pirateInterface

        self.textBox = QLineEdit(self.pirateInterface.port, self)
        self.textBox.setGeometry(5, 5, 200, 20)
        button = QPushButton("Open", self)
        button.setGeometry(210, 5, 85, 20)
        button.pressed.connect(self.handleButtonClicked)

    def handleButtonClicked(self):
        if self.pirateInterface.open(self.textBox.text()):
            self.hide()

# ------------------------------------------------------------------------------

class MainWindow(QMainWindow):
    def __init__(self, controller, pirateInterface):
        QMainWindow.__init__(self, None)
        self.setWindowTitle("PCO Control Panel")
        self.setFixedSize(windowWidth, windowHeight)

        view = PcoControlSection(controller, self)
        self.settings = SettingsWindow(pirateInterface)

        settingsAction = QAction(QIcon('exit.png'), '&Settings', self)
        settingsAction.setShortcut('Cmd+,')
        settingsAction.setStatusTip('Settings')
        settingsAction.triggered.connect(self.settings.show)

        menubar = self.menuBar()
        editMenu = menubar.addMenu('&Edit')
        editMenu.addAction(settingsAction)

# ------------------------------------------------------------------------------

app = QApplication(sys.argv)

pirate = BusPirateInterface("/dev/tty.usbserial-AE01J4WM", 115200)

pcoController = PcoController(pirate)

window = MainWindow(pcoController, pirate)

window.show()
returnCode = app.exec_()
pirate.close()
sys.exit(returnCode)

