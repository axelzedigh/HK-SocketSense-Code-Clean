import mat4py
import serial
import time
from pySerialTransfer import pySerialTransfer as txfer
import sys

def mat_to_matrix_force():
    """Converts exported mat file from Custom_SP.slx to python-lists."""

    # Load Simulink .mat file
    data = mat4py.loadmat("../SimulinkData/simout.mat")

    # Initialize variables
    m1 = list()
    m2 = list()
    m3 = list()
    m4 = list()
    m5 = list()
    m6 = list()
    time = list()
    matrix = list()

    for row in data["Forces"]["time"]:
        time.append(row[0])

    for row in data["Forces"]["signals"]["values"]:
        m1.append(row[0])
        m2.append(row[1])
        m3.append(row[2])
        m4.append(row[3])
        m5.append(row[4])
        m6.append(row[5])

    # Check if all lists are of equal length
    eq_length = (len(m1)
                == len(m2)
                == len(m3)
                == len(m4)
                == len(m5)
                == len(m6)
                == len(time)
                )

    # Append rows with time and motordata to matrix.
    # Motordata is rounded to nearest integer.
    if eq_length:
        for i in range(len(m1)):
            matrix.append([
                time[i],
                round(m1[i]),
                round(m2[i]),
                round(m3[i]),
                round(m4[i]),
                round(m5[i]),
                round(m6[i]),
            ])
    print(len(matrix))

    return matrix

def mat_to_matrix_position():
    """Converts exported mat file from Custom_SP.slx to python-lists."""

    # Load Simulink .mat file
    data = mat4py.loadmat("../SimulinkData/simout_position_sinus.mat")

    # Initialize variables
    m1 = list()
    m2 = list()
    m3 = list()
    m4 = list()
    m5 = list()
    m6 = list()
    time = list()
    matrix = list()

    for row in data["d"]["time"]:
        time.append(row[0])

    for row in data["d"]["signals"]["values"]:
        m1.append(row[0])
        m2.append(row[1])
        m3.append(row[2])
        m4.append(row[3])
        m5.append(row[4])
        m6.append(row[5])

    # Check if all lists are of equal length
    eq_length = (len(m1)
                == len(m2)
                == len(m3)
                == len(m4)
                == len(m5)
                == len(m6)
                == len(time)
                )

    # Append rows with time and motordata to matrix.
    # Motordata is rounded to nearest integer.
    if eq_length:
        for i in range(len(m1)):
            matrix.append([
                time[i],
                round(m1[i]),
                round(m2[i]),
                round(m3[i]),
                round(m4[i]),
                round(m5[i]),
                round(m6[i]),
            ])
    #print(len(matrix))

    return matrix

def mat_to_matrix_position_simple_matrix():
    """Converts exported mat file from Custom_SP.slx to python-lists."""

    # Load Simulink .mat file
    data = mat4py.loadmat("../SimulinkData/PosMat.mat")

    # Initialize variables
    m1 = list()
    m2 = list()
    m3 = list()
    m4 = list()
    m5 = list()
    m6 = list()
    matrix = list()

    for row in data["PositionMatrix"]:
        m1.append(row[0])
        m2.append(row[1])
        m3.append(row[2])
        m4.append(row[3])
        m5.append(row[4])
        m6.append(row[5])

    # Check if all lists are of equal length
    eq_length = (len(m1)
                == len(m2)
                == len(m3)
                == len(m4)
                == len(m5)
                == len(m6)
                )

    # Append rows with time and motordata to matrix.
    # Motordata is rounded to nearest integer.
    if eq_length:
        for i in range(len(m1)):
            matrix.append([
                round(m1[i]),
                round(m2[i]),
                round(m3[i]),
                round(m4[i]),
                round(m5[i]),
                round(m6[i]),
            ])
    print(len(matrix))

    return matrix

def serial_write_matrix_with_time(matrix, port='/dev/cu.usbmodem14101'):
    """
    Sends each row in matrix to Arduino.
    Will send data in "real time", i.e. according to time-vector in matrix.
    """

    # Initialize variables
    arduino = txfer.SerialTransfer(port)
    arduino.open()
    time.sleep(6)
    curr_time = 0
    prev_time = 0

    try:
        for row in matrix:
            row_size = 0
            curr_time = row[0]

            # Remove time from row
            row = row[1:7]
            print(row)
            row_size = arduino.tx_obj(row)
            arduino.send(row_size)
            time.sleep(curr_time - prev_time)
            prev_time = curr_time


    except KeyboardInterrupt:
        try:
            arduino.close()
        except:
            pass

    except:
        import traceback
        traceback.print_exc()

        try:
            arduino.close()
        except:
            pass

