import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import time


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
rpm = 0

while True:

    with open('speed.txt', 'r') as file:
        content1 = file.read().strip()
        if content1:
            currunt_speed = int(content1)

    with open('temp.txt', 'r') as file:
        content2 = file.read().strip()
        if content2:
            currunt_temp = int(content2)

    # Update the Firebase database with new values
    db_ref.update({
        'speed': currunt_speed,
        'temp': currunt_temp,
        'fuel': fuel,
        'temperature': temperature
    })
    
    time.sleep(1)
