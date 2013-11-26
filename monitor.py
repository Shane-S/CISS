import os
from pyinotify import WatchManager, Notifier, ThreadedNotifier, EventsCodes, ProcessEvent

# The class that will be passed into the watcher to be called on triggered events
class PTmp(ProcessEvent):
    def process_IN_CREATE(self, event):
        print "Create: %s" %  event.name#os.path.join(event.path, event.name)
        if event.name == "0"
        	LED_OFF()
        if event.name == "1"
        	LED_RED()
        if event.name == "2"
        	LED_BLUE()
        if event.name == "3"
        	LED_GREEN()

    #def process_IN_DELETE(self, event):
    #    print "Remove: %s" %  os.path.join(event.path, event.name)

# create the watch manager
wm = WatchManager()

#create the mask that determines which events to watch for
mask = EventsCodes.IN_CREATE 

#create the notifier
notifier = Notifier(wm, PTmp())

# 	the watch to be added to the watch
# 	'/[monitored directory]'
# 	rec=False means no monitoring of nested dirs, can be set true
#	wdd is used for removing 
wdd = wm.add_watch('/tmp', mask, rec=False)

LEDSETUP()

while True:  # loop forever
    # process the queue of events as explained above
    notifier.process_events()
    if notifier.check_events():
        # read notified events and enqeue them
        notifier.read_events()
    # you can do some tasks here...