#from signal import signal, SIGPIPE, SIG_DFL 
#Ignore SIG_PIPE and don't throw exceptions on it... (http://docs.python.org/library/signal.html)
#signal(SIGPIPE,SIG_DFL) 
import numpy as np
import math
import sys

np.set_printoptions(threshold=sys.maxsize)
from sklearn.neighbors import LocalOutlierFactor


def circtocart(v_theta):
    # v_theta: [0, 360, 1080,...]
    # [[x1,y1], [x2,y2]]
    """
    Change les cord d'un angle [0, 1440] to cart coord (x,y)
    Returns :
        le vect des coord cart
    """
    # initialisation du vecteur
    v_cart_cord = np.zeros((len(v_theta), 2))

    for i in range(len(v_theta)):
        angle = v_theta[i]
        angle_rad = (angle / 1440) * 2 * np.pi

        x = math.cos(angle_rad)
        y = math.sin(angle_rad)
        v_cart_cord[i] = np.array([x, y])

    return v_cart_cord


def train(data, k):
    # instantiate model
    clf = LocalOutlierFactor(n_neighbors=k, metric='cosine',novelty=True)

    # changing coordinates
    X = circtocart(data)

    # fit
    clf.fit(X)
    return clf


def score(clf, value):
    # changing coordinates
    X = circtocart([value])
    #prediction prends la valeur de 1 ou -1
    predict10 = clf.predict(X)
    predict = - clf.score_samples(X)
    return predict[0],predict10[0]


def main():
    pass


if __name__ == '__main__':
    main()
