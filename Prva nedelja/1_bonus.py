import time as t
import numpy as np
import random as r

N = int(input("N : "))
M = int(input("M : "))

people_speed = []

for i in range(N):
    people_speed.append(int(input("X{} [min] : ".format(i))))

start = t.time()

x = N
y = M

num_of_moves = 1       

while(x>y):    
    num_of_moves = num_of_moves + 1  
    x = x - y + 1

vector_size = num_of_moves*M + num_of_moves-1
vector = np.zeros(vector_size)

S1 = people_speed.copy()
S2 = []
vector_pos = 0
temp_pos_a = 0
temp_pos_b = M
temp_vector = 0

Time_iterations = []
iterations = 10000      # sto veci broj to je veca sansa da se "ubode" najefikasniji vektor

#iterations = int(input("Broj iteracija:"))      # moze ga zadavati i korisnik

vectors = np.zeros((iterations, vector_size))

for k in range(iterations):
    for i in range(num_of_moves):
        if i == num_of_moves - 1:
            if x != M:
                for j in range(x):
                    temp = r.choice(S1)
                    vector[vector_pos] = temp
                    S2.append(temp)
                    S1.remove(temp)
                    vector_pos = vector_pos +1
            else:
                for j in range(M):
                    temp = r.choice(S1)
                    vector[vector_pos] = temp
                    S2.append(temp)
                    S1.remove(temp)
                    vector_pos = vector_pos +1
        else:
            for j in range(M):
                temp = r.choice(S1)
                vector[vector_pos] = temp
                S2.append(temp)
                S1.remove(temp)
                vector_pos = vector_pos +1
                
        if vector_pos < vector_size:
            vector[vector_pos] = min(S2)
            S1.append(min(S2))
            S2.remove(min(S2))    
            vector_pos = vector_pos + 1
            
    for p in range(2*num_of_moves-1):
        if p % 2 == 0:
            temp_vector = temp_vector + max(vector[temp_pos_a:temp_pos_a+M])
            temp_pos_a = temp_pos_a + M + 1
        else:
            temp_vector = temp_vector + vector[temp_pos_b]
            temp_pos_b = temp_pos_b + M + 1
            
    
    Time_iterations.append(temp_vector)
    vectors[k] = vector
    
    S1 = people_speed.copy()
    S2 = []
    vector_pos = 0
    temp_pos_a = 0
    temp_pos_b = M
    temp_vector = 0

stop = t.time()

print("-------------------")
print("Tmin = {} min".format(min(Time_iterations)))
print("Vektor: {}".format(vectors[Time_iterations.index(min(Time_iterations))]))
print("Vreme izvrsavanja programa: {} sekundi".format(stop-start))


