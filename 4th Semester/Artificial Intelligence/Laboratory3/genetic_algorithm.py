from typing import List

from my_chromosome import MyChromosome
from my_network import MyNetwork

from random import randint, uniform


class GeneticAlgorithm:
    mutation_prob = 0.5
    __cached_fitness = {}

    def __init__(self, network: MyNetwork, communities_count: int, population_size: int, modularity_function):
        self.__network = network
        self.__communities_count = communities_count
        self.__population_size = population_size
        self.__population = []
        for _ in range(population_size):
            c = MyChromosome(network, communities_count)
            self.__population.append(c)
        self.__modularity_function = modularity_function

        self.evaluate()

    @property
    def population(self) -> List[MyChromosome]:
        return self.__population

    def evaluate(self) -> None:
        for chromosome in self.__population:
            if chromosome in GeneticAlgorithm.__cached_fitness:
                chromosome.fitness = GeneticAlgorithm.__cached_fitness[chromosome]
            chromosome.fitness = self.__modularity_function(self.__network, chromosome.representation,
                                                            self.__communities_count)
            GeneticAlgorithm.__cached_fitness[chromosome] = chromosome.fitness

    def __best_chromosome_index(self) -> int:
        best = 0
        for i in range(1, self.__population_size):
            if self.__population[i] > self.__population[best]:
                best = i
        return best

    def best_chromosome(self) -> MyChromosome:
        return self.__population[self.__best_chromosome_index()]

    def __worst_chromosome_index(self) -> int:
        worst = 0
        for i in range(1, self.__population_size):
            if self.__population[i] < self.__population[worst]:
                worst = i
        return worst

    def worst_chromosome(self) -> MyChromosome:
        return self.__population[self.__worst_chromosome_index()]

    def __select(self, population: List[MyChromosome] = None) -> MyChromosome:
        if population is None:
            population = self.__population
        chromosome1 = population[randint(0, len(population) - 1)]
        chromosome2 = population[randint(0, len(population) - 1)]
        return chromosome1 if chromosome1.fitness > chromosome2.fitness else chromosome2

    def next_generation(self):
        # Select top 10% chromosomes
        new_population = sorted(self.__population, reverse=True)[:self.__population_size // 10]

        # Generate offsprings from top individuals
        for _ in range(self.__population_size // 4):
            parent1 = self.__select(new_population)
            parent2 = self.__select(new_population)
            child = parent1.crossover(parent2)
            if uniform(0, 1) < GeneticAlgorithm.mutation_prob:
                child.mutate()
            new_population.append(child)

        # Generate some offsprings from the rest of the individuals
        for _ in range(len(new_population), self.__population_size * 19 // 20):
            parent1 = self.__select(new_population)
            parent2 = self.__select(new_population)
            child = parent1.crossover(parent2)
            if uniform(0, 1) < GeneticAlgorithm.mutation_prob:
                child.mutate()
            new_population.append(child)

        # Fill remaining slots with random individuals
        new_population += [self.__select(self.__population[self.__population_size * 2 // 3:]) for _ in
                           range(len(new_population), self.__population_size)]

        self.__population = new_population
        self.evaluate()

