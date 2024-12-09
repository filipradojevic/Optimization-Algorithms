import sys
import math
import random
import matplotlib.pyplot as plt

file_sizes = [
    173669, 275487, 1197613, 1549805, 502334, 217684,
    1796841, 274708, 631252, 148665, 150254, 4784408,
    344759, 440109, 4198037, 329673, 28602, 144173,
    1461469, 187895, 369313, 959307, 1482335, 2772513,
    1313997, 254845, 486167, 2667146, 264004, 297223,
    94694, 1757457, 576203, 8577828, 498382, 8478177,
    123575, 4062389, 3001419, 196884, 617991, 421056,
    3017627, 131936, 1152730, 2676649, 656678, 4519834,
    201919, 56080, 2142553, 326263, 8172117, 2304253,
    4761871, 205387, 6148422, 414559, 2893305, 2158562,
    465972, 304078, 1841018, 1915571
] #Ovo je niz velicina datoteka u bajtovima koje treba selektovati

MAX_MEMORY = 64 * 1024 * 1024  # Maksimalna memorija
T0 = 32 * 1024 * 1024  # Početna temperatura Procenjena srednja vrednost optimizacione fje
NUM_ITERATIONS = 100000  # 100 000 Maksimalan broj iteracija
NUM_RUNS = 20  # Broj pokretanja algoritma

def objective_function(solution):
    F = sum(file_sizes[i] * solution[i] for i in range(len(file_sizes)))
    return F if F <= MAX_MEMORY else float('inf') 

def random_solution(): 
    #Ovo generise random niz duzine file_sizes da li ulaze u mem ili ne fajlovi (1->da, 0->ne)
    return [random.randint(0, 1) for _ in range(len(file_sizes))]

def neighbor_solution(solution):
    neighbor = solution[:]
    idx = random.randint(0, len(solution) - 1)
    neighbor[idx] = 1 - neighbor[idx]  
    # Flipuje vrednost (0 -> 1 ili 1 -> 0) na mestu random index-a 
    return neighbor

def simulated_annealing(): #Simuliranog kaljenja algoritam
    current_solution = random_solution()
    current_cost = objective_function(current_solution)
    best_solution = current_solution[:]
    best_cost = current_cost

    T = T0
    costs = []

    for i in range(NUM_ITERATIONS):
        new_solution = neighbor_solution(current_solution)
        new_cost = objective_function(new_solution)

        #ako je novo resenje manje od prvog automatski uzimamo
        if new_cost < current_cost or random.random() < math.exp((current_cost - new_cost) / T): 
            current_solution = new_solution
            current_cost = new_cost

        #Uzimamo najbolje resenjes
        if current_cost < best_cost:
            best_solution = current_solution[:]
            best_cost = current_cost

        T *= 0.99

        costs.append(best_cost)

        if best_cost <= 32*1024*1024:
            break

    return best_solution, best_cost, costs

all_runs_solutions = []
all_runs_costs = []
all_runs_best_costs = []

for run in range(NUM_RUNS):
    best_solution, best_cost, costs = simulated_annealing()
    all_runs_solutions.append(best_solution)
    all_runs_costs.append(costs)
    all_runs_best_costs.append(best_cost)
    print(f"Pokretanje {run + 1}: Vrednost optimizacione funkcije = {best_cost / (1024 * 1024):.2f} MiB")

for costs in all_runs_costs:
    for i in range(len(costs)):
        costs[i] = costs[i] / (1024 * 1024)

mean_cost_val = 0
for cost in all_runs_best_costs:
    if cost > sys.maxsize:
        continue
    else:
        mean_cost_val += cost
mean_cost_val /= len(all_runs_best_costs)

cost_diff = max(all_runs_best_costs)
mean_cost = 0
for cost in all_runs_best_costs:
    if cost_diff > abs(mean_cost_val - cost):
        mean_cost = cost
        cost_diff = abs(mean_cost_val - cost)

plt.figure()
plt.title("Kumulativni minimum svakog pokretanja algoritma simuliranog kaljenja")
plt.xlabel("Broj iteracija")
plt.axhline(y=32, linewidth=2, color = 'g')
plt.ylabel("Vrednost optimizacione funkcije [MiB]")
plt.yscale("log")
plt.xscale("log")
plt.grid()
for costs in all_runs_costs:
    plt.plot(costs, alpha=0.7)
plt.show()

plt.figure()
plt.plot(all_runs_costs[all_runs_best_costs.index(mean_cost)], alpha=0.7)
plt.title("Srednje najbolje resenje")
plt.xlabel("Broj iteracija")
plt.axhline(y=32, linewidth=2, color = 'g')
plt.ylabel("Vrednost optimizacione funkcije [MiB]")
plt.yscale("log")
plt.xscale("log")
plt.grid()
plt.show()

best_run_index = all_runs_best_costs.index(min(all_runs_best_costs))
best_run_solution = all_runs_solutions[best_run_index]
best_cost_bytes = min(all_runs_best_costs)

print("\n")
print(f"Najbolje resenje: {best_run_solution}")
print(f"Vrednost optimizacione funkcije najboljeg resenja: {best_cost_bytes / (1024 * 1024):.2f} MiB")
print("\n")
print(f"Srednje najbolje resenje: {all_runs_solutions[all_runs_best_costs.index(mean_cost)]}")
print(f"Vrednost optimizacione funkcije najboljeg resenja: {mean_cost / (1024 * 1024):.2f} MiB")

with open("AverageBestSolution.txt", "w") as f:
    f.write(f"Najbolje pronadjeno resenje:\n{best_run_solution}\n\n")
    f.write(f"Vrednost optimizacione funkcije: {best_cost_bytes / (1024 * 1024):.2f} MiB")