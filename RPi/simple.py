import serial

# 115200, 8, N, 1
ser = serial.Serial('/dev/serial0', 115200, timeout=None,
                    parity=serial.PARITY_NONE)
print(ser.name)
ser.write(b'2048,-2048\r\n')

ser.close()
