# gwendolyn goins


import numpy as np
import matplotlib.pyplot as plt


nstates = 51

snames = np.array(['AL', \
                   'AK', \
                   'AZ', \
                   'AR', \
                   'CA', \
                   'CO', \
                   'CT', \
                   'DC', \
                   'DE', \
                   'FL', \
                   'GA', \
                   'HI', \
                   'ID', \
                   'IL', \
                   'IN', \
                   'IA', \
                   'KS', \
                   'KY', \
                   'LA', \
                   'ME', \
                   'MD', \
                   'MA', \
                   'MI', \
                   'MN', \
                   'MS', \
                   'MO', \
                   'MT', \
                   'NE', \
                   'NV', \
                   'NH', \
                   'NJ', \
                   'NM', \
                   'NY', \
                   'NC', \
                   'ND', \
                   'OH', \
                   'OK', \
                   'OR', \
                   'PA', \
                   'RI', \
                   'SC', \
                   'SD', \
                   'TN', \
                   'TX', \
                   'UT', \
                   'VA', \
                   'VT', \
                   'WA', \
                   'WV', \
                   'WI', \
                   'WY'])

# Clinton %, Trump %, EC
dataNov8 = np.array([ \
    [ 0.1, 99.9,  9], \
    [23.5, 76.5,  3], \
    [33.4, 66.6, 11], \
    [ 0.4, 99.6,  6], \
    [99.9,  0.1, 55], \
    [22.4, 77.6,  9], \
    [97.3,  2.7,  7], \
    [91.5,  8.5,  3], \
    [99.9,  0.1,  3], \
    [55.1, 44.9, 29], \
    [20.9, 79.1, 16], \
    [98.9,  1.1,  4], \
    [ 0.9, 99.1,  4], \
    [98.3,  1.7, 20], \
    [ 2.5, 97.5, 11], \
    [30.2, 69.8,  6], \
    [ 2.7, 97.3,  6], \
    [ 0.4, 99.6,  8], \
    [ 0.5, 99.5,  8], \
    [82.7, 17.3,  4], \
    [99.9,  0.1, 10], \
    [99.9,  0.1, 11], \
    [78.9, 21.1, 16], \
    [85.0, 15.0, 10], \
    [ 2.2, 97.8,  6], \
    [ 3.9, 96.1, 10], \
    [ 4.1, 95.9,  3], \
    [ 2.3, 97.7,  5], \
    [58.3, 41.7,  6], \
    [69.8, 30.2,  4], \
    [96.9,  3.1, 14], \
    [82.8, 17.2,  5], \
    [99.8,  0.2, 29], \
    [55.5, 44.5, 15], \
    [ 2.3, 97.7,  3], \
    [35.4, 64.6, 18], \
    [ 0.1, 99.9,  7], \
    [93.7,  6.3,  7], \
    [77.0, 23.0, 20], \
    [93.2,  6.8,  4], \
    [10.3, 89.7,  9], \
    [ 6.1, 93.9,  3], \
    [ 2.7, 97.3, 11], \
    [ 6.0, 94.0, 38], \
    [ 3.8, 96.2,  6], \
    [98.1,  1.9, 13], \
    [85.5, 14.5,  3], \
    [98.4,  1.6, 12], \
    [ 0.3, 99.7,  5], \
    [83.5, 16.5, 10], \
    [ 1.1, 98.9,  3], \
])


def simulate(data, states):
    wincount1 = 0
    wincount2 = 0
    tie_count = 0
    trumpvotes = 0
    clintonvotes = 0
    elect_votes = data[:, -1]
    for state in range(1, states):
        votes = elect_votes[state]
        elect_college_votes = sim_one(data, votes, state)
        clintonvotes += elect_college_votes[0]
        trumpvotes += elect_college_votes[1]
        # getting probability
        if elect_college_votes[0] > elect_college_votes[1]:
            wincount1 = wincount1 + 1
        elif elect_college_votes[1] > elect_college_votes[0]:
            wincount2 = wincount2 + 1
        else:
            tie_count = tie_count + 1
    outcome = False
    if trumpvotes > 270:
        pass
    elif clintonvotes > 270:
        outcome = True
    else:
        outcome = None
    prob1 = wincount1 / states  # clinton
    prob2 = wincount2 / states  # trump
    prob_tie = tie_count / states
    return prob1, prob2, prob_tie, clintonvotes, trumpvotes, outcome


def sim_one(data, elect_votes, trial):
    college1 = 0  # clinton
    college2 = 0  # trump
    votes = elect_votes
    rnd = np.random.randint(0,100)
    if rnd < data[trial][0]:
        college1 += votes
    else:
        college2 += votes
    return college1, college2


