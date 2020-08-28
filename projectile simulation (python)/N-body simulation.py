from scipy.spatial.distance import pdist, squareform
import scipy.stats as stats
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation



# Refactored particle class from the original script from Jake. 
class Particle:
    """Particle class

    Properties include position and velocities. Methods include an
    advance function as well as convenience function to calculate
    momentum and energies.
    """

    # QUESTION 1
    g = np.array( [ 0.0, -9.8 ] )
    
    def __init__(self, state = [0.0, 0.0, 0.0, -1.0], size = 0.05, M = 0.05):
        self.state = state
        self.size = size
        self.mass = M

    def advance(self, dt ):
        self.state[:2] += dt*self.state[2:] + 0.5*Particle.g*dt*dt
        self.state[2:] += Particle.g*dt

    def getMomentum( self, dir ):
        # using pythagorus to find velocity
        vel_m = (self.state[3] ** 2 +self.state[2] ** 2) ** .5
        return vel_m * self.mass

    def getKE( self ):
        vel_ke = (self.state[3] ** 2 + self.state[2] ** 2)
        return .5 * vel_ke * self.mass

    def getPE( self, ref ):
        height = self.state[1] + 1
        return self.mass * 9.8 * height 

class ParticleBox:
    """ParticleBox class
    
    bounds is the size of the box: [xmin, xmax, ymin, ymax]
    """
    def __init__(self, Np = 3,
                 bounds = [-1.0, 1.0, -1.0, 1.0],
                 psize = 0.05,
                 mass = 0.05,
                 temperature = 1.0,
                 gravity = [0.0, -9.8] ):
        
        self.psize = psize # radius not diameter
        self.time_elapsed = 0
        self.bounds = np.array( bounds )
        self.delmv = np.zeros(4)
        Particle.g = np.array( gravity )

        # allocate and initialize state
        init_state = np.random.random( (Np, 4) )

        # QUESTION 2
        # position is somewhere in the box but not crossing boundaries
        Lxbox = (self.bounds[1] - self.bounds[0]) * (1-2*psize)
        Lybox = (self.bounds[3] - self.bounds[2]) * (1-2*psize)
        init_state[:,0] = bounds[0] + psize + init_state[:,0] * Lxbox
        init_state[:,1] = bounds[2] + psize + init_state[:,1] * Lybox

        # velocity from MB distribution
        vel = stats.maxwell.rvs( scale=np.sqrt( temperature ), size=Np )
        theta = 2 * np.pi * np.random.rand(Np)
        init_state[:, 2] = vel * np.sin(theta)
        init_state[:, 3] = vel * np.cos(theta)

        self.particles = [Particle( init_state[i],
                                    self.psize,
                                    mass )
                              for i in range( Np )]


        
    def advanceall(self, dt):
        for particle in self.particles:
            particle.advance( dt )
        
    def step(self, dt):
        """step once by dt seconds"""
        self.time_elapsed += dt
        
        # update positions and velocities
        self.advanceall(dt)

        # QUESTION 3
        # find pairs of particles undergoing a collision
        D = squareform(pdist(np.array([p.state[:2] for p in self.particles])))
        ind1, ind2 = np.where(D < 2 * self.psize)
        unique = (ind1 < ind2)
        ind1 = ind1[unique]
        ind2 = ind2[unique]

        # update velocities of colliding pairs
        for i1, i2 in zip(ind1, ind2):

            # mass
            m1 = self.particles[i1].mass
            m2 = self.particles[i2].mass

            # location vector
            r1 = self.particles[i1].state[:2]
            r2 = self.particles[i2].state[:2]

            # velocity vector
            v1 = self.particles[i1].state[2:]
            v2 = self.particles[i2].state[2:]

            # relative location & velocity vectors
            r_rel = r1 - r2
            v_rel = v1 - v2

            # QUESTION 4
            # this could happen if we have already scattered two balls
            # in a ternary collision
            if np.linalg.norm(r_rel) > 2*self.psize:
                continue

            # This scattering approach is modified by DGW from Jake's original
            # method to accomplish real 2D elastic scattering and to
            # approximate better the position of the collision scattering
            # formulas courtesy of Chad Berchek (a short monograph referenced
            # below).

            # back up until they touch using quadratic trajectory
            a = np.sum(v_rel**2)
            b = 2*np.sum(r_rel*v_rel)
            c = np.sum(r_rel**2) - 4*self.psize**2
            if a != 0:
                delt = (-b-np.sqrt(b*b-4*a*c))/(4*a)
            else:
                delt = 0

            self.particles[i1].advance( delt )
            self.particles[i2].advance( delt )


            # The numbered steps refer to Chad Berchek's steps. (DGW)
            # https://vobarian.com/collisions/2dcollisions2.pdf 

            # new location vector
            r1 = self.particles[i1].state[:2]
            r2 = self.particles[i2].state[:2]

            # velocity vector
            v1 = self.particles[i1].state[2:]
            v2 = self.particles[i2].state[2:]

            # new relative location
            r_rel = r1 - r2
            v_rel = v1 - v2

            # normal and tangent of collision (#1)
            n = -r_rel / np.linalg.norm(r_rel)
            t = np.array([-n[1], n[0]])

            # get velocities (#2)

            # project velocities (#3)
            vp1 = [np.dot(n,v1), np.dot(t,v1)]
            vp2 = [np.dot(n,v2), np.dot(t,v2)]
            
            # new velocity (#4 and #5)
            vn1 = [(vp1[0]*(m1-m2)+2*m2*vp2[0])/(m1+m2), vp1[1]]
            vn2 = [(vp2[0]*(m2-m1)+2*m1*vp1[0])/(m1+m2), vp2[1]]
            
            # unproject (#6 and #7)
            self.particles[i1].state[2:] = vn1[0]*n + vn1[1]*t
            self.particles[i2].state[2:] = vn2[0]*n + vn2[1]*t

            # continue with the new velocities
            self.particles[i1].advance( -delt )
            self.particles[i2].advance( -delt )


        # QUESTION 5
        # check for crossing boundary
        crossed_x1 = ([p.state[0]-p.size for p in self.particles] < self.bounds[0])
        crossed_x2 = ([p.state[0]+p.size for p in self.particles] > self.bounds[1])
        crossed_y1 = ([p.state[1]-p.size for p in self.particles] < self.bounds[2])
        crossed_y2 = ([p.state[1]+p.size for p in self.particles] > self.bounds[3])

        # left boundary bounce (index 0)
        for i in np.where(crossed_x1)[0]:
            p = self.particles[i]

            a = 0.5 * Particle.g[0]
            b = p.state[2]
            c = self.bounds[0] + p.size - p.state[0]
            if a == 0.0:
                delt = -c/b
            else:
                delt = (-b - np.sqrt( b*b - 4*a*c )) / (2*a)

            p.advance( -delt )
            # QUESTION 6
            p.state[2] *= -1
            self.delmv[0] += np.abs( p.getMomentum( 0 ) )
            p.advance( delt )
            
        # right boundary (index 1)
        for i in np.where(crossed_x2)[0]:
            p = self.particles[i]

            a = 0.5 * Particle.g[0]
            b = p.state[2]
            c = self.bounds[1] - p.size - p.state[0]
            if a == 0.0:
                delt = -c/b
            else:
                delt = (-b + np.sqrt( b*b - 4*a*c )) / (2*a)
            
            p.advance( -delt )
            p.state[2] *= -1
            self.delmv[1] += np.abs( p.getMomentum( 0 ) )
            p.advance( delt )
            
        # bottom boundary (index 2)
        for i in np.where(crossed_y1)[0]:
            p = self.particles[i]

            a = 0.5 * Particle.g[1]
            b = p.state[3]
            c = self.bounds[2] + p.size - p.state[1]
            if a == 0.0:
                delt = -c/b
            else:
                delt = (-b - np.sqrt( b*b - 4*a*c )) / (2*a)

            p.advance( -delt )
            p.state[3] *= -1
            self.delmv[2] += np.abs( p.getMomentum( 1 ) )
            p.advance( delt )
            
        # top boundary (index 3)
        for i in np.where(crossed_y2)[0]:
            p = self.particles[i]

            a = 0.5 * Particle.g[1]
            b = p.state[3]
            c = self.bounds[3] - p.size - p.state[1]
            if a == 0.0:
                delt = -c/b
            else:
                delt = (-b + np.sqrt( b*b - 4*a*c )) / (2*a)

            p.advance( -delt )
            p.state[3] *= -1
            self.delmv[3] += np.abs( p.getMomentum( 1 ) )
            p.advance( delt )

        
    # collect statistics (DGW)
    def getTotalEnergy(self):
        ke = self.getKineticEnergy()
        pe = self.getPotentialEnergy()
        return sum(ke+pe)

    def getPressure(self):
        return 2 * self.delmv / self.time_elapsed

    def getKineticEnergy(self):
        return sum( [p.getKE() for p in self.particles] )

    def getPotentialEnergy(self):
        return sum( [p.getPE( self.bounds ) for p in self.particles] )

    def getState( self, indx ):
        return [p.state[indx] for p in self.particles]


