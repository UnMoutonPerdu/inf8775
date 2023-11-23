import matplotlib.pyplot as plt
import csv
  
x = []
y = []
  
with open('qs_seuil2.csv','r') as csvfile:
    plots = csv.reader(csvfile, delimiter = ',')
    for row in plots:
        if row[0] == "seuil":
            continue
        x.append(int(row[0]))
        y.append(int(row[1]))
  
plt.plot(x, y)
plt.xlabel('Seuil')
plt.ylabel('Temps')
plt.legend()
plt.show()