import sys

def process_sensor_data():
    """
    Process the received sensor data from stdin.

    This function reads lines from the standard input and extracts the received sensor data.
    The extracted data is then stored in separate files based on the ECU ID.

    Args:
        None
    """
    for line in sys.stdin:
        data_values = line.strip().split(" ")
        
        if len(data_values) < 8:
            print("INVALID FRAME !!")
        else:
            # Extract the data values
            ECU_ID = data_values[2]

            # Check the ID
            # Store the received sensor data
            if ECU_ID == "7D0":
                recieved_speed = int(data_values[-1], 16)
                with open('speed.txt', 'w') as file:
                    file.write(str(recieved_speed))
                print(f"Received speed: {recieved_speed}")
            elif ECU_ID == "3B8":
                recieved_Temp = int(data_values[-1], 16)
                with open('temp.txt', 'w') as file:
                    file.write(str(recieved_Temp))
                print(f"Received temp: {recieved_Temp}")
            elif ECU_ID == "7A0":
                if len(data_values) < 9:
                    print("INVALID FRAME !!")
                else:
                    recieved_LDR = int(data_values[-1], 16) << 8
                    recieved_LDR |= int(data_values[-2], 16)
                    with open('ldr.txt', 'w') as file:
                        file.write(str(recieved_LDR))
                    print(f"Received LDR: {recieved_LDR}")

# Call the function to start processing the sensor data
process_sensor_data()
