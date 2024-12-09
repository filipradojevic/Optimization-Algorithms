import numpy as np
import matplotlib.pyplot as plt
from scipy.special import spherical_jn
from scipy.optimize import brentq

def plot_spherical_bessel_functions(n, z_range):
    z = np.linspace(z_range[0], z_range[1], 400)
    for order in range(1, n + 1):  # Почиње од 1, не укључује n=0
        jn_values = spherical_jn(order, z)
        plt.plot(z, jn_values, label=f'n={order}')
    
    plt.title('Сферне Беселове функције')
    plt.xlabel('Аргумент z')
    plt.ylabel('spherical_jn(n, z)')
    plt.axhline(0, color='black', lw=0.5, ls='--')
    plt.axvline(0, color='black', lw=0.5, ls='--')
    plt.legend()
    plt.grid()
    plt.show()

def find_spherical_bessel_zeros(n, p_max, accuracy=1e-12):
    zeros = []
    
    for p in range(1, p_max + 1):
        # Постављање интервала претраге
        a = p * np.pi  # Долња граница
        b = (p + 1) * np.pi  # Горња граница

        try:
            # Израчунавање вредности функције на границама
            f_a = spherical_jn(n, a)
            f_b = spherical_jn(n, b)

            # Проверити промену знака
            if f_a * f_b < 0:
                root = brentq(lambda z: spherical_jn(n, z), a, b, xtol=accuracy)
                zeros.append(root)
            else:
                print(f"Nема промене знака за n={n}, p={p}. f(a)={f_a}, f(b)={f_b}")
        except ValueError as e:
            print(f"Грешка за n={n}, p={p}: {e}")
    
    return zeros

# Главни део кода
if __name__ == "__main__":
    # Цртање сферних Беселових функција
    plot_spherical_bessel_functions(2, (0, 20))  # Након цртања за ред до 2
    
    # Израчунавање нула и чување у ASCII фајл
    results = {}
    for n in [1, 2]:  # Редови функција
        results[n] = find_spherical_bessel_zeros(n, 2)  # Налажење прве две нуле

    # Испис резултата у ASCII фајл
    with open('spherical_bessel_zeros.txt', 'w', encoding='utf-8') as f:
        for n, zeros in results.items():
            f.write(f"Nуле за n={n}:\n")
            for zero in zeros:
                f.write(f"{zero}\n")

    print("Нуле су сачуване у 'spherical_bessel_zeros.txt'")
