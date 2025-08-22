import matplotlib.pyplot as plt
import pandas as pd


def plot_stats(field: str):
    title = field.capitalize() + " Speed"

    plt.figure(figsize=(8, 6), dpi=200)
    plt.title(title)
    plt.xlabel("Chunk Size")
    plt.ylabel("Time")
    plt.xscale("log", base=2)
    plt.yscale("log", base=2)

    bufsizes = df["bufsize"].unique()
    for bs in bufsizes:
        sizes = df[df["bufsize"] == bs]["chunksize"]
        times = df[df["bufsize"] == bs][field]

        plt.plot(sizes, times, "s-", label=f"{int(bs / 1024 / 1024)} MB")

    plt.grid(True)
    plt.legend(title="Buffer Size")
    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    headers = ["bufsize", "chunksize", "write", "read"]
    df = pd.read_csv("./results/read_write.csv", header=None, names=headers)
    print(df)

    plot_stats("write")
    plot_stats("read")