# problem 1
x_list = []
for num in range(1, 5000):
    outcome = simulate(dataNov8, nstates)
    x = outcome[3]
    x_list.append(x)

plt.hist(x_list, bins='auto')
plt.title("Clinton electoral college votes")
plt.show()

# problem 2
x1_list = []
y_list = []
for num in range(1, 1000):
    outcome = simulate(dataNov8, nstates)
    x = outcome[0]
    y = outcome[1]
    x1_list.append(x)
    y_list.append(x)

plt.hist([x1_list, y_list], alpha=0.5, label=['Clinton Probability', 'Trump Probability'])
plt.legend(loc='upper right')
plt.show()

oneElection = simulate(dataNov8, nstates)
print('probability of clinton:')
print(oneElection[0])
print('probability of trump:')
print(oneElection[1])
print('probability of tie:')
print(oneElection[2])

# looking at the graph out put, the probability that a candidate wins 350 votes is less than 50% percent likely given
# the simulated values.  That being said, there does seem to be a 47ish% chance that a Clinton would score more than
# 100 votes


# question 3

# what is the probability of Clinton winning assuming that she does win Ohio and what is the probability of Trump
# winning assuming that he does win Ohio – how do these compare with the probabilities in general, not assuming an Ohio
# win one way or the other?

# Given the output and running the simulation a few times, it seems that winning OH increases one's chances in winning
# the election. In both, when compared to the general election, the odds are respectively greater.

dataCWinOH = np.array([ \
    [ 0.1, 99.9,  9], \
    [23.5, 76.5,  3], \
    [33.4, 66.6, 11], \
    [ 0.4, 99.6,  6], \
    [99.9,  0.1, 55], \
    [22.4, 77.6,  9], \
    [97.3,  2.7,  7], \
    [91.5,  8.5,  3], \
    [99.9,  0.1,  3], \
    [55.1, 44.9, 29], \
    [20.9, 79.1, 16], \
    [98.9,  1.1,  4], \
    [ 0.9, 99.1,  4], \
    [98.3,  1.7, 20], \
    [ 2.5, 97.5, 11], \
    [30.2, 69.8,  6], \
    [ 2.7, 97.3,  6], \
    [ 0.4, 99.6,  8], \
    [ 0.5, 99.5,  8], \
    [82.7, 17.3,  4], \
    [99.9,  0.1, 10], \
    [99.9,  0.1, 11], \
    [78.9, 21.1, 16], \
    [85.0, 15.0, 10], \
    [ 2.2, 97.8,  6], \
    [ 3.9, 96.1, 10], \
    [ 4.1, 95.9,  3], \
    [ 2.3, 97.7,  5], \
    [58.3, 41.7,  6], \
    [69.8, 30.2,  4], \
    [96.9,  3.1, 14], \
    [82.8, 17.2,  5], \
    [99.8,  0.2, 29], \
    [55.5, 44.5, 15], \
    [ 2.3, 97.7,  3], \
    [0, 100, 18], # --------RIGHT HERE IS OHIO
    [ 0.1, 99.9,  7], \
    [93.7,  6.3,  7], \
    [77.0, 23.0, 20], \
    [93.2,  6.8,  4], \
    [10.3, 89.7,  9], \
    [ 6.1, 93.9,  3], \
    [ 2.7, 97.3, 11], \
    [ 6.0, 94.0, 38], \
    [ 3.8, 96.2,  6], \
    [98.1,  1.9, 13], \
    [85.5, 14.5,  3], \
    [98.4,  1.6, 12], \
    [ 0.3, 99.7,  5], \
    [83.5, 16.5, 10], \
    [ 1.1, 98.9,  3], \
])

print("OHIO: Clinton")
C_winOH_Election = simulate(dataCWinOH, nstates)
print('probability of clinton:')
print(C_winOH_Election[0])
print('probability of trump:')
print(C_winOH_Election[1])
print('probability of tie:')
print(C_winOH_Election[2])


