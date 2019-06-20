from serial import Serial
import keyboard
import time
ser = Serial('/dev/ttyACM0',38400)
pos = 0
def inc(n,pos):
    pos +=n
    if(pos>180):
        pos = 180
    s =''
    print(n)
    s =('inc '+str(n)+'\n') 
    ser.write(s.encode())
    return pos
def dec(n,pos):
    pos = pos-n
    if(pos<0):
        pos = 0
    ser.write(('dec '+str(n)+'\n').encode())
    return pos
def laserOn():
    ser.write('laserOn\n'.encode())
def laserOff():
    ser.write('laserOff\n'.encode())
def calibrar():
    ser.write('pos 0\n'.encode())
    pos = 0
    return pos
calibrar()
q = ''
fps = 50
while(q!='q'):
    if keyboard.is_pressed('d'):
        pos = inc(1,pos)
    elif keyboard.is_pressed('a'):
        pos = dec(1,pos)
    elif keyboard.is_pressed('o'):
        laserOn()
    elif keyboard.is_pressed('f'):
        laserOff()
    elif keyboard.is_pressed('q'):
        q = 'q'
    elif(keyboard.is_pressed('c')):
        pos = calibrar()
    time.sleep(1/fps)



    
   
      # inc(str(q[2:]))
      # dec(str(q[2:]))
      # laserOn()
      # laserOff()
