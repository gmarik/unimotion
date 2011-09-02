import sys, socket, time, traceback

kCFAbsoluteTimeIntervalSince1970 = 978307200.0 # from CFDate.c 

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(('',0))
sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

while 1:
  try:
    line = sys.stdin.readline()[:-1] # read line and strip EOL 
    fields = line.split() # split around space character 
    floatfields = map(float, fields) # convert to floats 

    # transform co-ordinate system, from SMS- to UIAcceleration-format,
    # for my macbook (late 2006) 
    x, y, z = map(lambda x: -1 * x, floatfields)

    # change epoch to be compatible with CFAbsoluteTimeGetCurrent() 
    currentTime = time.time() - kCFAbsoluteTimeIntervalSince1970

    accdata = ','.join(map(str,('ACC: 0',currentTime,x,y,z)))

    sock.sendto(accdata, ('<broadcast>', 10552))
    print '% .2f % .2f % .2f' % (x, y, z) 
  except (ValueError, KeyboardInterrupt):
    sock.close()
    sys.exit(-1)
  except:
    traceback.print_exc()