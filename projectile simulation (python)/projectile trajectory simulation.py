# Gwendolyn Goins




import math
import matplotlib.pyplot as plt
import numpy as np

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


def getTraj(dt, th):
    # initialize the problem
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
    return state


delt = 0.1
th = 20.0 * math.pi / 180.0  # gun angle in radians
m = 2400

# question one

Cd = 0.0
ideal = getTraj(delt, th)
tf = -2.0 * V * math.sin(th) / g
distance = V * math.cos(th) * tf

print("exact time in seconds: ", tf)
print("exact distance in m : ", distance)
print("no drag distance in m : ", ideal[-1][1])


Cd = 1.0
tsteps = [0.001, 0.003, .01, .03, 0.1, 0.3, 1.0, 3.0]

with_drag = getTraj(delt, th)
print("with drag distance in m : ", ideal[-1][1])

# question two

y = []
x = np.linspace(.001, 3, 100)
for value in x:
    y_val = getTraj(value, th)[-1][1]
    y.append(y_val)

plt.plot(x, y)
plt.xlabel("Time step in seconds")
plt.ylabel("Distance in meters")
plt.show()


# question three
ideal = np.array(ideal)
with_drag = np.array(with_drag)
plt.plot(ideal[:, 1], ideal[:, 2])
plt.plot(with_drag[:, 1], with_drag[:, 2])
plt.xlabel("Time step in seconds")
plt.ylabel("Distance in meters")
plt.show()




