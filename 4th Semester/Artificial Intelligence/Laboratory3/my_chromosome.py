from random import randint, shuffle
from typing import List, Dict

from my_network import MyNetwork


class MyChromosome:
    def __init__(self, network: MyNetwork, communities_count: int,
                 representation: List[int] = None,
                 repartition: Dict[int, int] = None):
        self.__network = network
        self.__communities_count = communities_count
        self.__fitness = 0.0
        self.__representation = representation
        self.__repartition = repartition

        if representation is None and repartition is None:
            self.__representation = [i for i in range(1, communities_count + 1)]
            self.__repartition = {community: 1 for community in range(1, communities_count + 1)}

            for _ in range(self.__network.no_nodes - communities_count):
                value = randint(1, communities_count)
                self.__representation.append(value)
                self.__repartition[value] += 1
            shuffle(self.__representation)

    @property
    def representation(self):
        return self.__representation

    @property
    def repartition(self):
        return self.__repartition

    @property
    def fitness(self):
        return self.__fitness

    @fitness.setter
    def fitness(self, value: float):
        self.__fitness = value

    def __lt__(self, other):
        return self.__fitness < other.__fitness

    def __gt__(self, other):
        return self.__fitness > other.__fitness

    def __eq__(self, other):
        return self.__representation == other.__representation

    def __hash__(self):
        return hash(tuple(self.__representation))

    def crossover(self, other):
        cut = randint(0, len(self.__representation) - 1)
        new_representation = self.__representation[0:cut] + other.__representation[cut:len(self.__representation)]
        new_repartition = {community: new_representation.count(community)
                           for community in range(1, self.__communities_count + 1)}

        for community in range(1, self.__communities_count + 1):
            if community not in new_repartition:
                print(community)
                position = randint(0, len(self.__representation) - 1)
                while new_repartition[new_representation[position]] == 1:
                    position = randint(0, len(self.__representation) - 1)
                new_repartition[new_representation[position]] -= 1
                new_repartition[community] = 1
                self.__representation[position] = community

        return MyChromosome(self.__network, self.__communities_count,
                            representation=new_representation,
                            repartition=new_repartition)

    def mutate(self):
        position = randint(0, len(self.__representation) - 1)
        value = randint(1, self.__communities_count)
        while self.__repartition[self.__representation[position]] == 1 or self.__representation[position] == value:
            position = randint(0, len(self.__representation) - 1)
        self.__repartition[self.__representation[position]] -= 1
        self.__repartition[value] += 1
        self.__representation[position] = value
        return self
