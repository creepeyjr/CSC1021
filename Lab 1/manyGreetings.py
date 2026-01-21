from multiprocessing import *

def sayHi2(n):
    print("Hi", n, "from process", current_process().pid)

def manyGreetings():
    print("Hi from process", current_process().pid, "(main process)")
    
    name = str(input("Enter name : "))
    howMany = int(input("How many instances do you want : "))

    i = 0
    while i <= howMany:
        p = Process(target=sayHi2, args=(name,))
        p.start()

        i += 1
    
#execute
manyGreetings()