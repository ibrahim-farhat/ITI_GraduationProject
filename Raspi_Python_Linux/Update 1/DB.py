import tkinter as tk
import math
# from coooood_dasboard import speed, temp, gear

def create_gauge(canvas, x, y, radius, color, label, start_value, end_value):
    """
    Create a gauge on the canvas.

    Args:
        canvas (Tkinter.Canvas): The canvas to draw on.
        x (int): The x-coordinate of the center of the gauge.
        y (int): The y-coordinate of the center of the gauge.
        radius (int): The radius of the gauge.
        color (str): The color of the gauge outline.
        label (str): The label of the gauge.
        start_value (float): The start value of the gauge arc.
        end_value (float): The end value of the gauge arc.
    """
    # Draw gauge outline
    canvas.create_arc(x - radius, y - radius, x + radius, y + radius, start=start_value, extent=end_value - start_value,
                    style=tk.ARC, outline=color, width=10)
    # Draw gauge label
    canvas.create_text(x, y + radius + 25, text=label, font=("Arial", 12, "bold"), fill="red")

def draw_speed_arrow(canvas, x, y, radius, value, color):
    """
    Create a gauge on the canvas.

    Args:
        canvas (Tkinter.Canvas): The canvas to draw on.
        x (int): The x-coordinate of the center of the gauge.
        y (int): The y-coordinate of the center of the gauge.
        radius (int): The radius of the gauge.
        color (str): The color of the gauge outline.
        label (str): The label of the gauge.
        start_value (float): The start value of the gauge arc.
        end_value (float): The end value of the gauge arc.
    """
    angle = math.radians(225 - (value * 270))
    x1 = x + radius * 0.05 * math.cos(angle)
    y1 = y - radius * 0.05 * math.sin(angle)
    x2 = x + radius * 0.9 * math.cos(angle)
    y2 = y - radius * 0.9 * math.sin(angle)
    canvas.create_line(x1, y1, x2, y2, fill=color, width=3)

def draw_temp_arrow(canvas, x, y, radius, value, color, start_angle, end_angle):
    """
    Draw an arrow indicating the temperature on the canvas.

    Args:
        canvas (Tkinter.Canvas): The canvas to draw on.
        x (int): The x-coordinate of the center of the arrow.
        y (int): The y-coordinate of the center of the arrow.
        radius (int): The radius of the arrow.
        value (float): The value representing the temperature (0 to 1).
        color (str): The color of the arrow.
        start_angle (int): The start angle of the temperature sector.
        end_angle (int): The end angle of the temperature sector.
    """
    angle = math.radians(start_angle - (value * (start_angle - end_angle)))
    x1 = x + radius * 0.05 * math.cos(angle)
    y1 = y - radius * 0.05 * math.sin(angle)
    x2 = x + radius * 0.9 * math.cos(angle)
    y2 = y - radius * 0.9 * math.sin(angle)
    canvas.create_line(x1, y1, x2, y2, fill=color, width=3)

def draw_fuel_arrow(canvas, x, y, radius, value, color, start_angle, end_angle):
    """
    Draw an arrow indicating the fuel level on the canvas.

    Args:
        canvas (Tkinter.Canvas): The canvas to draw on.
        x (int): The x-coordinate of the center of the arrow.
        y (int): The y-coordinate of the center of the arrow.
        radius (int): The radius of the arrow.
        value (float): The value representing the fuel level (0 to 1).
        color (str): The color of the arrow.
        start_angle (int): The start angle of the fuel sector.
        end_angle (int): The end angle of the fuel sector.
    """
    angle = math.radians(start_angle - (value * (start_angle - end_angle)))
    x1 = x + radius * 0.05 * math.cos(angle)
    y1 = y - radius * 0.05 * math.sin(angle)
    x2 = x + radius * 0.9 * math.cos(angle)
    y2 = y - radius * 0.9 * math.sin(angle)
    canvas.create_line(x1, y1, x2, y2, fill=color, width=3)

def draw_speedometer_dashes(canvas, x, y, radius, recieved_speed):
    """
    Draw dashes on the speedometer indicating speed

    Args:
        canvas (Tkinter.Canvas): The canvas to draw on.
        x (int): The x-coordinate of the center of the speedometer.
        y (int): The y-coordinate of the center of the speedometer.
        radius (int): The radius of the speedometer.
        received_speed (int): The current speed value received.
    """
    for i in range(0, 141, 10):  # Draw dashes from 0 to 140 km/h, every 10 units
        angle = math.radians(225 - (i / 140 * 270))
        x1 = x + (radius - 10) * math.cos(angle)
        y1 = y - (radius - 10) * math.sin(angle)
        x2 = x + radius * math.cos(angle)
        y2 = y - radius * math.sin(angle)
        canvas.create_line(x1, y1, x2, y2, width=2, fill="red")

        label_x = x + (radius - 25) * math.cos(angle)
        label_y = y - (radius - 25) * math.sin(angle)
        canvas.create_text(label_x, label_y, text=str(i), font=("Arial", 8), fill="red")
        canvas.create_text((x - radius * 1.3)+265, (y) + 10, text="warning", font=("Arial", 12, "bold"), fill="red")
        canvas.create_text((x - radius * 1.3)+130, (y)+40, text=f"{recieved_speed} km/h", font=("Arial", 12, "bold"), fill="red")

