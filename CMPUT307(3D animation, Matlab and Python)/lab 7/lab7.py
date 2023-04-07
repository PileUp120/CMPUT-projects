from dataclasses import replace
from dis import dis
import numpy as np
from sklearn import cluster

#referenced numpy documentation heavily

def point_wise_dist(point1, point2): #eucidean distance squared between two points
  return np.sum(np.power((point1 - point2), 2))

def find_new_centers(assignments, data, n_centers, curr_centers):
  clusters = [[] for i in range(n_centers)] #create a list of lists to store data points based on their assigned centers
  #assign point to cluster
  for i in range(np.shape(assignments)[0]):
    clusters[assignments[i]].append(data[i].tolist()) #store each point in the appropriate index of the clusted based on assignment
  
  for i in range(n_centers): #if a center has been assigned no points, keep it as is, otherwise calcualte the 
      if(len(clusters[i])==0): #new center based on the mean value of all of a center's assigned points
        clusters[i] = curr_centers[i]
      else:
        clusters[i] = np.array(clusters[i])
        clusters[i] = np.mean(clusters[i], axis=0)
  
  clusters = np.array(clusters)
  return clusters

def distance(data, centers):
    '''
    Calculate the distances from points to cluster centers.
      parameter:
        data: nparray of shape (n, 2)
        centers: nparray of shape (m, 2)
      return:
        distance: nparray of shape (n, m)
    '''
    '''
    num_points = np.shape(data)[0]
    num_centers = np.shape(centers)[0]
    distances = np.full((num_points, num_centers), np.inf) #create nxm array and initialise with infinity
    

    for i in range(num_centers):
      for j in range(num_points):
        distances[j][i] = np.sqrt(point_wise_dist(data[j], centers[i])) #find the distance between each point and every center
    '''
    vec_dist = np.vectorize(point_wise_dist) # vectorize distance function
    distances = np.zeros((np.shape(data)[0],1)) # create a zeros column vector with the same number of rows as data points
    for center in centers:
      # the vectorised function returns a n x 2 array of the squares of the differences of the x and y coordinates of each point to a center
      # so we find row wise sum and square root each value
      # then we concatenate the resultant nx1 array to the distances vector
      distances = np.column_stack((distances, np.sqrt(np.sum(vec_dist(data,center),axis=1))))
    distances = np.delete(distances,0,1) #finally we romove the initial 0 column, resulting in a nxm array
    
    return distances
    

def kmeans(data, n_centers):
    """
    Divide data into n_centers clusters, return the cluster centers and assignments.
    Assignments are the indices of the closest cluster center for the corresponding data point.
      parameter:
        data: nparray of shape (n, 2)
        n_centers: int
      return:
        centers: nparray of shape (n_centers, 2)
        assignments: nparray of shape (n,)
    """
    
    old_centers = np.zeros((n_centers,2))
    new_centers = np.zeros((n_centers,2))
    point_assignments = []
    random_indexes = np.random.choice(np.shape(data)[0], n_centers, replace=False)

    for i in range(n_centers):
      new_centers[i] = data[random_indexes[i]] #select n_centers number of points as centers from the original data list without duplicates

    centers_converged = False

    while not(centers_converged): #until centers stop changing keep recalculating centers
      old_centers = new_centers
      #using data calculate new centers
      distances = distance(data, new_centers)
      point_assignments = np.argmin(distances, axis=1)
      new_centers = find_new_centers(point_assignments, data, n_centers, old_centers)
      if(np.array_equal(old_centers,new_centers)):
        centers_converged = True
    
    return (new_centers, point_assignments)


def distortion(data, centers, assignments):
    """
    Calculate the distortion of the clustering.
      parameter:
        data: nparray of shape (n, 2)
        centers: nparray of shape (m, 2)
        assignments: nparray of shape (n,)
      return:
        distortion: float
    """
    distortion_value = 0.0
     #calcuate sum of distance squared of each point from the center they're assigned to
    distortion_value += np.sum([point_wise_dist(data[i],centers[assignments[i]]) for i in range(np.shape(data)[0])])
    return distortion_value

if __name__ == "__main__":
    # test your code here
    '''
    data = np.load('lab7.npy',allow_pickle=True)
    '''
    # I was getting a strange error when trying to open the sample data file, so I made my own sample of 15 data points
    data =[[74, 64], [60, 73], [1, 52], [-11, -6], [-5, 42], [6, 10], [13, 75], [-10, 79], [82, -17], [5, 15], [48, 65], [39, 43], [21, 17], [36, 35], [2, 46]]
    data = np.array(data)
    k_means_clusters = kmeans(data, 3)
    print(k_means_clusters[0])
    print(k_means_clusters[1])
    distortion_value = distortion(data, k_means_clusters[0], k_means_clusters[1])
    print(distortion_value)