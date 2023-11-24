import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import time


def update_firebase_data():
    """
    Continuously updates the sensor data to a Firebase Realtime Database.

    This function reads the sensor data from local files and updates the corresponding
    values in a Firebase Realtime Database. The data is retrieved from files 'speed.txt',
    'temp.txt', and 'ldr.txt'. The updated values are stored under specific keys in the
    Firebase database.

    Args:
        None

    Returns:
        None
    """
    # Initialize Firebase
    cred = credentials.Certificate("key.json")
    firebase_admin.initialize_app(cred, {
        'databaseURL': 'https://can-hegazy-default-rtdb.firebaseio.com/'
    })

    # Create a Firebase database reference
    db_ref = db.reference('/car_data')  

    # Initialize variables
    currunt_speed = 0
    currunt_temp = 0
    fuel = 0
    currunt_ldr = 0

    while True:

        with open('speed.txt', 'r') as file:
            content1 = file.read().strip()
            if content1:
                currunt_speed = int(content1)

        with open('temp.txt', 'r') as file:
            content2 = file.read().strip()
            if content2:
                currunt_temp = int(content2)
                
        with open('ldr.txt', 'r') as file:
            content3 = file.read().strip()
            if content3:
                currunt_ldr = int(content3)

        # Update the Firebase database with new values
        db_ref.update({
            '01 Speed': currunt_speed,
            '02 temprature': currunt_temp,
            '03 fuel_Level': fuel,
            '04 light_Intenisty': currunt_ldr
        })
        
        time.sleep(1)

# Call the function to start updating the Firebase data
update_firebase_data()
