"""
Лабораторная работа: Полиномиальная регрессия
Стр. 47-52 учебного пособия

Задание 1: Генерирование выборки для заданных функций с моделированием случайной ошибки измерения
Задание 2: Восстановление функциональной зависимости с помощью полиномиальной регрессии
"""

import numpy as np
import math
import matplotlib
matplotlib.use('Agg')  # не требует GUI
import matplotlib.pyplot as plt
from typing import Optional
from scipy import stats


# ─────────────────────────────────────────────
# Часть I. Генерирование выборок
# ─────────────────────────────────────────────

def generate_uniform_error(n: int, eps0: float) -> np.ndarray:
    """Генерирует массив из n ошибок, равномерно распределённых на [-eps0, eps0]."""
    return np.random.uniform(-eps0, eps0, n)


def generate_normal_error(n: int, eps0: float, sigma: Optional[float] = None) -> np.ndarray:
    """Генерирует массив из n ошибок, нормально распределённых.

    Параметры
    ----------
    n      : размер выборки
    eps0   : граница интервала [-eps0, eps0]; используется для обрезки (clip) выходящих значений
    sigma  : стандартное отклонение; по умолчанию eps0 / 3 (правило трёх сигм)
    """
    if sigma is None:
        sigma = eps0 / 3.0
    errors = np.random.normal(0.0, sigma, n)
    return np.clip(errors, -eps0, eps0)


def f_poly3(x: np.ndarray, a: float, b: float, c: float, d: float) -> np.ndarray:
    """f(x) = ax³ + bx² + cx + d."""
    return a * x**3 + b * x**2 + c * x + d


def f_sinusoidal(x: np.ndarray) -> np.ndarray:
    """f(x) = x · sin(2πx)."""
    return x * np.sin(2 * math.pi * x)


def generate_sample(func, n: int, eps0: float, error_type: str = 'uniform', **func_kwargs):
    """Генерирует выборку {(x⁽ⁱ⁾, y⁽ⁱ⁾)}.

    x⁽ⁱ⁾ ~ Uniform(-1, 1)
    y⁽ⁱ⁾ = f(x⁽ⁱ⁾) + ε⁽ⁱ⁾

    Параметры
    ----------
    func       : функция f
    n          : размер выборки
    eps0       : граница ошибки
    error_type : 'uniform' или 'normal'
    **func_kwargs : дополнительные аргументы для func (a, b, c, d для f_poly3)

    Возвращает
    ----------
    x_sample, y_sample : массивы numpy
    """
    x_sample = np.random.uniform(-1, 1, n)
    y_true = func(x_sample, **func_kwargs)

    if error_type == 'uniform':
        errors = generate_uniform_error(n, eps0)
    elif error_type == 'normal':
        errors = generate_normal_error(n, eps0)
    else:
        raise ValueError(f"Неизвестный тип ошибки: {error_type!r}")

    y_sample = y_true + errors
    return x_sample, y_sample


# ─────────────────────────────────────────────
# Часть II. Полиномиальная регрессия (стр. 47-52)
# ─────────────────────────────────────────────

def build_gram_matrix(x: np.ndarray, M: int) -> np.ndarray:
    """Составляет матрицу Грама A и вектор b системы нормальных уравнений.

    Базисные функции: φⱼ(x) = xʲ, j = 0, …, M.

    Нормальные уравнения (из условия ∂E/∂wᵢ = 0):
        Σⱼ wⱼ · (Σₙ φᵢ(xₙ) φⱼ(xₙ)) = Σₙ yₙ φᵢ(xₙ), i = 0, …, M

    Параметры
    ----------
    x : обучающие аргументы
    M : степень полинома

    Возвращает
    ----------
    A : матрица (M+1) × (M+1)
    """
    A = np.zeros((M + 1, M + 1))
    for i in range(M + 1):
        for j in range(M + 1):
            A[i, j] = np.sum(x**i * x**j)  # Σₙ xₙⁱ · xₙʲ = Σₙ xₙ^(i+j)
    return A


