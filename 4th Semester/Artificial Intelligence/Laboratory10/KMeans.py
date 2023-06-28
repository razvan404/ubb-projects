import copy
import random

import numpy as np


class MyKMeans:
    class Distances:
        @staticmethod
        def manhattan(point1, point2):
            return sum(abs(x - y) for x, y in zip(point1, point2))

        @staticmethod
        def euclidean(point1, point2):
            return sum((x - y) ** 2 for x, y in zip(point1, point2)) ** 0.5

        @staticmethod
        def cosine(point1, point2):
            return 1 - sum(x * y for x, y in zip(point1, point2)) / (sum(x ** 2 for x in point1) ** 0.5 *
                                                                     sum(y ** 2 for y in point2) ** 0.5)

    def __init__(self, n_clusters: int = 2, max_iter: int = 300, distance: str = 'euclidean'):
        if distance == 'euclidean':
            self.__distance = MyKMeans.Distances.euclidean
        elif distance == 'manhattan':
            self.__distance = MyKMeans.Distances.manhattan
        elif distance == 'cosine':
            self.__distance = MyKMeans.Distances.cosine
        else:
            raise Exception('Invalid distance metric')
        self.__n_clusters = n_clusters
        self.__max_iter = max_iter
        self.__centroids = None

    def fit(self, x: list, eps: float = 0.001):
        centroids_indexes = random.sample(range(len(x)), self.__n_clusters)
        self.__centroids = [x[i] for i in centroids_indexes]
        for k in range(self.__max_iter):
            print(f'Current iteration: {k}')
            prev_centroids = copy.deepcopy(self.__centroids)
            clusters = [[] for _ in range(self.__n_clusters)]
            for point in x:
                distances = [self.__distance(point, centroid) for centroid in self.__centroids]
                clusters[np.argmin(distances)].append(point)
            for i in range(self.__n_clusters):
                self.__centroids[i] = np.mean(clusters[i], axis=0)
            are_different = False
            for i in range(self.__n_clusters):
                for j in range(len(self.__centroids[i])):
                    if abs(self.__centroids[i][j] - prev_centroids[i][j]) > eps:
                        are_different = True
                        break
                if are_different:
                    break
            if not are_different:
                break

    def predict(self, x: list):
        centroids = []
        centroid_indexes = []
        for point in x:
            distances = [self.__distance(point, centroid) for centroid in self.__centroids]
            centroid_index = np.argmin(distances)
            centroids.append(self.__centroids[centroid_index])
            centroid_indexes.append(centroid_index)
        return centroid_indexes
