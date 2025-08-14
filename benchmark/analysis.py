import matplotlib.pyplot as plt
import pandas as pd


def plot_stats(filepath, title):
    df = pd.read_csv(filepath)

    plt.figure(figsize=(8, 6), dpi=200)
    plt.title(title)
    plt.xlabel("Bytes Written")
    plt.ylabel("Time")
    plt.xscale("log", base=2)
    plt.yscale("log", base=2)

    chunksizes = df["chunksize"].unique()
    for cs in chunksizes:
        sizes = df[df["chunksize"] == cs]["bytes"]
        times = df[df["chunksize"] == cs]["time"]
        plt.plot(sizes, times, "s-", label=f"{cs} bytes")

    plt.grid(True)
    plt.legend(title="Chunksizes")
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    plot_stats("write_results.csv", "Write Speed")
    plot_stats("read_results.csv", "Read Speed")
