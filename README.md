#About

Unnoficial mirror of http://unimotion.sourceforge.net

#About Unimotion

UniMotion provides unified motion detection for Apple portables. UniMotion is based on Motion with support for additional hardware coming from here. On top of all this, I've created a basic API and implemented probing so that you don't have to know what machine you're on.

While Motion has a BSD license, UniMotion is released under the LGPL. The original author and all contributors have given permission for this license change. The intent is to ensure that fixes and improvements aren't hoarded by closed-source projects and to ensure that closed-source programs utilising UniMotion are able to support the newest hardware models, even without support from the vendor. There is software out there that is SMS-aware but doesn't support my MacBook Pro. If everyone uses UniMotion, that will never happen again.

#Also

Mirrored here because of the mods made to get it built

also it contains python script form [iFiddling](http://ifiddling.blogspot.com/2009/01/dummy2.html) to allow data to be sent to iOS simulator running with [this code](http://code.google.com/p/accelerometer-simulator/wiki/Home)

So it lets simulate UIAccelerometer changes in iOS simulator using MacBook's accelerometer.


# HOWTO

## Build Unimotion

    $ cd src/; make; cd ..

## Run simulation

    $ src/bin/motion -f 17 | python sendaccsim.py
    >
     0.01 -0.02 -1.01
     0.01 -0.01 -1.02
     0.02 -0.01 -1.02
     0.01 -0.01 -1.03
     0.01 -0.02 -1.03
    -0.00 -0.02 -1.03
     0.01 -0.02 -1.03
     0.01 -0.02 -1.02

## Run simulator

With [code](http://code.google.com/p/accelerometer-simulator/wiki/Home#Embedding_into_your_application)


# Examples

- [HypnoAccel](https://github.com/gmarik/iOsProgramming-2e/tree/master/08-Accelerometer/HypnoAccell)