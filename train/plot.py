import matplotlib.pyplot as plt

start = 0
rate = 0

try :
	model = open("theta", "r")
	try :
		rate = float(model.readline())
		start = float(model.readline())
		model.close()
	except ValueError :
		print("Corrupted model file")
except IOError :
	print("No model file, default values are 0")

try : 
	data = open("data.csv", "r")
except IOError:
	print("No data.csv file, exit")
	exit()
km = []
price = []
data.readline()
line = data.readline()
while line :
	sp = line.split(',')
	km.append(float(sp[0]))
	price.append(float(sp[1]))
	line = data.readline()

#create prediction line
pred_km = [min(km), max(km)]
pred_price = [start + rate * pred_km[0], start + rate * pred_km[1]]

#plot
plt.plot(km, price, "og")
plt.plot(pred_km, pred_price, "r")
plt.xlabel('Km')
plt.ylabel('Price (eur)')
plt.show()

data.close()
