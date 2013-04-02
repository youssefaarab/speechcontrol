from PyQt4 import QtCore, QtDBus
from PyQt4.QtDBus import QDBusMessage, QDBusConnection

DBUS_SERVICE = "org.sii.speechcontrol"
DBUS_OBJECT_PATH = "/SpeechRecognizer"
DBUS_INTERFACE = "org.sii.speechcontrol.SpeechRecognition"

class RecognitionInterface(QtDBus.QDBusAbstractInterface):
	def __init__(self, service, path, connection, parent=None):
		super().__init__(service, path, DBUS_INTERFACE, connection, parent)

	def oneUtterance(self):
		reply = self.call("oneUtterance")
		if reply.isValid():
			return reply.arguments()[0]
		else:
			return ""

    def oneUtteranceAsync(self):
        self.callAsync("oneUtterance")

	def oneUtteranceTo(self, receiver, method, errMethod):
		self.callWithCallback("oneUtterance", [], receiver, method, errMethod)

class AsrFacility(QtCore.QObject):
	def __init__(self):
		super().__init__()
		self.recogIface = RecognitionInterface(DBUS_SERVICE, DBUS_OBJECT_PATH, 
			QtDBus.QDBusConnection.sessionBus(), self)

	def requestUtterance(self):
		"""Request one utterance from SpeechControl

			This call is a blocking one, use it if you need the text immediately.
		"""
		return self.recogIface.oneUtterance()

    def requestUtteranceAsync(self):
        """Request one utterance from SpeechControl

            This call is asynchronous, to use it one has to connect the signal
            ... to a slot responsible for handling the text.
        """
        #TODO: Connect proper signals
        self.recogIface.oneUtteranceAsync()