def serial_write_matrix_simple(matrix, port='/dev/cu.usbmodem14101'):
    """
    Sends each row in matrix to Arduino.
    Waits for response from Arduino before sending next row via serial.
    """

    sensor_type_list = [ integer for integer in range(12) ]
    sensor_type_list[1] = 1.1
    #sensor_type_list = list()

    # Initialize variables
    arduino = txfer.SerialTransfer(port)
    arduino.open()
    time.sleep(6)
    curr_time = 0
    prev_time = 0
    final_sensor_matrix = list()

    try:
        sensor_row_size = arduino.tx_obj(sensor_type_list, 0)

        for row in matrix:
            row.insert(0, len(matrix))
            row_size = 0
            # print(row)
            row_size = arduino.tx_obj(row)
            arduino.send(row_size)

            # Wait for a response 
            # and report any errors while receiving packets
            while not arduino.available():
                if arduino.status < 0:
                    if arduino.status == txfer.CRC_ERROR:
                        print('ERROR: CRC_ERROR')
                    elif arduino.status == txfer.PAYLOAD_ERROR:
                        print('ERROR: PAYLOAD_ERROR')
                    elif arduino.status == txfer.STOP_BYTE_ERROR:
                        print('ERROR: STOP_BYTE_ERROR')
                    else:
                        print('ERROR: {}'.format(arduino.status))

            # Parse response list
            sensor_list  = arduino.rx_obj(obj_type=type(sensor_type_list),
                                     obj_byte_size=sensor_row_size,
                                        list_format='f')
            print('SENT: {}'.format(row))
            print('RCVD: {}'.format(sensor_list))

            # final_sensor_matrix.append(sensor_list)


    except KeyboardInterrupt:
        try:
            arduino.close()
        except:
            pass

    except:
        import traceback
        traceback.print_exc()

        try:
            arduino.close()
        except:
            pass

def serial_write_matrix_whole_test(matrix, port='/dev/cu.usbmodem14101'):
    """
    Sends whole matrix to Arduino.
    Received whole matrix again.
    """
    # Initialize variables
    arduino = txfer.SerialTransfer(port)
    arduino.open()
    time.sleep(0.5)
    final_sensor_matrix = list()
    row = [500,500,500,500,500,500]
    row.insert(0, len(matrix))
    row_size = 0
    row_size = arduino.tx_obj(row)
    time.sleep(0.1)
    arduino.send(row_size)

    # Send whole matrix
    try:
        # print(sensor_row_size)
        for row in matrix:
            row.insert(0, len(matrix))
            row_size = 0
            row_size = arduino.tx_obj(row)
            time.sleep(0.1)
            arduino.send(row_size)
            print("Sending {}".format(row))

    except KeyboardInterrupt:
        try:
            arduino.close()
        except:
            pass

    except:
        import traceback
        traceback.print_exc()

        try:
            arduino.close()
        except:
            pass

    # Receive whole matrix
    try:
        print("Listening...")
        while True:
            # Wait for a response 
            # and report any errors while receiving packets
            # while not arduino.available():
                # if arduino.status < 0:
                    # if arduino.status == txfer.CRC_ERROR:
                        # print('ERROR: CRC_ERROR')
                    # elif arduino.status == txfer.PAYLOAD_ERROR:
                        # print('ERROR: PAYLOAD_ERROR')
                    # elif arduino.status == txfer.STOP_BYTE_ERROR:
                        # print('ERROR: STOP_BYTE_ERROR')
                    # else:
                        # print('ERROR: {}'.format(arduino.status))

            rx_list = [ integer for integer in range(3) ]
            rx_list[1] = 1.1
            rx_row_size = arduino.tx_obj(rx_list, 0)

            if arduino.available():
                # Parse response list
                sensor_rx  = arduino.rx_obj(obj_type=type(rx_list),
                                            obj_byte_size=rx_row_size,
                                            list_format='h')
                print('RCVD: {}'.format(sensor_rx))
                # final_sensor_matrix.append(sensor_rx)

            # store_final_matrix(final_sensor_matrix)

    except KeyboardInterrupt:
        try:
            arduino.close()
        except:
            pass

    except:
        import traceback
        traceback.print_exc()

        try:
            arduino.close()
        except:
            pass

