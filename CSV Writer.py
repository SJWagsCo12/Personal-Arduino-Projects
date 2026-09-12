"""
This program is used with the Arduino IDE to save the data from the IDE to a
csv file.
"""

import serial
import csv
import time

# Replace 'COM3' with your Arduino's COM port
serial_port = 'COM10'
baud_rate = 9600  # Match this with your Arduino sketch
output_file = 'output.csv'

# Open serial connection
ser = serial.Serial(serial_port, baud_rate)
print(f"Connected to {serial_port}")

# Open the CSV file for writing
with open(output_file, 'w', newline='') as csvfile:
    csvwriter = csv.writer(csvfile)
    
    # Write header (optional)
    csvwriter.writerow(["Timestamp", "Data"])

    try:
        while True:
            # Read a line from the serial port
            line = ser.readline().decode('utf-8').strip()
            
            # Write to the CSV file
            csvwriter.writerow([time.time(), line])
            print(f"Saved: {line}")
    except KeyboardInterrupt:
        print("Logging stopped.")
    finally:
        ser.close()