import threading
import time
import random

# Buffer (shared resource)
buffer = []
buffer_lock = threading.Lock()

# Semaphores for synchronization
empty_slots = None
filled_slots = None

# A flag to indicate when to stop the threads   
stop_threads = False

# Producer function
def producer(id):
    while not stop_threads:
        item = random.randint(1, 100)          # Produce an item (random number)
        empty_slots.acquire()                  # Wait if buffer is full
        with buffer_lock:                      # Lock the buffer
            buffer.append(item)                # Add item to buffer
            print(f"Producer {id} produced item {item}. Buffer: {buffer}")
        filled_slots.release()                 # Signal that a new item is available
        time.sleep(random.uniform(0.1, 1.0))   # Simulate production time

# Consumer function
def consumer(id):
    while not stop_threads:
        filled_slots.acquire()                 # Wait if buffer is empty
        with buffer_lock:                      # Lock the buffer
            if buffer:                         # Check if buffer is not empty
                item = buffer.pop(0)           # Remove item from buffer
                print(f"Consumer {id} consumed item {item}. Buffer: {buffer}")
        empty_slots.release()                  # Signal that a slot is now available
        time.sleep(random.uniform(0.1, 1.5))   # Simulate consumption time

# Main function to start threads
def main():
    global empty_slots, filled_slots, stop_threads

    # Take input from user
    buffer_size = int(input("Enter buffer size: "))
    num_producers = int(input("Enter number of producers: "))
    num_consumers = int(input("Enter number of consumers: "))
    run_time = int(input("Enter run time in seconds: "))

    # Initialize semaphores based on buffer size
    empty_slots = threading.Semaphore(buffer_size)  # Slots available initially
    filled_slots = threading.Semaphore(0)           # No filled slots initially

    # Create and start producer and consumer threads
    producer_threads = [threading.Thread(target=producer, args=(i,)) for i in range(num_producers)]
    consumer_threads = [threading.Thread(target=consumer, args=(i,)) for i in range(num_consumers)]

    for t in producer_threads + consumer_threads:
        t.start()

    # Run the program for the specified time
    time.sleep(run_time)
    print("\nTime is up! Ending program.")

    # Set the flag to stop threads
    stop_threads = True

    # Wait for threads to finish
    for t in producer_threads + consumer_threads:
        t.join()  # Wait for threads to finish execution

    print("All threads have been terminated.")

# Run the program
if __name__ == "__main__":
    main()





# import threading
# import random
# import time

# buffer=[]
# buffer_lock=threading.Lock()

# empty_slots=None
# filled_slots=None


# stop_threads=False

# def producer(id):
# 	while not stop_threads:
# 		item=random.randint(1,100)
# 		empty_slots.acquire()
# 		with buffer_lock:
# 			buffer.append(item)
# 			print(f'producer {id} produced item {item}. Buffer:{buffer}')
# 			filled_slots.release()
# 			time.sleep(random.uniform(0.1,1.0))

# def consumer(id):
	
# 		while not stop_threads:
# 			filled_slots.acquire()
# 			with buffer_lock:
# 				if buffer:
# 					item=buffer.pop(0)
# 					print(f'consumer {id} consumed item {item}. Buffer:{buffer}')
# 			empty_slots.release()
# 			time.sleep(random.uniform(0.1,1.5))

# def main():
# 	global empty_slots,filled_slots,stop_threads
	
# 	buffer_size=int(input("enter size of buffer:"))
# 	num_producers=int(input("enter total number of producers:"))
# 	num_consumers=int(input("enter total number of consumers:"))
# 	run_time=int(input("enter run time in seconds:"))

# 	empty_slots=threading.Semaphore(buffer_size)
# 	filled_slots=threading.Semaphore(0)	
	
# 	producer_threads=[threading.Thread(target=producer, args=(i,)) for i in range(num_producers)]
# 	consumer_threads=[threading.Thread(target=consumer,args=(i,)) for i in range(num_consumers)]

# 	for t in producer_threads + consumer_threads:
# 		t.start()
# 	time.sleep(run_time)
# 	print("\ntime is up! ending program:")
	
# 	stop_threads=True
	
# 	for t in producer_threads + consumer_threads:
# 		t.join()
	
# 	print("all threads have been terminated.")
	
# if __name__=="__main__":
# 	main()
				






# import threading
# import time
# import random

# # Shared buffer and related variables
# buffer = []
# buffer_size = 5  # Max size of the buffer

# # Mutex for synchronizing access to the buffer
# mutex = threading.Lock()

# # Semaphore to control the number of items in the buffer
# empty_slots = threading.Semaphore(buffer_size)
# full_slots = threading.Semaphore(0)

# # Producer function
# def producer():
#     while True:
#         item = random.randint(1, 100)  # Produce an item (random number)
#         empty_slots.acquire()           # Wait for an empty slot
#         mutex.acquire()                 # Lock the buffer

#         buffer.append(item)             # Add item to buffer
#         print(f'Produced: {item}, Buffer: {buffer}')

#         mutex.release()                 # Release the lock
#         full_slots.release()            # Signal that there is a new item
#         time.sleep(random.uniform(0.1, 1))  # Sleep for a bit

# # Consumer function
# def consumer():
#     while True:
#         full_slots.acquire()            # Wait for an item
#         mutex.acquire()                 # Lock the buffer

#         item = buffer.pop(0)            # Remove item from buffer
#         print(f'Consumed: {item}, Buffer: {buffer}')

#         mutex.release()                 # Release the lock
#         empty_slots.release()           # Signal that there is an empty slot
#         time.sleep(random.uniform(0.1, 1))  # Sleep for a bit

# # Create producer and consumer threads
# producer_thread = threading.Thread(target=producer)
# consumer_thread = threading.Thread(target=consumer)

# # Start the threads
# producer_thread.start()
# consumer_thread.start()

# # Join threads (infinite loop here, so this line won't be reached)
# producer_thread.join()
# consumer_thread.join()
