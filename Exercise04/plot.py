# Plots Exercise 4 results from timings.csv: threads vs time, and threads vs speedup.
# Needs matplotlib:  pip install matplotlib   then   python plot.py
import csv
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

rows = list(csv.DictReader(open("timings.csv")))
threads = [int(r["threads"]) for r in rows]
times = [float(r["time_s"]) for r in rows]
speedup = [times[0] / t for t in times]   # time for 1 thread / time for N threads

for y, label, name in ((times, "Time (s)", "threads_vs_time.png"),
                       (speedup, "Speedup (T1 / TN)", "threads_vs_speedup.png")):
    plt.figure(figsize=(6, 4))
    plt.plot(threads, y, marker="o")
    plt.xlabel("Number of threads"); plt.ylabel(label); plt.xticks(threads)
    plt.title(f"Pi, N = 100,000,000: {label.split(' (')[0].lower()} vs threads")
    plt.grid(alpha=0.3); plt.tight_layout(); plt.savefig(name, dpi=130); plt.close()

for t, s in zip(threads, speedup):
    print(f"{t:2d} threads: speedup = {s:.2f}")