def serial_write_matrix_whole(matrix, port='/dev/cu.usbmodem14101'):
    """
    Sends whole matrix to Arduino.
    Received whole matrix again.
    """
    # Initialize variables
    arduino = txfer.SerialTransfer(port)
    arduino.open()
    time.sleep(0.5)
    final_sensor_matrix = list()
    stop = False

    # Send whole matrix
    try:
        # print(sensor_row_size)
        for row in matrix:
            row.insert(0, len(matrix))
            row_size = 0
            row_size = arduino.tx_obj(row)
            arduino.send(row_size)
            print("Sending {}".format(row))
            time.sleep(0.2)

    except KeyboardInterrupt:
        try:
            arduino.close()
        except:
            pass

    except:
        import traceback
        traceback.print_exc()

        try:
            arduino.close()
        except:
            pass

    # Receive whole matrix
    try:
        print("Listening...")
        while stop != True:
            # Wait for a response 
            # and report any errors while receiving packets
            # while not arduino.available():
                # if arduino.status < 0:
                    # if arduino.status == txfer.CRC_ERROR:
                        # print('ERROR: CRC_ERROR')
                    # elif arduino.status == txfer.PAYLOAD_ERROR:
                        # print('ERROR: PAYLOAD_ERROR')
                    # elif arduino.status == txfer.STOP_BYTE_ERROR:
                        # print('ERROR: STOP_BYTE_ERROR')
                    # else:
                        # print('ERROR: {}'.format(arduino.status))

            rx_list = [ integer for integer in range(14) ]
            rx_list[1] = 1.1
            rx_row_size = arduino.tx_obj(rx_list, 0)

            if arduino.available():
                # Parse response list
                sensor_rx  = arduino.rx_obj(obj_type=type(rx_list),
                                            obj_byte_size=rx_row_size,
                                            list_format='f')
                print('RCVD: {}'.format(sensor_rx))
                final_sensor_matrix.append(sensor_rx)
                stop = sensor_rx[13]

            # store_final_matrix(final_sensor_matrix)

    except KeyboardInterrupt:
        try:
            arduino.close()
        except:
            pass

    except:
        import traceback
        traceback.print_exc()

        try:
            arduino.close()
        except:
            pass

def serial_write_matrix_whole_SERIAL(matrix, rec_time=10, port='/dev/cu.usbmodem14101'):
    """
    Sends whole matrix to Arduino.
    Received whole matrix again.
    """
    # Initialize variables
    arduino = serial.Serial(port, baudrate=115200, timeout=1)
    arduino.flushInput()
    final_sensor_matrix = list()
    # stop = False
    # done = False
    REF_STRING = '{},{},{},{},{},{},{},{}'
    try:
        for row in matrix:
            # Insert length of matrix at position 0 in matrix
            row.insert(0, len(matrix))
            # Insert stop-program instruction bool
            row.insert(0, 0)
            REF_STRING = '{},{},{},{},{},{},{},{}'.format(
                    row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7]
                    )
            print("SEND: {}".format(REF_STRING))
            arduino.write(bytearray(REF_STRING, 'utf-8'))
            time.sleep(0.1)

    except KeyboardInterrupt:
        try:
            arduino.close()
        except:
            pass

    except:
        import traceback
        traceback.print_exc()

        try:
            arduino.close()
        except:
            pass

    # Receive sensor data
    try:
        time.sleep(0.1)
        t_end = time.time() + rec_time
        print("Listening...")
        while time.time() < t_end:
            count = time.perf_counter()
            data = arduino.readline().decode()[:-2].split(',')
            try:
                sensor_values = [float(num) for num in data]
                sensor_values.insert(0, count)
                print('RCVD: {}'.format(sensor_values))
                final_sensor_matrix.append(sensor_values)
            except:
                pass
        # store_final_matrix(final_sensor_matrix)

    except KeyboardInterrupt:
        try:
            arduino.close()
        except:
            pass

    except:
        import traceback
        traceback.print_exc()

        try:
            arduino.close()
        except:
            pass