def draw_temp_sector(canvas, x, y, radius,recieved_Temp):
    """
    Draw the temperature sector on the canvas.

    Args:
        canvas (tk.Canvas): The canvas on which to draw.
        x (int): The x-coordinate of the center of the sector.
        y (int): The y-coordinate of the center of the sector.
        radius (int): The radius of the sector.
        recieved_Temp (int): The received temperature value.
    """
    canvas.create_arc((x - radius)+55,(y - radius)-35, x + radius+55, y + radius-35, start=180, extent=90, style=tk.ARC, outline="red", width=10)
    canvas.create_text((x - radius) * 1.25, y-40, text="200", font=("Arial", 12, "bold"), fill="red")
    canvas.create_text((x - radius) * 1.53, y+52, text="0", font=("Arial", 12, "bold"), fill="red")
    canvas.create_text(x+30, y + radius +30, text="Temperature", font=("Arial", 12, "bold"), fill="red")
    canvas.create_text((x - radius * 1.3)+185, (y)-50, text=f"{recieved_Temp} C", font=("Arial", 12, "bold"), fill="red")


def draw_fuel_half_circle(canvas, x, y, radius,recieved_fuel):
    """
    Draw the fuel level half circle on the canvas.

    Args:
        canvas (tk.Canvas): The canvas on which to draw.
        x (int): The x-coordinate of the center of the half circle.
        y (int): The y-coordinate of the center of the half circle.
        radius (int): The radius of the half circle.
        recieved_fuel (int): The received fuel level value.
    """
    canvas.create_arc(x - radius, y - radius, x + radius, y + radius, start=0, extent=180, style=tk.ARC, outline="red", width=10)
    canvas.create_text((x + radius * 1.3)-198, y, text="FULL", font=("Arial", 12, "bold"), fill="red")
    canvas.create_text((x + radius * 1.4)-80, y, text="EMPTY", font=("Arial", 12, "bold"), fill="red")
    canvas.create_text(x, (y - radius * 1.4)+20, text="1/2", font=("Arial", 12, "bold"), fill="red")
    canvas.create_text(x, y + radius , text="Fuel Level", font=("Arial", 12, "bold"), fill="red")
    canvas.create_text(x+5, y +10, text=f"{recieved_fuel} L", font=("Arial", 12, "bold"), fill="red")


def draw_gear(canvas, x, y):
    """
    Draw the gear indicator on the canvas.

    Args:
        canvas (tk.Canvas): The canvas on which to draw.
        x (int): The x-coordinate of the gear indicator.
        y (int): The y-coordinate of the gear indicator.
    """
    if recieved_gear == 1:
        canvas.create_text(x, y , text="P", font=("Arial", 25, "bold"), fill="red")
    elif recieved_gear == 2:
        canvas.create_text(x, y , text="R", font=("Arial", 25, "bold"), fill="red")
    elif recieved_gear == 3:
        canvas.create_text(x, y , text="N", font=("Arial", 25, "bold"), fill="red")
    elif recieved_gear == 4:
        canvas.create_text(x, y , text="D", font=("Arial", 25, "bold"), fill="red")


def update_values():
    """
    Update the values displayed on the canvas.

    This function reads the received values from files, performs necessary calculations,
    and redraws the canvas based on the updated values.

    Args:
        None
    """
    global speed, recieved_speed, temperature, recieved_Temp,recieved_fuel, fuel,recieved_gear
    with open('speed.txt', 'r') as file:
        content1 = file.read().strip()
        if content1:
            recieved_speed = int(content1)
    with open('temp.txt', 'r') as file:
        content2 = file.read().strip()
        if content2:
            recieved_Temp = int(content2)
            
    # some equations to manage the movment of arrows (speed example : 0-140 => 0-1 )
    speed = recieved_speed * (1/140)
    temperature = recieved_Temp * (1/200)
    fuel = recieved_fuel * (1/50)  
    
    canvas.delete("all")
    canvas.config(bg="black")  # Set canvas background to black

    # Draw Speedometer
    create_gauge(canvas, 150, 150, 100, "red", "Speed", 225, -135)  # Extending the range till 140 km/h
    draw_speedometer_dashes(canvas, 150, 150, 100, recieved_speed)
    draw_speed_arrow(canvas, 150, 150, 100, speed, "red")

    # Draw Temperature meter
    draw_temp_sector(canvas, 400, 150, 100,recieved_Temp)
    draw_temp_arrow(canvas, 450, 110, 100, temperature, "red", 270, 180)  # Adjust start and end angles

    # Draw Fuel Level gauge
    draw_fuel_half_circle(canvas, 650,180, 100,recieved_fuel)
    draw_fuel_arrow(canvas, 650, 180, 100, fuel, "red", 0, 180)  # Adjust start and end angles

    # Draw Gear_dir
    draw_gear(canvas,300,30)

    # Schedule the next update after 500 milliseconds (0.5 second)
    root.after(50, update_values)


# main
root = tk.Tk()
root.title("CAR DASHBOARD 🚗")
root.geometry("800x300")
root.resizable(0,0)

canvas = tk.Canvas(root, width=800, height=300, bg="black")  # Set initial canvas background to black
canvas.pack()

#initialiezed the data variables
recieved_gear = 0
recieved_speed =0
recieved_Temp = 0
recieved_fuel = 0

# Call the "update_values" for the first time
update_values()

# main loop
root.mainloop()
