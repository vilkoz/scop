#!/usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt

def load_data_from_file(name):
    with open(name, 'r') as f:
        s = f.read()

    s = s.split('\n')

    number = [int(x[0:x.find(' ')]) for x in s if x.find("test") != -1]
    times = [x[0:x.find('elapsed')] for x in s if x.find("elapsed") != -1]
    times = [float(x[0:x.find(':')]) * 60 + float(x[x.find(':') + 1:]) for x in times]
    print(number)
    print(times)
    return (times, number)

def get_x_y(name):
    times, number = load_data_from_file(name)
    x = np.array(number)
    y = np.array(times)
    return x, y

def main():
    x, y = get_x_y("data")
    x1, y1 = get_x_y("data2")
    x2, y2 = get_x_y("data3")
    x3, y3 = get_x_y("data4")

    p = np.poly1d(np.polyfit(x, y, 2))
    p30 = np.poly1d(np.polyfit(x, y, 7))

    print("prediction for 973139 %d" % p(973139))

    xp = np.linspace(0, 160e3, 100)
    _ = plt.plot(x, y, '.', x1, y1, '-', x2, y2, '--', x3, y3, '*')#, xp, p(xp), '-', xp, p30(xp), '--')
    plt.ylim(0,80)
    plt.show()

if __name__ == "__main__":
    main()
