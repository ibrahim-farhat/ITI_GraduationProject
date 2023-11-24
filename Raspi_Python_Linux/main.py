import multiprocessing
import subprocess

# Function to run the Dashboard
def run_Dash_Board():
    subprocess.run(['python', 'DB.py'])

# Function to run the received data
def run_rec_data():
    subprocess.run(['python', 'received_data.py'])
    
# Function to run the server script
def run_server():
    subprocess.run(['python', 'server.py'])

if __name__ == '__main__':
    # Create two processes to run the scripts concurrently
    Dashboard_process = multiprocessing.Process(target=run_Dash_Board)
    received_process = multiprocessing.Process(target=run_rec_data)
    server_process = multiprocessing.Process(target=run_server)

    # Start the processes
    Dashboard_process.start()
    received_process.start()
    server_process.start()

    # Wait for the processes to finish
    Dashboard_process.join()
    received_process.join()
    server_process.join()
