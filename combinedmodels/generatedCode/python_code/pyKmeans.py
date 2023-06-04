import numpy as np
from scipy.stats import circstd
from pyclustering.cluster.kmeans import kmeans
from pyclustering.utils.metric import distance_metric, type_metric
from pyclustering.cluster.center_initializer import kmeans_plusplus_initializer
from sklearn.metrics import silhouette_score




def training(x):
    X = np.array(x)
    data1 = X.reshape((len(X), 1))
    #print(data1)
    silh_scores = []
    for k in range(2, 5):
        initial_centers = kmeans_plusplus_initializer(data1, k).initialize()
        #print(initial_centers)
        metric = distance_metric(type_metric.USER_DEFINED, func=distance)
        instanceKm = kmeans(data1, initial_centers=initial_centers, metric=metric, ccore=True)
        instanceKm.process()
        pyClusters = instanceKm.get_clusters()
        data2 = np.concatenate(pyClusters)
        labels = []
        for j in range(len(pyClusters)):
            labels.append([j] * len(pyClusters[j]))
        #print(len(pyClusters))
        #print(instanceKm.get_centers())
        #print(labels)
        labels_merg = np.concatenate(labels)
        if len(pyClusters) == 1 :
            silh_scores.append(0)
            break
        else:
            silh_score = silhouette_score(data2.reshape(-1, 1), labels_merg, metric=distance)
            silh_scores.append(silh_score)
    if len(silh_scores) == 1 and silh_scores[0] == 0:
        nbr_clusters = 1
    else:
        nbr_clusters = np.argmax(silh_scores) + 2
    initial_centers = kmeans_plusplus_initializer(data1, nbr_clusters).initialize()
    metric = distance_metric(type_metric.USER_DEFINED, func=distance)
    instanceKm = kmeans(data1, initial_centers=initial_centers, metric=metric, ccore=True)
    instanceKm.process()
    pyClusters = instanceKm.get_clusters()
    pyCenters = instanceKm.get_centers()
    #print(pyClusters)
    #print(pyCenters)
    stdVars = []
    for i in range(len(pyClusters)):
        stdVars.append(circstd(pyClusters[i], high=1440, low=0))
    centers = np.concatenate(pyCenters)
    
    
    return centers,np.array(stdVars)

def distance(a1, b1):
    a = a1[0]
    b = b1[0]
    if a < b:
        return min(b - a, a - b + 1440)
    else:
        return min(a - b, b - a + 1440)

