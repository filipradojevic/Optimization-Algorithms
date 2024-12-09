import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import minimize

# Sigmoid funkcija za aktivaciju
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

# Funkcija za izračunavanje izlaza mreže
def calculate_output(x_input, weights):
    # Izdvajanje težina
    w1, w2, w3, w4, w5, b1, b2, b3, b4, b5, v1, v2, v3, v4, v5, bias_out = weights[:16]

    # Srednji sloj (hidden layer)
    hidden_layer = np.array([
        w1 * x_input + b1,
        w2 * x_input + b2,
        w3 * x_input + b3,
        w4 * x_input + b4,
        w5 * x_input + b5
    ])
    hidden_layer = sigmoid(hidden_layer)  # Aktivacija skrivenog sloja (sigmoid)

    # Izlaz mreže (output layer)
    network_output = (
        v1 * hidden_layer[0] +
        v2 * hidden_layer[1] +
        v3 * hidden_layer[2] +
        v4 * hidden_layer[3] +
        v5 * hidden_layer[4] +
        bias_out
    )
    return network_output

# Funkcija za izračunavanje srednje kvadratne greške (MSE)
def calculate_mse(weights):
    # Izračunaj izlaze mreže za sve ulazne vrednosti
    y_predicted = np.array([calculate_output(x_i, weights) for x_i in x_values])
    # Izračunaj srednju kvadratnu grešku između predikcija i stvarnih vrednosti
    mse = np.mean((y_predicted - y_actual) ** 2)
    return mse

# Parametri sistema
Z_c = 5  # Karakteristična impedansa (Ohm)
Z_p = 10 + 2j  # Impedansa opterećenja (Ohm)
beta = 2 * np.pi  # Propagaciona konstanta (1/m)

# Ulazne vrednosti
x_values = np.arange(0, 0.251, 0.005)  # Koraci na opsegu [0, 0.25] sa intervalom 0.005

# Inicijalne težine mreže (slučajne vrednosti)
weights_initial = np.random.uniform(-30, 30, 16)

# Granice za optimizaciju težina
bounds = [(-30, 30) for _ in range(16)]

# Ciljne (trenirane) vrednosti izlaza
y_actual = np.abs(Z_c * (Z_p + 1j * Z_c * np.tan(beta * x_values)) / (Z_c + 1j * Z_p * np.tan(beta * x_values)))

# Izračunavanje inicijalne greške
error = calculate_mse(weights_initial)
iteration = 0  # Brojač iteracija

# Optimizacioni proces
while error > 1e-2:  # Ponovi dok greška ne bude manja od 0.01
    # Minimizacija funkcije greške korišćenjem Nelder-Mead metode
    result = minimize(calculate_mse, weights_initial, method='Nelder-Mead', bounds=bounds)
    # Ažuriranje težina sa optimizovanim vrednostima
    weights_initial = result.x
    # Ponovno izračunavanje greške
    error = calculate_mse(weights_initial)
    # Ispis trenutne greške
    print(f"Iteration {iteration + 1} - MSE: {error}")
    iteration += 1

# Izlaz mreže sa optimizovanim težinama
y_predicted_optimized = np.array([calculate_output(x_i, weights_initial) for x_i in x_values])

# Grafik poređenja ciljanih i predikovanih vrednosti
fig, ax = plt.subplots()
ax.plot(x_values, y_actual, color='red', lw=3, label="Trenirani podaci (y_actual)")
ax.plot(x_values, y_predicted_optimized, color='blue', linestyle='--', label="Predikcije mreže (y_predicted)")
ax.set_xlabel("x (Ulazne vrednosti)")
ax.grid()
ax.legend()
plt.show()

# Zapis rezultata u fajl
with open("output.txt", "w", encoding='utf-8') as file:
    file.write("Optimizovane težine (w1, w2, ..., w16):\n\n")
    file.write("(")
    for i in range(len(weights_initial)):
        file.write(f"{weights_initial[i]}")
        if i != len(weights_initial) - 1:
            file.write(", ")
        else:
            file.write(")\n\n")
    file.write(f"Minimalna greška (MSE): {error}\n")
