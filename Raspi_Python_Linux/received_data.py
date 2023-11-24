import sys

for line in sys.stdin:
    data_values = line.strip().split(" ")
    # Extract the data values
    ECU_ID = data_values[2]

    # Check the ID
    # Store the received sensor data
    if ECU_ID == "7D0":
        recieved_speed = int(data_values[-1], 16)
        with open('speed.txt', 'w') as file:
            file.write(str(recieved_speed))
        print(f"Received speed: {recieved_speed}")
    elif ECU_ID == "5EB":
        recieved_Temp = int(data_values[-1], 16)
        with open('temp.txt', 'w') as file:
            file.write(str(recieved_Temp))
        print(f"Received temp: {recieved_Temp}")
