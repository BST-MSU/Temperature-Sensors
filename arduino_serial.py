import numpy  as np# Import numpy
import matplotlib.pyplot as plt #import matplotlib library
from drawnow import *

tempF = []
# arduinoData = serial.Serial('/dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0') #Creating our serial object named arduinoData
plt.ion() #Tell matplotlib you want interactive mode to plot live data
buff = ""


def makeFig(): #Create a function that makes our desired plot
    plt.ylim(15,35)                                 #Set y min and max values
    plt.title('My Live Streaming Sensor Data')      #Plot the title
    plt.grid(True)                                  #Turn the grid on
    plt.ylabel('Temp F')                            #Set ylabels
    #plt.plot(tempF, 'ro-', label='Degrees F')       #plot the temperature
    objects = ('TP0','TP1','TP2','TP3','TP4','TP5')
    y_pos = np.arange(len(objects))
    performance = [10,8,6,4,2,1]
     
    plt.bar(y_pos, tempF, align='center', alpha=0.5)
    plt.xticks(y_pos, objects)
    plt.ylabel('Usage')
    plt.title('Programming language usage')


    # for i, v in enumerate(objects):
    #     plt.text(v + 3, i + .25, str(v), color='blue', fontweight='bold')
     
    plt.show()
    
print('lets go')
import serial
#ser = serial.Serial('/dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0', 57600)
ser = serial.Serial('/dev/ttyACM0', 57600)
ser_bytes = ser.readline()
temperature = [[] for i in range(10)]
x = 0

while True:
    #try:
        while (ser.inWaiting()==0): #Wait here until there is data
             pass #do nothing

        ser_bytes = ser.readline()
        decoded_bytes = str(ser_bytes[0:len(ser_bytes)].decode("utf-8"))
        
        decoded_bytes = decoded_bytes.replace('>','').replace('<','').replace('.','')
        decoded_bytes = decoded_bytes.rstrip('\n')

        #print(ser_bytes)
        recieved = decoded_bytes.split(':')
        # for i in range(6):
        #     recieved[i+1] = recieved[i+1][:len(recieved[i+1])-1] + '.' + recieved[i+1][len(recieved[i+1])-1:]

        if recieved[0] == 'TP05':
            temperature[0] = recieved
            temperature[0].pop(0)
            for i in range(len(temperature[0])):
                try:
                    temperature[0][i] = float(temperature[0][i])
                    temperature[0][i] /= 10.;
                except:
                    pass

        if recieved[0] == 'TP06':
            temperature[1] = recieved
            temperature[1].pop(0)
            for i in range(len(temperature[1])):
                try:
                    temperature[1][i] = float(temperature[1][i])
                    temperature[1][i] /= 10.;
                except:
                    pass

        if recieved[0] == 'TP07':
            temperature[2] = recieved
            temperature[2].pop(0)
            for i in range(len(temperature[2])):
                temperature[2][i] = float(temperature[2][i])
                temperature[2][i] /= 10.;
        if recieved[0] == 'TP08':
            temperature[3] = recieved
            temperature[3].pop(0)
            for i in range(len(temperature[3])):
                temperature[3][i] = float(temperature[3][i])
                temperature[3][i] /= 10.;
        if recieved[0] == 'TP09':
            temperature[4] = recieved
            temperature[4].pop(0)
            for i in range(len(temperature[4])):
                temperature[4][i] = float(temperature[4][i])
                temperature[4][i] /= 10.;
        if recieved[0] == 'TP10':
            temperature[5] = recieved
            temperature[5].pop(0)
            for i in range(len(temperature[5])):
                temperature[5][i] = float(temperature[5][i])
                temperature[5][i] /= 10.;
        if recieved[0] == 'TP11':
            temperature[6] = recieved
            temperature[6].pop(0)
            for i in range(len(temperature[6])):
                temperature[6][i] = float(temperature[6][i])
                temperature[6][i] /= 10.;
        if recieved[0] == 'TP12':
            temperature[7] = recieved
            temperature[7].pop(0)
            for i in range(len(temperature[7])):
                temperature[7][i] = float(temperature[7][i])
                temperature[7][i] /= 10.;
        if recieved[0] == 'TP13':
            temperature[8] = recieved
            temperature[8].pop(0)
            for i in range(len(temperature[8])):
                temperature[8][i] = float(temperature[8][i])
                temperature[8][i] /= 10.;
        if recieved[0] == 'TP14':
            temperature[9] = recieved
            temperature[9].pop(0)
            for i in range(len(temperature[9])):
                temperature[9][i] = float(temperature[9][i])
                temperature[9][i] /= 10.;
        if recieved[0] == 'TP15':
            temperature[10] = recieved
            temperature[10].pop(0)
            for i in range(len(temperature[10])):
                temperature[10][i] = float(temperature[10][i])
                temperature[10][i] /= 10.;

        
        x += 1
        buff = ""
        if x == 10:
            for i in range(10):
                buff += str(temperature[i]) + '  \n'
            x = 0
            tempF = (temperature[0])
            #print(tempF)

            try:
                drawnow(makeFig)                       #Call drawnow to update our live graph
            except:
                pass
            print(buff)


        # tempF = (temperature[0])
        # print(tempF)

        # drawnow(makeFig)                       #Call drawnow to update our live graph










    # except:
    #     print("poo Interrupt")
    #     ser.close()
    #     break
