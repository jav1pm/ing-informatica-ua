# taskset -c 0 python3 Lamport.py

import threading

choosing = [False, False, False, False]
number = [0, 0, 0, 0]

THREADS = 4
MAX_COUNT = 10000

counter = 0

def entry_critical_section(i):
    global choosing
    global number
    choosing[i] = True
    number[i] = 1 + max(number)
    choosing[i] = False
    for j in range(THREADS):
        while choosing[j]:
            pass
        while number[j] > 0 and (number[j] < number[i] or (number[j] == number[i] and j < i)):
            pass


def critical_section(i):
    global counter
    counter += 1

def exit_critical_section(i):
    global number
    number[i] = 0

def thread(i):
    for j in range(MAX_COUNT//THREADS):
        entry_critical_section(i)
        critical_section(i)
        exit_critical_section(i)

def main():
    threads = []
    for i in range(THREADS):
        # Create new threads
        t = threading.Thread(target=thread, args=(i,))
        threads.append(t)
        t.start() # start the thread

    # Wait for all threads to complete
    for t in threads:
        t.join()

    print("Counter value: {} Expected: {}\n".format(counter, MAX_COUNT))


if __name__ == "__main__":
    main()