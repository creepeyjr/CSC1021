from multiprocessing import *

def sayHi():
    print("Hi from process", current_process().pid, "(child process 1)")


def procEx2():
    print("Hi from process", current_process().pid, "(parent process)")

    process1 = Process(target=sayHi, args=())
    process2 = Process(target=sayHi, args=())
    process3 = Process(target=sayHi, args=())

    process1.start()
    process2.start()
    process3.start()

# Execute function
procEx2()

# Unused code
'''
def procEx():
    print("Hi from process", current_process().pid, "(parent process)")

    otherProc = Process(target=sayHi, args=())
    otherProc.start()

# execute
procEx()

'''
# My personal attempt, broke D.R.Y. rule (Do Not Repeat) without realising. 
'''
from multiprocessing import *

def sayHi():
    print("Hi from process", current_process().pid, "(child process 1)")

def sayHello():
    print("Hello from process 3", current_process().pid, "(child process 2)")

def procEx():
    print("Hi from process", current_process().pid, "(parent process)")

    otherProc = Process(target=sayHi, args=())
    otherProc.start()

    firstProc = Process(target=sayHello, args=())
    firstProc.start()

# execute
procEx()
'''