dataTWinOH = np.array([ \
    [ 0.1, 99.9,  9], \
    [23.5, 76.5,  3], \
    [33.4, 66.6, 11], \
    [ 0.4, 99.6,  6], \
    [99.9,  0.1, 55], \
    [22.4, 77.6,  9], \
    [97.3,  2.7,  7], \
    [91.5,  8.5,  3], \
    [99.9,  0.1,  3], \
    [55.1, 44.9, 29], \
    [20.9, 79.1, 16], \
    [98.9,  1.1,  4], \
    [ 0.9, 99.1,  4], \
    [98.3,  1.7, 20], \
    [ 2.5, 97.5, 11], \
    [30.2, 69.8,  6], \
    [ 2.7, 97.3,  6], \
    [ 0.4, 99.6,  8], \
    [ 0.5, 99.5,  8], \
    [82.7, 17.3,  4], \
    [99.9,  0.1, 10], \
    [99.9,  0.1, 11], \
    [78.9, 21.1, 16], \
    [85.0, 15.0, 10], \
    [ 2.2, 97.8,  6], \
    [ 3.9, 96.1, 10], \
    [ 4.1, 95.9,  3], \
    [ 2.3, 97.7,  5], \
    [58.3, 41.7,  6], \
    [69.8, 30.2,  4], \
    [96.9,  3.1, 14], \
    [82.8, 17.2,  5], \
    [99.8,  0.2, 29], \
    [55.5, 44.5, 15], \
    [ 2.3, 97.7,  3], \
    [100, 0, 18], # --------RIGHT HERE IS OHIO
    [ 0.1, 99.9,  7], \
    [93.7,  6.3,  7], \
    [77.0, 23.0, 20], \
    [93.2,  6.8,  4], \
    [10.3, 89.7,  9], \
    [ 6.1, 93.9,  3], \
    [ 2.7, 97.3, 11], \
    [ 6.0, 94.0, 38], \
    [ 3.8, 96.2,  6], \
    [98.1,  1.9, 13], \
    [85.5, 14.5,  3], \
    [98.4,  1.6, 12], \
    [ 0.3, 99.7,  5], \
    [83.5, 16.5, 10], \
    [ 1.1, 98.9,  3], \
])

print("OHIO: Trump")
T_winOH_Election = simulate(dataTWinOH, nstates)
print('probability of clinton:')
print(T_winOH_Election[0])
print('probability of trump:')
print(T_winOH_Election[1])
print('probability of tie:')
print(T_winOH_Election[2])

print("OHIO: General")
gen_Election = simulate(dataNov8, nstates)
print('probability of clinton:')
print(gen_Election[0])
print('probability of trump:')
print(gen_Election[1])
print('probability of tie:')
print(gen_Election[2])

# Picking my  home state (north carolina) and doing the same thing, How critical is my state to the outcome?
# what happens if Clinton wins and what happens if Trump wins your home state?


# Given the output and running the simulation a few times, it seems that winning NC only slightly increases one's
# chances in winning the election. In both, when compared to the general election, the odds are sometimes greater.
# Still, it does have a small impact. It seems winning NC helps trump more than it does for Clinton


dataCWinNC = np.array([ \
    [0.1, 99.9, 9], \
    [23.5, 76.5, 3], \
    [33.4, 66.6, 11], \
    [0.4, 99.6, 6], \
    [99.9, 0.1, 55], \
    [22.4, 77.6, 9], \
    [97.3, 2.7, 7], \
    [91.5, 8.5, 3], \
    [99.9, 0.1, 3], \
    [55.1, 44.9, 29], \
    [20.9, 79.1, 16], \
    [98.9, 1.1, 4], \
    [0.9, 99.1, 4], \
    [98.3, 1.7, 20], \
    [2.5, 97.5, 11], \
    [30.2, 69.8, 6], \
    [2.7, 97.3, 6], \
    [0.4, 99.6, 8], \
    [0.5, 99.5, 8], \
    [82.7, 17.3, 4], \
    [99.9, 0.1, 10], \
    [99.9, 0.1, 11], \
    [78.9, 21.1, 16], \
    [85.0, 15.0, 10], \
    [2.2, 97.8, 6], \
    [3.9, 96.1, 10], \
    [4.1, 95.9, 3], \
    [2.3, 97.7, 5], \
    [58.3, 41.7, 6], \
    [69.8, 30.2, 4], \
    [96.9, 3.1, 14], \
    [82.8, 17.2, 5], \
    [99.8, 0.2, 29], \
    [0, 100, 15],  # <---- RIGHT HERE IS NC
    [2.3, 97.7, 3], \
    [35.4, 64.6, 18], \
    [0.1, 99.9, 7], \
    [93.7, 6.3, 7], \
    [77.0, 23.0, 20], \
    [93.2, 6.8, 4], \
    [10.3, 89.7, 9], \
    [6.1, 93.9, 3], \
    [2.7, 97.3, 11], \
    [6.0, 94.0, 38], \
    [3.8, 96.2, 6], \
    [98.1, 1.9, 13], \
    [85.5, 14.5, 3], \
    [98.4, 1.6, 12], \
    [0.3, 99.7, 5], \
    [83.5, 16.5, 10], \
    [1.1, 98.9, 3], \
    ])

