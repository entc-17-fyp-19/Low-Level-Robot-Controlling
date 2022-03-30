import matplotlib.pyplot as plt
import numpy as np
from sklearn import linear_model

f = open("Angular Velocities vs PWM.txt", "r")
data = []
for x in f:
    data.append(x)

data_L = []
data_R = []
for i in data[:-1]:
    data_L.append(float(i[:-1].split(" ")[1]))
    data_R.append(float(i[:-1].split(" ")[2]))

l = int(len(data_L)/2)
data_L1 = data_L[:l]
data_L2 = data_L[l:]
data_R1 = data_R[:l]
data_R2 = data_R[l:]

data_L_avg = []
data_R_avg = []
for i in range(l):
    data_L_avg.append((data_L1[i]+data_L2[-(i+1)])/2)
    data_R_avg.append((data_R1[i]+data_R2[-(i+1)])/2)

for i in range(l):
    if data_L_avg[i] > 0:
        L_begin = i
        break
for i in range(l):
    if data_R_avg[i] > 0:
        R_begin = i
        break

L = []
R = []
for i in range(L_begin,l):
    L.append(i)
for i in range(R_begin,l):
    R.append(i)

data_L_avg_filtered = data_L_avg[L_begin:]
data_R_avg_filtered = data_R_avg[R_begin:]

L_2D = np.array(L).reshape(-1,1)
R_2D = np.array(R).reshape(-1,1)
data_L_avg_filtered_2D = np.array(data_L_avg_filtered).reshape(-1,1)
data_R_avg_filtered_2D = np.array(data_R_avg_filtered).reshape(-1,1)

#print(L)
#print(data_L_avg_filtered)

regression = linear_model.LinearRegression(fit_intercept = True)
regression.fit(L_2D, data_L_avg_filtered_2D)
Coefficients_L = regression.coef_
Ïnercept_L = regression.intercept_
print("Coefficients_L: \n", Coefficients_L)
print("Ïnercept_L: \n", Ïnercept_L)

regression.fit(R_2D, data_R_avg_filtered_2D)
Coefficients_R = regression.coef_
Ïnercept_R = regression.intercept_
print("Coefficients_R: \n", Coefficients_R)
print("Ïnercept_R: \n", Ïnercept_R)

pred_L = []
pred_R = []
for i in range (L_begin,l):
    pred_L.append(Coefficients_L*i + Ïnercept_L)
for i in range (R_begin,l):
    pred_R.append(Coefficients_R*i + Ïnercept_R)

pred_L = np.array(pred_L).reshape(-1,1)
pred_R = np.array(pred_R).reshape(-1,1)

Coefficients_L_2 = np.polyfit(L,data_L_avg_filtered,2)
Coefficients_R_2 = np.polyfit(R,data_R_avg_filtered,2)

print("Coefficients_L_2: \n" , Coefficients_L_2)
print("Coefficients_R_2: \n" , Coefficients_R_2)

pred_L_2 = []
pred_R_2 = []
for i in range (L_begin,l):
    pred_L_2.append(Coefficients_L_2[0]*i**2 + Coefficients_L_2[1]*i+ Coefficients_L_2[2])
for i in range (R_begin,l):
    pred_R_2.append(Coefficients_R_2[0]*i**2 + Coefficients_R_2[1]*i+ Coefficients_R_2[2])

pred_L_2 = np.array(pred_L_2).reshape(-1,1)
pred_R_2 = np.array(pred_R_2).reshape(-1,1)

Coefficients_L_PWM = np.polyfit(data_L_avg_filtered,L,2)
Coefficients_R_PWM = np.polyfit(data_R_avg_filtered,R,2)

print(L_begin)
print(R_begin)

print("Coefficients_L_PWM: \n" , Coefficients_L_PWM)
print("Coefficients_R_PWM: \n" , Coefficients_R_PWM)
pred_L_PWM = []
pred_R_PWM = []
w = []
for i in range (360):
    w.append(i/100)
    pred_L_PWM.append(Coefficients_L_PWM[0]*(i/100)**2 + Coefficients_L_PWM[1]*(i/100)+ Coefficients_L_PWM[2])
for i in range (360):
    pred_R_PWM.append(Coefficients_R_PWM[0]*(i/100)**2 + Coefficients_R_PWM[1]*(i/100)+ Coefficients_R_PWM[2])

w = np.array(w).reshape(-1,1)
pred_L_PWM = np.array(pred_L_PWM).reshape(-1,1)
pred_R_PWM = np.array(pred_R_PWM).reshape(-1,1)

# Plot outputs
#plt.plot(L, data_L_avg_filtered, color="black")
#plt.plot(L, pred_L, color="red")
#plt.plot(L, pred_L_2, color="red")
#plt.plot(R, data_R_avg_filtered, color="black")
#plt.plot(R, pred_R, color="blue")
#plt.plot(R, pred_R_2, color="blue")
plt.plot(data_L_avg_filtered, L, color="black")
plt.plot(w, pred_L_PWM, color="red")
plt.plot(data_R_avg_filtered, R, color="black")
plt.plot(w, pred_R_PWM, color="blue")

plt.xticks(())
plt.yticks(())

plt.show()




