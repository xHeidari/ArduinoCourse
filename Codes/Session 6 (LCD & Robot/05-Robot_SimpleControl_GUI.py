import serial
import tkinter as tk
from tkinter import ttk

# Set your Arduino COM port here
arduino = serial.Serial('COM13', 9600)  # Change 'COM3' to your port

def send_command():
    b = base_scale.get()
    s = shoulder_scale.get()
    e = elbow_scale.get()
    command = f"B{b} S{s} E{e}\n"
    arduino.write(command.encode())

# GUI Setup
root = tk.Tk()
root.title("Robotic Arm Controller")

ttk.Label(root, text="Base Rotation").pack()
base_scale = tk.Scale(root, from_=0, to=180, orient=tk.HORIZONTAL, command=lambda x: send_command())
base_scale.set(90)
base_scale.pack()

ttk.Label(root, text="Shoulder Angle").pack()
shoulder_scale = tk.Scale(root, from_=0, to=180, orient=tk.HORIZONTAL, command=lambda x: send_command())
shoulder_scale.set(90)
shoulder_scale.pack()

ttk.Label(root, text="Elbow Angle").pack()
elbow_scale = tk.Scale(root, from_=0, to=180, orient=tk.HORIZONTAL, command=lambda x: send_command())
elbow_scale.set(90)
elbow_scale.pack()

root.mainloop()