def build_rhs(x: np.ndarray, y: np.ndarray, M: int) -> np.ndarray:
    """Составляет правую часть системы нормальных уравнений.

    bᵢ = Σₙ yₙ · xₙⁱ, i = 0, …, M

    Параметры
    ----------
    x, y : обучающая выборка
    M    : степень полинома

    Возвращает
    ----------
    b : вектор (M+1,)
    """
    b = np.array([np.sum(y * x**i) for i in range(M + 1)])
    return b


def polynomial_regression(x_train: np.ndarray, y_train: np.ndarray, M: int) -> np.ndarray:
    """Вычисляет коэффициенты полиномиальной регрессии степени M.

    Решает систему нормальных уравнений методом numpy.linalg.solve.

    Параметры
    ----------
    x_train, y_train : обучающая выборка
    M                : степень полинома

    Возвращает
    ----------
    w : вектор коэффициентов (w₀, w₁, …, wₘ)
    """
    A = build_gram_matrix(x_train, M)
    b = build_rhs(x_train, y_train, M)
    w = np.linalg.solve(A, b)
    return w


def predict(x: np.ndarray, w: np.ndarray) -> np.ndarray:
    """Вычисляет предсказание полинома: f̃(x) = Σⱼ wⱼ · xʲ."""
    M = len(w) - 1
    return sum(w[j] * x**j for j in range(M + 1))


def mse_loss(y_true: np.ndarray, y_pred: np.ndarray) -> float:
    """Среднеквадратическая ошибка (MSE = E(w)/N)."""
    return float(np.mean((y_true - y_pred) ** 2))


def train_test_split(x: np.ndarray, y: np.ndarray, test_ratio: float = 0.3, seed: int = 42):
    """Разбивает выборку на обучающую и тестовую.

    Параметры
    ----------
    x, y       : исходная выборка
    test_ratio : доля тестовой выборки (по умолчанию 30%)
    seed       : инициализатор генератора случайных чисел

    Возвращает
    ----------
    x_train, x_test, y_train, y_test
    """
    rng = np.random.default_rng(seed)
    indices = rng.permutation(len(x))
    n_test = int(len(x) * test_ratio)
    test_idx = indices[:n_test]
    train_idx = indices[n_test:]
    return x[train_idx], x[test_idx], y[train_idx], y[test_idx]


# ─────────────────────────────────────────────
# Вспомогательные функции для визуализации
# ─────────────────────────────────────────────

def plot_sample_and_function(ax, x_grid, y_grid, x_sample, y_sample,
                              title: str, func_label: str = 'f(x)'):
    """Отображает исходную функцию и выборку на одних осях."""
    ax.plot(x_grid, y_grid, 'b-', linewidth=2, label=func_label)
    ax.scatter(x_sample, y_sample, s=20, color='red', alpha=0.6, label='Выборка')
    ax.set_title(title, fontsize=10)
    ax.legend(fontsize=8)
    ax.grid(True, alpha=0.3)


def plot_regression(ax, x_grid, y_grid, x_sample, y_sample, w,
                    M: int, train_mse: float, test_mse: float, title: str):
    """Отображает исходную функцию, выборку и аппроксимирующий полином."""
    y_fit = predict(x_grid, w)
    ax.plot(x_grid, y_grid, 'b-', linewidth=2, label='f(x)')
    ax.scatter(x_sample, y_sample, s=15, color='red', alpha=0.5, label='Выборка')
    ax.plot(x_grid, y_fit, 'g--', linewidth=2, label=f'Полином M={M}')
    ax.set_title(f'{title}\nMSE train={train_mse:.4f}, test={test_mse:.4f}', fontsize=9)
    ax.legend(fontsize=7)
    ax.grid(True, alpha=0.3)
    # Ограничиваем ось y для читаемости
    y_min = min(y_grid.min(), y_sample.min()) - 0.5
    y_max = max(y_grid.max(), y_sample.max()) + 0.5
    ax.set_ylim(y_min, y_max)


