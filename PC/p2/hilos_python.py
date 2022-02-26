import threading

THREADS = 5
MAX_COUNT = 50000
EXPECTED = 250000

counter = 0

def thread():
    global counter
    print("Hilo {}".format(threading.current_thread().name))
    
    for i in range(MAX_COUNT):
        counter += 1

def main():
    threads = []
    
    for i in range(THREADS):
    # Create new threads
        t = threading.Thread(target=thread)
        threads.append(t)
        t.start() # start the thread
    # Wait for all threads to complete
    for t in threads:
        t.join()
        
    print("Valor del contador: {} Esperado: {}\n".format(counter, EXPECTED))
        
if __name__ == "__main__":
    main()