xdata = np.ones( 1000 ) / 70


box = ParticleBox(Np = 30)

ke = []
pe = []
 
 # david bowie
under_pressure = []
 
dt = .001
for i in range(1000):
     box.step(dt)
     under_pressure.append(box.getPressure())
     ke.append(box.getKineticEnergy())
     pe.append(box.getPotentialEnergy())
     
# make new list to get total energy. zip up two lists into tuples 
 # make a list of pe and kw values at the same time
total_e = [k_energy + p_energy for (k_energy, p_energy) in zip(ke , pe)]


 # Plot  of the kinetic, potential, and total energy of the system  
fig, graph_one = plt.subplots()


graph_one.plot(pe)
graph_one.plot(total_e)
graph_one.plot(ke)
graph_one.set_xlabel("Time")
graph_one.legend(["Potential energy", "total energy", "kinetic energy"])
graph_one.set_ylabel("Energy")
graph_one.set_title("kinetic, potential, and total energy")

 # plot of the four pressures as  afunction of time.
fig, graph_two = plt.subplots()
  
graph_two.plot(under_pressure)
graph_two.set_xlabel("Time")
graph_two.legend(["Right", "Left", "Bottom", "Top"])
graph_two.set_ylabel("Pressure")
graph_two.set_title("Pressures")


plt.show()
 