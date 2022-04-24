import matplotlib.pyplot as plt
import numpy as np
import math

########## Constants
pi = math.pi

x = np.cos(-pi/4)
y = np.sin(-pi/4)
w = np.cos(pi/4)
z = np.sin(pi/4)

a1 = 45
b1 = 10
c1 = 25

a2 = 3
b2 = 15
c2 = 15

d = 125

d01 = 3
d1n = 15

velocity = 5.0
g = 9.82
##########

########## H matrices
H_r_c = np.array([[x, -y, 0, a2],
                  [y, x, 0, -b1-b2],
                  [0, 0, 1, c2],
                  [0, 0, 0, 1]])

H_r_a0 = np.array([[1, 0, 0, -a1],
                  [0, 1, 0, -b1],
                  [0, 0, 1, c1],
                  [0, 0, 0, 1]])
##########

def plant_init(H_o_r_init, phi_deg, theta_deg):
    
    phi = phi_deg*pi/180
    theta = theta_deg*pi/180
    beta = (45*pi/180) - theta
    
    H_c_p_init = np.array([[w, -z, 0, d*np.cos(theta)/np.cos(beta)],
                          [z, w, 0, -d*np.sin(theta)/np.cos(beta)],
                          [0, 0, 1, d*np.tan(phi)/np.cos(beta)],
                          [0, 0, 0, 1]])
    print("H_c_p_init = ",H_c_p_init)
    
    H_o_c_init = np.matmul(H_o_r_init, H_r_c)
    H_o_p = np.matmul(H_o_c_init, H_c_p_init)
    
    return H_o_p

def H_inv(H):
    R = np.array([H[0][0:3],
                  H[1][0:3],
                  H[2][0:3]])

    t = np.array([H[0][3],
                  H[1][3],
                  H[2][3]])

    R_T = np.transpose(R) 
    x = np.transpose(np.matmul(R_T,-t).reshape(1,3))
    y = np.concatenate((R_T,x), axis = 1)

    H_inv = np.concatenate((y,np.array([[0, 0, 0, 1]])), axis = 0)
    return H_inv

def localize(H_o_r):
    H_r_o = H_inv(H_o_r)
    H_r_p = np.matmul(H_r_o, H_o_p)
    H_a0_r = H_inv(H_r_a0)
    H_a0_p = np.matmul(H_a0_r, H_r_p)
    
    if H_a0_p[0][3] < 0:
        theta1 = 180 - (np.arctan(H_a0_p[1][3]/H_a0_p[0][3])*180/pi)
    else: 
        theta1 = np.arctan(-H_a0_p[1][3]/H_a0_p[0][3])*180/pi
        
    distance = ((H_a0_p[1][3]**2)+(H_a0_p[0][3]**2))**0.5/100
    height = H_a0_p[2][3]/100
    
    return theta1, distance, height

def instant_localize():
    global phi_deg, theta_deg
    phi = phi_deg*pi/180
    theta = theta_deg*pi/180
    beta = (45*pi/180) - theta

    H_c_p = np.array([[w, -z, 0, d*np.cos(theta)/np.cos(beta)],
                          [z, w, 0, -d*np.sin(theta)/np.cos(beta)],
                          [0, 0, 1, d*np.tan(phi)/np.cos(beta)],
                          [0, 0, 0, 1]])
    
    H_r_p = np.matmul(H_r_c, H_c_p)
    H_a0_r = H_inv(H_r_a0)
    H_a0_p = np.matmul(H_a0_r, H_r_p)
    
    if H_a0_p[0][3] < 0:
        theta1 = 180 - (np.arctan(H_a0_p[1][3]/H_a0_p[0][3])*180/pi)
    else: 
        theta1 = np.arctan(-H_a0_p[1][3]/H_a0_p[0][3])*180/pi
        
    distance = (((H_a0_p[1][3]**2)+(H_a0_p[0][3]**2))**0.5)/100
    height = (H_a0_p[2][3])/100
    
    return theta1, distance, height

def get_arm_pos():
    global phi_deg, theta_deg, velocity
    
    '''
    H_o_p = plant_init(H_o_r_init)
    theta1, distance, height = localize(H_o_r)
    print("theta1 = ",round(theta1,5), "distance = ",round(distance,5), "height = ",round(height,5))
    '''

    theta1, distance, height = instant_localize()
    print("theta1 = ",round(theta1,5), "distance = ",round(distance,5), "height = ",round(height,5))

    if theta1 < 0 and theta1 > 180:
        return "None"
    else:
        X = (velocity**4 - g*(2*height*velocity**2 + g*distance**2))
        if X < 0 :
            return "None"
        else:
            theta2 = np.arctan((1/g*distance)*(velocity**2 + X**0.5))*180/pi
            if theta2 < 0 and theta2 > 90:
                return "None"
            else:
                print("theta1 = ",round(theta1,5), "theta2 = ",round(theta2,5))
                return theta1, theta2

phi_deg = 30
theta_deg = 30
get_arm_pos()
