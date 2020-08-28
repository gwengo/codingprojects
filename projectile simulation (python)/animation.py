
import numpy as np
import matplotlib.pyplot as plt
import math
import matplotlib.animation as animation
from matplotlib import style

# inputs
rho = 1.2754  # density of air
Af = math.pi * (16 * 0.0254) ** 2/4  # frontal area
g = -9.8
V = 250.0  # initial vel
Cd = 1
m = 2400


# motion
def update(r, V, a, dt):
    return r + (V * dt) + (.5 * a * dt ** 2), V + a*dt


# drag force
def drag( Vx, Vy):
    Vmag = math.sqrt(Vx**2 + Vy ** 2)
    Ff = 0.5 * Cd * rho * Af * Vmag ** 2
    return -Ff * (Vx/Vmag), -Ff * (Vy/Vmag)


def getTraj(dt, th, desired_time):

    state = [[0.0, 0.0, 0.0, V*math.cos(th), V*math.sin(th)]]

    while state[-1][2] >= 0:
        time = state[-1][0] + dt

        Fd = drag(state[-1][3], state[-1][4])
        ax = Fd[0] / m
        ay = (Fd[1] / m) + g

        nextX, nextVx = update(state[-1][1], state[-1][3], ax, dt)
        nextY, nextYx = update(state[-1][2], state[-1][4], ay, dt)

        state.append([time, nextX, nextY, nextVx, nextYx])

    dtf = -state[-1][2]*(state[-2][0]-state[-1][0])/(state[-2][2]-state[-1][2])

    xf, vxf = update(state[-1][1], state[-1][3], ax, dtf)
    yf, vyf = update(state[-1][2], state[-1][4], ay, dtf)

    state[-1] = [time+dtf, xf, yf, vxf, vyf]

    i = 0
    for ind, list in enumerate(state):
        if round(desired_time,2) == round(list[0],2):
            i = ind
    return state[i][1], state[i][2]


th = 20.0 * math.pi / 180.0  # gun angle in radians


##########
#############


style.use('fivethirtyeight')



a_time = 0
a_dt = .1


fig = plt.figure()
ax = plt.axes()
ax.set_xlabel("distance in seconds" )
ax.set_xlim(0, 5000)
ax.set_ylabel("Distance in meters" )
ax.set_ylim(0,500)

line1, = ax.plot(0, 0, lw=2, marker='o', markersize=12)
x_tsteps = np.linspace( 0, 1000, 1)

# current run

def animate(i):
    global a_time, dt, line1
   
    # steps need to match with time. Need distance of how much we are changing

    x = getTraj(a_dt, th, a_time)[0]  # gets the current x value
    line1.set_xdata(x)

    y = getTraj(a_dt, th, a_time)[1] # gets the current y value
    line1.set_ydata(y)
    a_time += a_dt
    return line1,


ani = animation.FuncAnimation(fig, animate, frames=x_tsteps, interval=10, blit=True)
plt.show()