def serial_read_sensors(rec_time=10, 
        path="../ArduinoSensorData/SensorOutput.mat", 
        port='/dev/cu.usbmodem14101'):
    """
    Reads and records sensor data from arduino and stores it in a mat-file.
    """
    # Initialize variables
    path="ArduinoSensorData/SensorOutput.mat"
    final_sensor_matrix = list()
    arduino = serial.Serial(port, baudrate=115200, timeout=1)
    arduino.flushInput()

    # Recieve whole matrix
    t_end = time.time() + rec_time
    # print("Listening...")
    while time.time() < t_end:
        count = time.perf_counter()
        data = arduino.readline().decode()[:-2].split(',')
        try:
            sensor_values = [float(num) for num in data]
            sensor_values.insert(0, count)
            print('RCVD: {}'.format(sensor_values))
            final_sensor_matrix.append(sensor_values)
        except:
            pass
    store_final_matrix(final_sensor_matrix, path)
    arduino.close()
    return ["ArduinoSensorData/SensorOutput.mat"]

def serial_read_sensors_matlab(rec_time=10, 
        path="../ArduinoSensorData/SensorOutput.mat", 
        port='/dev/cu.usbmodem14101'):
    """
    Reads and records sensor data from arduino and stores it in a mat-file.
    """
    # Initialize variables
    path="ArduinoSensorData/SensorOutput.mat"
    final_sensor_matrix = list()
    arduino = serial.Serial(port, baudrate=115200, timeout=1)
    arduino.flushInput()

    # Recieve whole matrix
    t_end = time.time() + rec_time
    # print("Listening...")
    while time.time() < t_end:
        try:
            count = time.perf_counter()
            data = arduino.readline().decode()[:-2].split(',')
            sensor_values = [float(num) for num in data]
            sensor_values.insert(0, count)
            print('RCVD: {}'.format(sensor_values))
            final_sensor_matrix.append(sensor_values)
        except:
            pass
    data = dict()
    time_list = list()
    force = list()
    position = list()
    ref_position = list()

    # Loop through each row in matrix
    for row in final_sensor_matrix:
        if len(row) == 19:
            # Time
            time_list.append(row[0])
            # Force
            values = [row[1],row[2],row[3],row[4],row[5],row[6]]
            force.append(values)
            # Position
            values = [row[7],row[8],row[9],row[10],row[11],row[12]]
            position.append(values)
            # Ref Position
            values = [row[13],row[14],row[15],row[16],row[17],row[18]]
            ref_position.append(values)

    data["sensor_time"] = time_list
    data["sensor_force"] = force
    data["sensor_position"] = position
    data["ref_position"] = ref_position
    mat4py.savemat(path, data)
    arduino.close()
    return "ArduinoSensorData/SensorOutput.mat"

def serial_read_sensors_watch(path="../ArduinoSensorData/SensorOutput.mat", 
        port='/dev/cu.usbmodem14101'):
    """
    Reads and records sensor data from arduino and stores it in a mat-file.
    """
    # Initialize variables
    path="ArduinoSensorData/SensorOutput.mat"
    final_sensor_matrix = list()
    arduino = serial.Serial(port, baudrate=115200, timeout=1)
    arduino.flushInput()

    # Recieve whole matrix
    while True:
        count = time.perf_counter()
        try:
            data = arduino.readline().decode()[:-2].split(',')
            try:
                sensor_values = [float(num) for num in data]
                sensor_values.insert(0, count)
                print('RCVD: {}'.format(sensor_values))
            except:
                pass
            # final_sensor_matrix.append(sensor_values)

        except KeyboardInterrupt:
            pass

def store_final_matrix(matrix, path="../ArduinoSensorData/SensorOutput.mat"):
    """Function for storing the received in a file.
    The file will then be opened by the GUI and display the sensor-
    values."""

    data = dict()
    time_list = list()
    force = list()
    position = list()
    ref_position = list()

    # Loop through each row in matrix
    for row in matrix:
        if len(row) == 19:
            # Time
            time_list.append(row[0])
            # Force
            values = [row[1],row[2],row[3],row[4],row[5],row[6]]
            force.append(values)
            # Position
            values = [row[7],row[8],row[9],row[10],row[11],row[12]]
            position.append(values)
            # Ref Position
            values = [row[13],row[14],row[15],row[16],row[17],row[18]]
            ref_position.append(values)

    data["sensor_time"] = time_list
    data["sensor_force"] = force
    data["sensor_position"] = position
    data["ref_position"] = ref_position
    mat4py.savemat(path, data)

if __name__ == "__main__":
    port = '/dev/cu.usbmodem14101'
    # matrix = mat_to_matrix_position_simple_matrix()
    # serial_write_matrix_simple(matrix, port=port)
    serial_read_sensors_watch(path="../ArduinoSensorData/SensorOutput.mat", port=port)