print("NC: Clinton")
C_winNC_Election = simulate(dataCWinNC, nstates)
print('probability of clinton:')
print(C_winNC_Election[0])
print('probability of trump:')
print(C_winNC_Election[1])
print('probability of tie:')
print(C_winNC_Election[2])


dataTWinNC = np.array([ \
    [0.1, 99.9, 9], \
    [23.5, 76.5, 3], \
    [33.4, 66.6, 11], \
    [0.4, 99.6, 6], \
    [99.9, 0.1, 55], \
    [22.4, 77.6, 9], \
    [97.3, 2.7, 7], \
    [91.5, 8.5, 3], \
    [99.9, 0.1, 3], \
    [55.1, 44.9, 29], \
    [20.9, 79.1, 16], \
    [98.9, 1.1, 4], \
    [0.9, 99.1, 4], \
    [98.3, 1.7, 20], \
    [2.5, 97.5, 11], \
    [30.2, 69.8, 6], \
    [2.7, 97.3, 6], \
    [0.4, 99.6, 8], \
    [0.5, 99.5, 8], \
    [82.7, 17.3, 4], \
    [99.9, 0.1, 10], \
    [99.9, 0.1, 11], \
    [78.9, 21.1, 16], \
    [85.0, 15.0, 10], \
    [2.2, 97.8, 6], \
    [3.9, 96.1, 10], \
    [4.1, 95.9, 3], \
    [2.3, 97.7, 5], \
    [58.3, 41.7, 6], \
    [69.8, 30.2, 4], \
    [96.9, 3.1, 14], \
    [82.8, 17.2, 5], \
    [99.8, 0.2, 29], \
    [100, 0, 15],  # <---- RIGHT HERE IS NC
    [2.3, 97.7, 3],
    [35.4, 64.6, 18], \
    [0.1, 99.9, 7], \
    [93.7, 6.3, 7], \
    [77.0, 23.0, 20], \
    [93.2, 6.8, 4], \
    [10.3, 89.7, 9], \
    [6.1, 93.9, 3], \
    [2.7, 97.3, 11], \
    [6.0, 94.0, 38], \
    [3.8, 96.2, 6], \
    [98.1, 1.9, 13], \
    [85.5, 14.5, 3], \
    [98.4, 1.6, 12], \
    [0.3, 99.7, 5], \
    [83.5, 16.5, 10], \
    [1.1, 98.9, 3], \
    ])

print("NC: Trump")
T_winNC_Election = simulate(dataTWinNC, nstates)
print('probability of clinton:')
print(T_winNC_Election[0])
print('probability of trump:')
print(T_winNC_Election[1])
print('probability of tie:')
print(T_winNC_Election[2])

print("NC: General")
gen_Election = simulate(dataNov8, nstates)
print('probability of clinton:')
print(gen_Election[0])
print('probability of trump:')
print(gen_Election[1])
print('probability of tie:')
print(gen_Election[2])


# Part 2 --------------------------

from scipy.stats import norm

left = 1
mode = 2
right = 5


def pdf(x, left, right, mode):
    if (x >= left) & (x <= right):
        if x > mode:
            num = 2 * (x - left)
            denom = (right - left)*(mode - left)
            return num/denom
        if x <= mode:
            num = 2 * (right - x)
            denom = (right - left) * (right - mode)
            return num / denom
    return 0


# 	Plot the triangular	distribution

y = []
x = np.linspace(left - 1, right + 1, .25, endpoint=False)
for value in x:
    y = pdf(value, left, right, mode)
plt.plot(x, y)


h = plt.hist(np.random.triangular(left, mode, right,  700), bins=70,  density=True)
plt.show()

# Generate 1000 random samples from the triangular distribution using built in rand()


x1 = np.random.rand(1000)
y1 = []
for value in x1:
    y1 = pdf(value, left, right, mode)

# plt.plot(x1, y1)
h2 = plt.hist(np.random.triangular(left, mode, right,  1000), bins=70,  density=True)
plt.show()

# create your own random number generator for the triangular distribution using the rejection sampling method

def rejection(x, pdf, left, right, mode):
    rng = []
    for value in range(x):
        y = pdf(value, left, right, mode)

    box = [.5, .7]
    line = box / 2
    for value in y1:
        if value > line:
            rng.append(value)
    return rng


# create your own random number generator for the triangular distribution using the Metropolis algorithm

def metropolis(x, pdf, left, right, mode):
    total = num
    U = np.random.rand(0,1)
    rng = []
    for i in range(x):
        if (U <= left):
            value = (left * value + mode)
            rng.append(value / (num - 1))  # acceptance ration
    return rng