# ─────────────────────────────────────────────
# Главная функция
# ─────────────────────────────────────────────

def main():
    np.random.seed(0)

    N = 100            # размер выборки
    x_grid = np.linspace(-1, 1, 500)

    # ── Случайные коэффициенты для полинома 3-й степени ──
    a, b, c, d = np.random.uniform(-3, 3, 4)
    print(f"Коэффициенты полинома: a={a:.3f}, b={b:.3f}, c={c:.3f}, d={d:.3f}")

    # ── Сетка истинных значений функций ──
    y_grid_poly = f_poly3(x_grid, a, b, c, d)
    y_grid_sin  = f_sinusoidal(x_grid)

    # ══════════════════════════════════════════════════
    # Рисунок 1: Выборки для обеих функций, оба типа ошибок
    # ══════════════════════════════════════════════════
    fig1, axes1 = plt.subplots(2, 2, figsize=(12, 8))
    fig1.suptitle('Задание 1: Генерирование выборок', fontsize=13, fontweight='bold')

    eps0_variants = [0.3, 0.7]   # две разные границы ошибки

    # -- Строка 1: полином 3-й степени --
    for col, (error_type, eps0) in enumerate([('uniform', eps0_variants[0]),
                                               ('normal',  eps0_variants[1])]):
        x_s, y_s = generate_sample(f_poly3, N, eps0, error_type=error_type,
                                   a=a, b=b, c=c, d=d)
        label = 'равномерная' if error_type == 'uniform' else 'нормальная'
        plot_sample_and_function(
            axes1[0, col], x_grid, y_grid_poly, x_s, y_s,
            title=f'f=ax³+bx²+cx+d, ε₀={eps0}, ошибка: {label}',
            func_label='ax³+bx²+cx+d'
        )

    # -- Строка 2: x·sin(2πx) --
    for col, (error_type, eps0) in enumerate([('uniform', eps0_variants[0]),
                                               ('normal',  eps0_variants[1])]):
        x_s, y_s = generate_sample(f_sinusoidal, N, eps0, error_type=error_type)
        label = 'равномерная' if error_type == 'uniform' else 'нормальная'
        plot_sample_and_function(
            axes1[1, col], x_grid, y_grid_sin, x_s, y_s,
            title=f'f=x·sin(2πx), ε₀={eps0}, ошибка: {label}',
            func_label='x·sin(2πx)'
        )

    plt.tight_layout()
    fig1.savefig('lab2_task1_samples.png', dpi=150)
    plt.close(fig1)
    print("Сохранён: lab2_task1_samples.png")

    # ══════════════════════════════════════════════════
    # Задание 2: Полиномиальная регрессия
    # ══════════════════════════════════════════════════

    # Генерируем одну выборку для каждой функции (равномерная ошибка, ε₀=0.5)
    eps0 = 0.5
    x_poly, y_poly = generate_sample(f_poly3, N, eps0, error_type='uniform',
                                     a=a, b=b, c=c, d=d)
    x_sin,  y_sin  = generate_sample(f_sinusoidal, N, eps0, error_type='uniform')

    # Разбиение на обучающую и тестовую выборки (70% / 30%)
    xp_tr, xp_te, yp_tr, yp_te = train_test_split(x_poly, y_poly)
    xs_tr, xs_te, ys_tr, ys_te = train_test_split(x_sin,  y_sin)

    # Степени полиномов: недообучение / хорошая модель / переобучение
    degrees_poly = {'Недообучение (M=1)': 1,
                    'Хорошая модель (M=3)': 3,
                    'Переобучение (M=15)': 15}
    degrees_sin  = {'Недообучение (M=1)': 1,
                    'Хорошая модель (M=9)': 9,
                    'Переобучение (M=20)': 20}

    # ── Рисунок 2: регрессия для полинома 3-й степени ──
    fig2, axes2 = plt.subplots(1, 3, figsize=(15, 4))
    fig2.suptitle('Задание 2: Полиномиальная регрессия\nf=ax³+bx²+cx+d',
                  fontsize=12, fontweight='bold')

    print("\n── Полином 3-й степени ──")
    for ax, (label, M) in zip(axes2, degrees_poly.items()):
        w = polynomial_regression(xp_tr, yp_tr, M)
        tr_mse = mse_loss(yp_tr, predict(xp_tr, w))
        te_mse = mse_loss(yp_te, predict(xp_te, w))
        print(f"  M={M:2d}  train MSE={tr_mse:.6f}  test MSE={te_mse:.6f}")
        plot_regression(ax, x_grid, y_grid_poly, x_poly, y_poly, w,
                        M, tr_mse, te_mse, label)

    plt.tight_layout()
    fig2.savefig('lab2_task2_poly3.png', dpi=150)
    plt.close(fig2)
    print("Сохранён: lab2_task2_poly3.png")

    # ── Рисунок 3: регрессия для x·sin(2πx) ──
    fig3, axes3 = plt.subplots(1, 3, figsize=(15, 4))
    fig3.suptitle('Задание 2: Полиномиальная регрессия\nf=x·sin(2πx)',
                  fontsize=12, fontweight='bold')

    print("\n── x·sin(2πx) ──")
    for ax, (label, M) in zip(axes3, degrees_sin.items()):
        w = polynomial_regression(xs_tr, ys_tr, M)
        tr_mse = mse_loss(ys_tr, predict(xs_tr, w))
        te_mse = mse_loss(ys_te, predict(xs_te, w))
        print(f"  M={M:2d}  train MSE={tr_mse:.6f}  test MSE={te_mse:.6f}")
        plot_regression(ax, x_grid, y_grid_sin, x_sin, y_sin, w,
                        M, tr_mse, te_mse, label)

    plt.tight_layout()
    fig3.savefig('lab2_task2_sinusoidal.png', dpi=150)
    plt.close(fig3)
    print("Сохранён: lab2_task2_sinusoidal.png")

    # ── Рисунок 4: MSE vs степень полинома (кривые обучения) ──
    Ms = list(range(1, 16))
    mse_tr_poly, mse_te_poly = [], []
    mse_tr_sin,  mse_te_sin  = [], []

    for M in Ms:
        # полином 3-й степени
        w = polynomial_regression(xp_tr, yp_tr, M)
        mse_tr_poly.append(mse_loss(yp_tr, predict(xp_tr, w)))
        mse_te_poly.append(mse_loss(yp_te, predict(xp_te, w)))
        # x·sin(2πx)
        w = polynomial_regression(xs_tr, ys_tr, M)
        mse_tr_sin.append(mse_loss(ys_tr, predict(xs_tr, w)))
        mse_te_sin.append(mse_loss(ys_te, predict(xs_te, w)))

    fig4, (ax4a, ax4b) = plt.subplots(1, 2, figsize=(12, 4))
    fig4.suptitle('MSE vs степень полинома M', fontsize=12, fontweight='bold')

    for ax, tr, te, title in [
        (ax4a, mse_tr_poly, mse_te_poly, 'f=ax³+bx²+cx+d'),
        (ax4b, mse_tr_sin,  mse_te_sin,  'f=x·sin(2πx)')
    ]:
        ax.plot(Ms, tr, 'b-o', markersize=4, label='Обучающая выборка')
        ax.plot(Ms, te, 'r-s', markersize=4, label='Тестовая выборка')
        ax.set_xlabel('Степень полинома M')
        ax.set_ylabel('MSE')
        ax.set_title(title)
        ax.legend()
        ax.grid(True, alpha=0.3)
        ax.set_yscale('log')

    plt.tight_layout()
    fig4.savefig('lab2_task2_mse_curve.png', dpi=150)
    plt.close(fig4)
    print("Сохранён: lab2_task2_mse_curve.png")

    print("\nВсе графики сохранены в текущую директорию.")


if __name__ == '__main__':
    main()
