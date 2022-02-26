import threading

states = [False, False]

THREADS = 2
MAX_COUNT = 100000

counter = 0

def entry_critical_section(i):
    global states
    states[i] = True
    while states[(i+1)%2]:
      pass

def critical_section(i):
    global counter
    counter += 1

def exit_critical_section(i):
    global states
    states[i] = False

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